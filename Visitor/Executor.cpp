//
// Created by Igor Maximov on 02.05.2020.
//

#include <Program.h>
#include <Stmt/Assign.h>
#include <Stmt/Cond.h>
#include <Stmt/Print.h>
#include <Visitor/Executor.h>

#include <iostream>
#include <Stmt/Ret.h>

#include <ast.h>
#include <log.h>

namespace Visitor {

int Executor::Run(Program *program) {
  Visit(program);
  return return_value_;
}

void Executor::Visit(Program *program) {
  program->list->Accept(this);
}

int Executor::CalcExpr(Expr::Base *expr) {
  temp_register_ = 0;
  expr->Accept(this);
  return temp_register_;
}

void Executor::Visit(Stmt::Assign *that) {
  std::string& id = that->lvalue->id->identifier;
  
  // Calc expression, store it into the variable
  int result = CalcExpr(that->expr);
  
  // .at() function throws `out_of_range` exception
  // when passed a non-existing key, just how we want it
  vars_.at(id) = temp_register_;
}

void Executor::Visit(Stmt::Cond *that) {
  bool condition = CalcExpr(that->condition);
  
  if (condition) {
    that->stmt_true->Accept(this);
  } else {
    that->stmt_false->Accept(this);
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
  vars_.insert({that->ident->identifier, 0});
}

void Executor::Visit(Entity::Const *that) {
  temp_register_ = that->value;
}

void Executor::Visit(Entity::Id *that) {
  temp_register_ = vars_.at(that->identifier);
}

void Executor::Visit(Expr::lvalue *that) {
  temp_register_ = vars_.at(that->id->identifier);
}

void Executor::Visit(Expr::rvalue *that) {
  if (that->type == Expr::rvalue::Type::constant) {
    Visit(that->literal);
  } else if (that->type == Expr::rvalue::Type::ident) {
    Visit(that->id);
  }
}

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
}

} // namespace Visitor
