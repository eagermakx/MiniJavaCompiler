//
// Created by Igor Maximov on 02.05.2020.
//

#include <Program.h>
#include <Stmt/Assign.h>
#include <Stmt/Cond.h>
#include <Stmt/Print.h>
#include <Visitor/Executor.h>
#include <Stmt/Ret.h>
#include <ast.h>
#include <log.h>
#include <iostream>
#include <Object/Integer.h>

namespace Visitor {

int Executor::Run(Program *program) {
  Visit(program);
  return return_value_;
}

void Executor::Visit(Program *program) {
  auto* main = program->main_class->GetMainFunction();
  
  CallMethod(program->main_class, main, std::vector<std::shared_ptr<Object>>());
}

int Executor::CalcExpr(Expr::Base *expr) {
  temp_register_ = 0;
  expr->Accept(this);
  return temp_register_;
}

void Executor::Visit(Stmt::Assign *that) {
  std::string& id = that->lhs->identifier;
  
  // Calc expression, store it into the variable
  int result = CalcExpr(that->rhs);
  
  // .at() function throws `out_of_range` exception
  // when passed a non-existing key, just how we want it
  
  Assign(that->lhs->symbol, std::make_shared<Integer>(result));
}

void Executor::Visit(Stmt::Cond *that) {
  bool condition = CalcExpr(that->condition);
  
  if (condition) {
    that->stmt_true->Accept(this);
  } else {
    if (that->stmt_false) {
      that->stmt_false->Accept(this);
    }
  }
}

void Executor::Visit(Stmt::Print *that) {
  int res = CalcExpr(that->expr);
  
  std::cout << res << std::endl;
}

void Executor::Visit(Stmt::Ret *that) {
  int result = CalcExpr(that->expr);
  return_value_ = result;
}

void Executor::Visit(Stmt::List *that) {
  for (Stmt::Base* stmt : that->list) {
    stmt->Accept(this);
  }
}

void Executor::Visit(Stmt::VarDecl *that) {
  Decl(that->var_id->symbol);
}

void Executor::Visit(Expr::Const *that) {
  temp_register_ = that->value;
}

void Executor::Visit(Expr::Id *that) {
  temp_register_ = Value(that->symbol)->ToInt();
}

void Executor::Visit(Expr::This *this_expr) {

}

/*void Executor::Visit(Expr::lvalue *that) {
  temp_register_ = Value(that->id->symbol);
}

void Executor::Visit(Expr::rvalue *that) {
  if (that->type == Expr::rvalue::Type::constant) {
    Visit(that->literal);
  } else if (that->type == Expr::rvalue::Type::ident) {
    Visit(that->id);
  }
}*/

void Executor::Visit(Expr::BinaryOp *that) {
  int lhs = CalcExpr(that->left);
  int rhs = CalcExpr(that->right);
  
  temp_register_ = that->op(lhs, rhs);
}

void Executor::Visit(Expr::UnaryOp *that) {
  int res = CalcExpr(that->expr);
  temp_register_ = that->op(res);
}

void Executor::Visit(Stmt::ScopedList *scoped_list) {
  Visit(scoped_list->list);
  
  /*for (auto& var : scoped_list->scope->variables_) {
    // TODO: clear of unused symbols
  }*/
}


void Executor::Visit(Class *class_decl) {

}

void Executor::Visit(ClassMethod *method) {

}

void Executor::Visit(ClassField *field) {

}

void Executor::Visit(ProgramBody *body) {

}

void Executor::Visit(MainClass *main_class) {

}

void Executor::Visit(Expr::New *new_expr) {
  new_expr->pointer = CreateObjectFromType(new_expr->type);
}

void Executor::Visit(Expr::Call *call) {
  CallMethod(call->cls, call->actual, std::vector<std::shared_ptr<Object>>(), call->pointer);
}

void Executor::Visit(Stmt::ExprStmt *stmt_expr) {
  stmt_expr->expr->Accept(this);
}

std::shared_ptr<Object>
Executor::CallMethod(Class *cls,
                     ClassMethod *method,
                     std::vector<std::shared_ptr<Object>> &&params,
                     std::shared_ptr<Object> self)
{
  // Prologue
  CallFrame* previous_frame = current_frame;
  current_frame = new CallFrame(cls, method);
  current_frame->PassParameters(std::move(params));
  
  if (!method->is_static) {
    current_frame->SetThis(std::move(self));
  }
  
  // Actual call
  method->statements->Accept(this);
  
  // Epilogue
  auto ret = std::move(current_frame->return_value);
  current_frame = previous_frame;
  return ret;
}

void Executor::Assign(Symbol* var, std::shared_ptr<Object> value) {
  try {
    std::string name = var->GetName();
    current_frame->VarSet(std::move(value), name);
  } catch (std::out_of_range& e) {
    std::cerr << "[!] Assignment to undeclared variable";
    exit(1);
  }
}

void Executor::Decl(Symbol* var) {
  std::string name = var->GetName();
  current_frame->AddVariable(name);
}

std::shared_ptr<Object> Executor::Value(Symbol* var) {
  try {
    return current_frame->VarGet(var->GetName());
  } catch (std::out_of_range& e) {
    std::cerr << "[!] Accessing undeclared variable";
    exit(1);
  }
}

/*void Executor::Assign(Symbol* var, int value) {
  try {
    std::string name = var->GetName();
    vars_.at(name) = value;
  } catch (std::out_of_range& e) {
    std::cerr << "[!] Assignment to undeclared variable";
    exit(1);
  }
}

void Executor::Decl(Symbol* var) {
  std::string name = var->GetName();
  vars_.insert({name, 0});
}

int Executor::Value(Symbol* var) {
  int res = 0;
  try {
    res = vars_.at(var->GetName());
  } catch (std::out_of_range& e) {
    std::cerr << "[!] Accessing undeclared variable";
    exit(1);
  }
  
  return res;
}*/

} // namespace Visitor
