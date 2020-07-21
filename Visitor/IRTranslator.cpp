//
// Created by Igor Maximov on 19.07.2020.
//

#include "IRTranslator.h"

#include <Decl/MainClass.h>
#include <Stmt/List.h>
#include <IR/wrappers/StmWrapper.h>
#include <IR/wrappers/ExpWrapper.h>
#include <IR/generators/Temp.h>
#include <IR/generators/Label.h>
#include <Stmt/Ret.h>
#include "ast.h"
#include "Program.h"

int Visitor::IRTranslator::Run(Program *program) {
  
  program->main_class->Accept(this);
  
  for (auto& cls : program->classes) {
    cls->Accept(this);
  }
  
  return 0;
}

void Visitor::IRTranslator::Visit(Class *class_decl) {
  for (auto& method : class_decl->methods) {
    auto method_subtree = Translate(method);
    method_trees_.emplace(method->name, method_subtree->ToStm());
  }
}

void Visitor::IRTranslator::Visit(ClassMethod *method) {
  current_frame_ = new IR::Frame(method->symbol);
  frames_[method->symbol] = current_frame_;
  
  for (auto& param : method->params) {
    current_frame_->AddVariable(*param.symbol);
  }
  
  current_frame_->StartScope();
  auto stm_list = Translate(method->statements);
  current_frame_->ExitScope();
  
  if (!stm_list) {
    std::cerr << "Empty function!" << std::endl;
    exit(1);
  }
  
  temp_value_ = new IR::StmWrapper(new IR::Seq(new IR::SetLabel(IR::Label(method->name)), stm_list->ToStm()));
}

void Visitor::IRTranslator::Visit(ClassField *field) {

}

void Visitor::IRTranslator::Visit(ProgramBody *body) {

}

void Visitor::IRTranslator::Visit(MainClass *main_class) {
  auto* main_method_subtree = Translate(main_class->GetMainFunction());
  method_trees_.emplace("main", main_method_subtree->ToStm());
}

void Visitor::IRTranslator::Visit(Program *program) {
  program->main_class->Accept(this);
  
  for (auto& cls : program->classes) {
    cls->Accept(this);
  }
}

void Visitor::IRTranslator::Visit(Expr::BinaryOp *binary_op) {
  auto e_lhs = Translate(binary_op->left);
  auto e_rhs = Translate(binary_op->right);
  
  temp_value_ = new IR::ExpWrapper(
    new IR::Binop(
      IR::AST_to_IR_transform(binary_op->operation_type),
      e_lhs->ToExp(),
      e_rhs->ToExp()
    )
  );
}

void Visitor::IRTranslator::Visit(Expr::Const *const_expr) {
  temp_value_ = new IR::ExpWrapper(new IR::Const(const_expr->value));
}

void Visitor::IRTranslator::Visit(Expr::Id *rvalue) {
  temp_value_ = new IR::ExpWrapper(current_frame_->GetAddress(*rvalue->symbol)->ToExp());
}

void Visitor::IRTranslator::Visit(Expr::This *this_expr) {

}

void Visitor::IRTranslator::Visit(Expr::UnaryOp *unary_op) {
  auto temp_expr = new IR::TempExp(IR::Temp());
  IR::Label ltrue;
  IR::Label lfalse;
  
  auto* expr = new IR::Eseq(
    new IR::Seq(
      new IR::Move(temp_expr, new IR::Const(1)),
      new IR::Seq(
        Translate(unary_op->expr)->ToCond(ltrue, lfalse),
        new IR::Seq(
          new IR::SetLabel(ltrue),
          new IR::Seq(
            new IR::Move(temp_expr, new IR::Const(0)),
            new IR::SetLabel(lfalse)
          )
        )
      )
    ),
    // Return negated value in IR context
    temp_expr
  );
  
  temp_value_ = new IR::ExpWrapper(expr);
}

void Visitor::IRTranslator::Visit(Expr::Call *call) {
  auto ir_params = new IR::ExpList();
  
  auto target = Translate(call->expr);
  
  IR::Temp left;
  auto temp_expr = new IR::TempExp(left);
  
  ir_params->Add(temp_expr);
  
  for (auto& ast_expr : call->passed_params->params) {
    ir_params->Add(Translate(ast_expr)->ToExp());
  }
  
  
  temp_value_ = new IR::ExpWrapper(new IR::Eseq(new IR::Move(temp_expr, target->ToExp()) ,new IR::Call(IR::Label(call->actual->name), ir_params)));
}

