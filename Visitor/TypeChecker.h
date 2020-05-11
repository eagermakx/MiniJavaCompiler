//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once
#include "Visitor.h"
#include "SymbolTable/Table.h"

#include <unordered_map>

namespace Visitor {

class TypeChecker : public Visitor::Base {
 public:
  explicit TypeChecker(Table* table) : symbol_table_(table) {}
  
  void Run(Program* program);
  
  void Visit(Program* program) override;
  
  void Visit(Class* class_decl) override;
  void Visit(ClassMethod* method) override;
  void Visit(ClassField* field) override;
  void Visit(ProgramBody* body) override;
  void Visit(MainClass* main_class) override;
  
  void Visit(Expr::BinaryOp* binary_op) override;
  void Visit(Expr::Const* const_expr) override;
  void Visit(Expr::Id* rvalue) override;
  void Visit(Expr::This* this_expr) override;
  void Visit(Expr::UnaryOp* unary_op) override;
  void Visit(Expr::Call* call) override;
  void Visit(Expr::New* new_expr) override;
  
  void Visit(Stmt::Assign* assn) override;
  void Visit(Stmt::Cond* cond) override;
  void Visit(Stmt::Print* print) override;
  void Visit(Stmt::Ret* ret) override;
  void Visit(Stmt::List* list) override;
  void Visit(Stmt::VarDecl* var_decl) override;
  void Visit(Stmt::ScopedList* scoped_list) override;
  void Visit(Stmt::ExprStmt* stmt_expr) override;
  
  void AddVariable(Symbol* symbol, Type* type);
  Type* GetVariableType(Symbol* symbol);
  
 private:
  std::unordered_map<Symbol, Type*> symbol_types;
  ClassMethod* current_method{nullptr};
  Table* symbol_table_;
};

}
