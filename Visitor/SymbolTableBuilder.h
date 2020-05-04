//
// Created by Igor Maximov on 04.05.2020.
//

#pragma once

#include "Visitor.h"
#include "ast_decl.h"
#include "SymbolTable/Scope.h"
#include "SymbolTable/ScopeTree.h"
#include "SymbolTable/Table.h"

#include <unordered_map>
#include <stack>

namespace Visitor {

class SymbolTableBuilder : public Visitor::Base {
 public:
  SymbolTableBuilder() = default;
  
  void Process(Program* program);
  
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
  void FindDefinition(Entity::Id* id);
  
 private:
  std::vector<ScopeTree*> trees_;
  ScopeTree* current_tree_{nullptr};
  std::stack<Scope*> scopes_;
};

} // namespace Visitor