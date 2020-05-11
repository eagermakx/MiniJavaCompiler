//
// Created by Igor Maximov on 02.05.2020.
//

#pragma once

#include "Visitor.h"
#include "ast_decl.h"
#include "SymbolTable/Symbol.h"

#include <unordered_map>

namespace Visitor {

class Executor : public Visitor::Base {
 public:
  Executor() = default;
  
  int Run(Program *program);
  
  int CalcExpr(Expr::Base* expr);
  
  // Variables
  void Assign(Symbol* var, int value);
  void Decl(Symbol* var);
  int Value(Symbol* var);
  
  void Visit(Class* class_decl) override;
  void Visit(ClassMethod* method) override;
  void Visit(ClassField* field) override;
  void Visit(ProgramBody* body) override;
  void Visit(MainClass* main_class) override;
  
  void Visit(Program *program) override;
  
  void Visit(Expr::BinaryOp* binary_op) override;
  void Visit(Expr::Const* const_expr) override;
  void Visit(Expr::Id* rvalue) override;
  void Visit(Expr::This* this_expr) override;
  void Visit(Expr::UnaryOp* unary_op) override;
  void Visit(Expr::Call* call) override;
  void Visit(Expr::New* new_stmt) override;
  
  void Visit(Stmt::Assign* assn) override;
  void Visit(Stmt::Cond* cond) override;
  void Visit(Stmt::Print* print) override;
  void Visit(Stmt::Ret* ret) override;
  void Visit(Stmt::List* list) override;
  void Visit(Stmt::VarDecl* var_decl) override;
  void Visit(Stmt::ScopedList* scoped_list) override;
 
 private:
  std::unordered_map<std::string, int> vars_{};
  int return_value_{0};
  int temp_register_{0};
};
  
} // namespace Visitor