//
// Created by Igor Maximov on 02.05.2020.
//

#pragma once

#include "Visitor.h"
#include "ast_decl.h"

#include <unordered_map>

namespace Visitor {

class Executor : public Visitor::Base {
 public:
  Executor() = default;
  
  int Run(Program *program);
  
  int CalcExpr(Expr::Base* expr);
  
  // Variables
  void Assign(const std::string& var, int value);
  void Decl(const std::string& var);
  int Value(const std::string& var);
  
  void Visit(Program *program) override;
  void Visit(Entity::Const *that) override;
  void Visit(Entity::Id *that) override;
  void Visit(Expr::BinaryOp *that) override;
  void Visit(Expr::lvalue *that) override;
  void Visit(Expr::rvalue *that) override;
  void Visit(Expr::UnaryOp *that) override;
  void Visit(Stmt::Assign *that) override;
  void Visit(Stmt::Cond *that) override;
  void Visit(Stmt::Print *that) override;
  void Visit(Stmt::Ret *that) override;
  void Visit(Stmt::List *that) override;
  void Visit(Stmt::VarDecl *that) override;
  void Visit(Stmt::ScopedList* scoped_list) override;
 
 private:
  std::unordered_map<std::string, int> vars_{};
  int return_value_{0};
  int temp_register_{0};
};
  
} // namespace Visitor