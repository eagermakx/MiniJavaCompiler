//
// Created by Igor Maximov on 04.05.2020.
//

#include <Stmt/ScopedList.h>
#include <Entity/Id.h>
#include "SymbolTableBuilder.h"
#include "Program.h"
#include "SymbolTable/Symbol.h"

#include "log.h"
#include "ast.h"

void Visitor::SymbolTableBuilder::Process(Program *program) {
  Visit(program);
}

void Visitor::SymbolTableBuilder::Visit(Program *program) {
  auto* global = new Scope(nullptr);
  global->SetLabel("main");
  auto* main = new ScopeTree(global);
  trees_.emplace_back(main);
  current_tree_ = main;
  
  scopes_.push(global);
  
  Visit(program->list);
  
  scopes_.pop();
}

void Visitor::SymbolTableBuilder::Visit(Stmt::ScopedList *scoped_list) {
  Scope* current_layer = scopes_.top();
  auto* new_layer = new Scope(current_layer);
  current_layer->AddChild(new_layer);
  
  scopes_.push(new_layer);
  
  // LOG("Pushed a scope! id = " << new_layer->GetId());
  
  Visit(scoped_list->list);
  
  for (auto& var : scopes_.top()->variables_) {
    current_tree_->scope_shadowing_map_.at(var).pop();
  }
  scopes_.pop();
  
  // LOG("Popped a scope! current id = " << scopes_.top()->GetId());
}

void Visitor::SymbolTableBuilder::Visit(Stmt::List *list) {
  for (auto* stmt : list->list) {
    stmt->Accept(this);
  }
}

void Visitor::SymbolTableBuilder::Visit(Entity::Const *that) {
  UNREACHABLE("SymbolTableBuilder::Visit(Entity::Const*)");
}

void Visitor::SymbolTableBuilder::Visit(Entity::Id *that) {
  UNREACHABLE("SymbolTableBuilder::Visit(Entity::Id*)");
}

void Visitor::SymbolTableBuilder::Visit(Expr::BinaryOp *that) {
  that->left->Accept(this);
  that->right->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Expr::lvalue *that) {
  FindDefinition(that->id);
}

void Visitor::SymbolTableBuilder::Visit(Expr::rvalue *that) {
  switch (that->type) {
    case Expr::rvalue::Type::ident:
      FindDefinition(that->id);
      break;
    case Expr::rvalue::Type::constant:
      // Do nothing
      break;
    default: UNREACHABLE("");
  }
}

void Visitor::SymbolTableBuilder::Visit(Expr::UnaryOp *that) {
  that->expr->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Stmt::Assign *that) {
  that->expr->Accept(this);
  that->lvalue->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Stmt::Cond *that) {
  that->condition->Accept(this);
  if (that->stmt_true) {
    that->stmt_true->Accept(this);
  }
  if (that->stmt_false) {
    that->stmt_false->Accept(this);
  }
}

void Visitor::SymbolTableBuilder::Visit(Stmt::Print *that) {
  that->expr->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Stmt::Ret *that) {
  that->expr->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Stmt::VarDecl *that) {
  Scope* current_scope = scopes_.top();
  std::string var_name = that->ident->identifier;
  
  // Will terminate if that variable was defined previously
  // in the same scope
  current_tree_->DefineVariable(current_scope, var_name);
  that->ident->symbol = new Symbol(current_scope, var_name);
}

void Visitor::SymbolTableBuilder::FindDefinition(Entity::Id *id) {
  std::string& var = id->identifier;
  
  // Might be defined out of current scope.
  // If was not found, terminates
  Scope* def_scope = current_tree_->TopDefinitionLayer(var);
  id->symbol = new Symbol(def_scope, var);
  
  // LOG("Found definition for \'" << id->symbol->GetName() << "\' at layer" << scopes_.top()->GetId());
  // LOG("Stack size = " << current_tree_->scope_shadowing_map_.at(var).size());
}

