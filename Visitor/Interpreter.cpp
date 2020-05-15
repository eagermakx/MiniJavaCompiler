//
// Created by Igor Maximov on 02.05.2020.
//

#include <Program.h>
#include <Stmt/Assign.h>
#include <Stmt/Cond.h>
#include <Stmt/Print.h>
#include <Visitor/Interpreter.h>
#include <Stmt/Ret.h>
#include <ast.h>
#include <log.h>
#include <iostream>
#include <Object/Integer.h>

namespace Visitor {

struct Returned : public std::exception {
  Returned() = default;
};

int Interpreter::Run(Program *program) {
  Visit(program);
  return return_value_;
}

void Interpreter::Visit(Program *program) {
  auto* main = program->main_class->GetMainFunction();
  
  CallParamList empty_list;
  
  CallMethod(program->main_class, main, &empty_list);
}

int Interpreter::CalcExpr(Expr::Base *expr) {
  temp_object_ = nullptr;
  expr->Accept(this);
  return temp_object_->ToInt();
}

void Interpreter::Visit(Stmt::Assign *that) {
  std::string& id = that->lhs->identifier;
  
  // Calc expression, store it into the variable
  int result = CalcExpr(that->rhs);
  
  // .at() function throws `out_of_range` exception
  // when passed a non-existing key, just how we want it
  
  Assign(that->lhs->symbol, std::make_shared<Integer>(result));
}

void Interpreter::Visit(Stmt::Cond *that) {
  bool condition = CalcExpr(that->condition);
  
  if (condition) {
    that->stmt_true->Accept(this);
  } else {
    if (that->stmt_false) {
      that->stmt_false->Accept(this);
    }
  }
}

void Interpreter::Visit(Stmt::Print *that) {
  int res = CalcExpr(that->expr);
  
  std::cout << res << std::endl;
}

void Interpreter::Visit(Stmt::Ret *that) {
  int result = CalcExpr(that->expr);
  // return_value_ = result;
  auto ret = std::make_shared<Integer>(result);
  current_frame->return_value = std::move(ret);
  
  throw Returned();
}

void Interpreter::Visit(Stmt::List *that) {
  for (Stmt::Base* stmt : that->list) {
    stmt->Accept(this);
  }
}

void Interpreter::Visit(Stmt::VarDecl *that) {
  Decl(that->var_id->symbol);
}

void Interpreter::Visit(Expr::Const *that) {
  // temp_register_ = that->value;
  // temp_object_ = std::make_shared<Integer>(that->value);
  temp_object_ = CreateObjectFromType(that->type, that->value);
}

void Interpreter::Visit(Expr::Id *that) {
  // temp_register_ = Value(that->symbol)->ToInt();
  temp_object_ = Value(that->symbol);
}

void Interpreter::Visit(Expr::This *this_expr) {
  if (current_frame->IsStatic()) {
    std::cerr << "'this' expression in static method does not refer to anything" << std::endl;
    exit(1);
  }
  
  temp_object_ = current_frame->GetThis();
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

void Interpreter::Visit(Expr::BinaryOp *that) {
  int lhs = CalcExpr(that->left);
  int rhs = CalcExpr(that->right);
  
  Type* output_type;
  
  if (Expr::IsBoolOperation(that->operation_type)) {
    output_type = new Bool();
  } else {
    output_type = new Int();
  }
  temp_object_ = CreateObjectFromType(output_type, that->op(lhs, rhs));
}

void Interpreter::Visit(Expr::UnaryOp *that) {
  int res = CalcExpr(that->expr);
  temp_object_ = CreateObjectFromType(new Int(), that->op(res));
}

void Interpreter::Visit(Stmt::ScopedList *scoped_list) {
  Visit(scoped_list->list);
  
  /*for (auto& var : scoped_list->scope->variables_) {
    // TODO: clear of unused symbols
  }*/
}


void Interpreter::Visit(Class *class_decl) {

}

void Interpreter::Visit(ClassMethod *method) {

}

void Interpreter::Visit(ClassField *field) {

}

void Interpreter::Visit(ProgramBody *body) {

}

void Interpreter::Visit(MainClass *main_class) {

}

void Interpreter::Visit(Expr::New *new_expr) {
  temp_object_ = CreateObjectFromType(new_expr->type);
}

void Interpreter::Visit(Expr::Call *call) {
  call->expr->Accept(this);
  
  auto return_value = CallMethod(call->cls, call->actual, call->passed_params, temp_object_);
  //temp_register_ = return_value->ToInt();
  temp_object_ = return_value;
}

void Interpreter::Visit(Stmt::ExprStmt *stmt_expr) {
  stmt_expr->expr->Accept(this);
}

std::shared_ptr<Object>
Interpreter::CallMethod(Class *cls,
                        ClassMethod *method,
                        CallParamList *params,
                        std::shared_ptr<Object> self)
{
  auto params_evaluated = EvaluateParams(params);
  
  // Prologue
  CallFrame* previous_frame = current_frame;
  current_frame = new CallFrame(cls, method);
  current_frame->PassParameters(std::move(params_evaluated));
  
  if (!method->is_static) {
    current_frame->SetThis(self);
  }
  
  // Actual call
  
  try {
    method->statements->Accept(this);
  } catch (Returned& returned) {
    // okay
  }
  
  // Epilogue
  auto ret = std::move(current_frame->return_value);
  
  delete current_frame;
  current_frame = previous_frame;
  return ret;
}

void Interpreter::Assign(Symbol* var, std::shared_ptr<Object> value) {
  try {
    std::string name = var->GetName();
    current_frame->VarSet(std::move(value), name);
  } catch (std::out_of_range& e) {
    std::cerr << "[!] Assignment to undeclared variable";
    exit(1);
  }
}

void Interpreter::Decl(Symbol* var) {
  std::string name = var->GetName();
  current_frame->AddVariable(name);
}

std::shared_ptr<Object> Interpreter::Value(Symbol* var) {
  try {
    return current_frame->VarGet(var->GetName());
  } catch (std::out_of_range& e) {
    std::cerr << "[!] Accessing undeclared variable";
    exit(1);
  }
}

std::vector<std::shared_ptr<Object>> Interpreter::EvaluateParams(CallParamList* params) {
  std::vector<std::shared_ptr<Object>> result;
  
  for (auto& param : params->params) {
    param->Accept(this);
    
    result.emplace_back(std::move(temp_object_));
  }
  
  return result;
}

} // namespace Visitor