void Visitor::IRTranslator::Visit(Expr::New *new_expr) {
  temp_value_ = new IR::ExpWrapper(new IR::Call(IR::Label("__malloc"), new IR::ExpList()));
}

void Visitor::IRTranslator::Visit(Stmt::Assign *assn) {
  auto to = current_frame_->GetAddress(*assn->lhs->symbol)->ToExp();
  auto from = Translate(assn->rhs);
  
  temp_value_ = new IR::StmWrapper(new IR::Move(to, from->ToExp()));
}

void Visitor::IRTranslator::Visit(Stmt::Cond *cond) {
  IR::Label ltrue;
  IR::Label lfalse;
  IR::Label ljoin;
  
  auto condition = Translate(cond->condition);

  current_frame_->StartScope();
  auto true_branch = Translate(cond->stmt_true);
  current_frame_->ExitScope();
  
  current_frame_->StartScope();
  auto false_branch = Translate(cond->stmt_false);
  current_frame_->ExitScope();
  
  // Building whole sequence bottom-up
  IR::BaseStm* suffix = new IR::SetLabel(ljoin);
  
  if (cond->stmt_false) {
    suffix = new IR::Seq(new IR::SetLabel(lfalse), new IR::Seq(false_branch->ToStm(), suffix));
    
    if (cond->stmt_true) {
      suffix = new IR::Seq(new IR::Jump(ljoin), suffix);
    }
  }
  
  if (cond->stmt_true) {
    suffix = new IR::Seq(new IR::SetLabel(ltrue), new IR::Seq(true_branch->ToStm(), suffix));
  }
  
  // With no 'else' branch, fall through
  if (!cond->stmt_false) {
    lfalse = ljoin;
  }
  
  auto tmp = condition->ToCond(ltrue, lfalse);
  
  temp_value_ = new IR::StmWrapper(new IR::Seq(condition->ToCond(ltrue, lfalse), suffix));
}

void Visitor::IRTranslator::Visit(Stmt::Print *print) {
  auto params = new IR::ExpList();
  params->Add(Translate(print->expr)->ToExp());
  
  temp_value_ = new IR::StmWrapper(new IR::Exp(new IR::Call(IR::Label("__println"), params)));
}

void Visitor::IRTranslator::Visit(Stmt::Ret *ret) {
  auto expr = Translate(ret->expr);
  temp_value_ = new IR::StmWrapper(
    new IR::Move(
            current_frame_->GetRetValueAddress()->ToExp(),
            expr->ToExp()
        )
  );
}

void Visitor::IRTranslator::Visit(Stmt::List *list) {
  if (list->list.empty()) {
    temp_value_ = nullptr;
    return;
  }
  
  if (list->list.size() == 1) {
    list->list[0]->Accept(this);
    // temp_value_ is overwritten
  } else {
    std::vector<IR::BaseStm*> statements;
    statements.reserve(list->list.size());
//    size_t index = 0;
    for (auto statement: list->list) {
      auto stmt = Translate(statement);
      if (stmt) {
        statements.push_back(stmt->ToStm());
      }
    }
    IR::BaseStm* suffix = statements.back();
    
    for (int index = static_cast<int>(statements.size()) - 2; index >= 0; --index) {
      suffix = new IR::Seq(
        statements.at(index),
        suffix
      );
    }
    temp_value_ = new IR::StmWrapper(suffix);
  }
}

void Visitor::IRTranslator::Visit(Stmt::VarDecl *var_decl) {
  current_frame_->AddVariable(*var_decl->var_id->symbol);
  temp_value_ = nullptr;
}

void Visitor::IRTranslator::Visit(Stmt::ScopedList *scoped_list) {
  current_frame_->StartScope();
  
  temp_value_ = Translate(scoped_list->list);
  
  std::cout << "[log] Variables to destroy: \n";
  auto variables = current_frame_->GetCurrentScope().vars;
  while (!variables.empty()) {
    auto symbol = variables.top();
    variables.pop();
    std::cout << symbol.GetLabel() << std::endl;
  }
  
  current_frame_->ExitScope();
}

void Visitor::IRTranslator::Visit(Stmt::ExprStmt *stmt_expr) {
  temp_value_ = new IR::StmWrapper(Translate(stmt_expr->expr)->ToStm());
}

IRMapping Visitor::IRTranslator::GetMapping() {
  return method_trees_;
}

IR::SubtreeWrapper *Visitor::IRTranslator::Translate(BaseNode *node) {
  if (!node) {
    return nullptr;
  }
  
  node->Accept(this);
  return temp_value_;
}
