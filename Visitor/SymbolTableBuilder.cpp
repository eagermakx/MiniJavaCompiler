//
// Created by Igor Maximov on 04.05.2020.
//

#include <Stmt/ScopedList.h>
#include <Expr/Id.h>
#include <Decl/MainClass.h>

#include "SymbolTableBuilder.h"
#include "Program.h"
#include "SymbolTable/Symbol.h"

#include "log.h"
#include "ast.h"

Visitor::SymbolTableBuilder::SymbolTableBuilder(Table *symbol_table) : symbol_table_(symbol_table) {
}

void Visitor::SymbolTableBuilder::Process(Program *program) {
  Visit(program);
  
  symbol_table_->PrintTable();
}

void Visitor::SymbolTableBuilder::Visit(Program *program) {
  
  for (auto* cls : program->classes) {
    cls->Accept(this);
    symbol_table_->AddClass(cls);
  }
  
  program->main_class->Accept(this);
  
  /*auto* global = new VariableScope(nullptr);
  global->SetLabel("main");
  auto* main = new ScopeTree(global);
  trees_.emplace_back(main);
  current_tree_ = main;
  
  scopes_.push(global);
  
  auto* main_method = program->main_class->GetMainFunction();
  main_method->statements->Accept(this);
  
  scopes_.pop();*/
}

void Visitor::SymbolTableBuilder::Visit(Stmt::ScopedList *scoped_list) {
  VariableScope* current_layer = scopes_.top();
  
  auto* new_scope = new VariableScope(current_layer);
  scoped_list->scope = new_scope;
  
  // current_layer->AddChild(new_scope);
  
  scopes_.push(new_scope);
  
  LOG("Pushed a scope! id = " << new_scope->GetId());
  
  Visit(scoped_list->list);
  
  for (auto& var : scopes_.top()->variables_) {
    current_tree_->scope_shadowing_map_.at(var).pop();
  }
  
  scopes_.pop();
  
  LOG("Popped a scope! current id = " << scopes_.top()->GetId());
}

void Visitor::SymbolTableBuilder::Visit(Stmt::List *list) {
  for (auto* stmt : list->list) {
    stmt->Accept(this);
  }
}

void Visitor::SymbolTableBuilder::Visit(Expr::Const *that) {
}

void Visitor::SymbolTableBuilder::Visit(Expr::Id *that) {
  FindDefinition(that);
}

void Visitor::SymbolTableBuilder::Visit(Expr::BinaryOp *that) {
  that->left->Accept(this);
  that->right->Accept(this);
}

/*void Visitor::SymbolTableBuilder::Visit(Expr::lvalue *that) {
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
}*/

void Visitor::SymbolTableBuilder::Visit(Expr::UnaryOp *that) {
  that->expr->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Stmt::Assign *that) {
  that->rhs->Accept(this);
  that->lhs->Accept(this);
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
  VariableScope* current_scope = scopes_.top();
  std::string var_name = that->var_id->identifier;
  
  // Will terminate if that variable was defined previously
  // in the same scope
  current_tree_->DefineVariable(current_scope, var_name);
  
  that->var_id->symbol = new Symbol(current_scope, var_name);
  that->var_id->symbol->AssignLabel(current_scope->GetFullLabel() + "::" + var_name);
}

void Visitor::SymbolTableBuilder::FindDefinition(Expr::Id *id) {
  std::string& var = id->identifier;
  
  // Might be defined out of current scope.
  // If was not found, terminates
  VariableScope* def_scope = current_tree_->TopDefinitionLayer(var);
  id->symbol = new Symbol(def_scope, var);
  id->symbol->AssignLabel(def_scope->GetFullLabel() + "::" + var);
  
  LOG("Found definition for \'" << id->symbol->GetName() << "\' at layer" << scopes_.top()->GetId());
  LOG("Stack size = " << current_tree_->scope_shadowing_map_.at(var).size());
}

void Visitor::SymbolTableBuilder::Visit(Class *cls) {
  for (auto* method : cls->methods) {
    method->Accept(this);
    symbol_table_->AddMethod(cls, method);
  }
}

void Visitor::SymbolTableBuilder::Visit(ClassMethod *method) {
  auto* initial_scope = new VariableScope(nullptr);
  initial_scope->SetLabel(method->name.c_str());
  
  auto* tree = new ScopeTree(initial_scope);
  // trees_.emplace_back(tree);
  current_tree_ = tree;
  
  scopes_.push(initial_scope);
  method->statements->Accept(this);
  scopes_.pop();
}

void Visitor::SymbolTableBuilder::Visit(ClassField *field) {
  // Do nothing...
}

void Visitor::SymbolTableBuilder::Visit(ProgramBody *body) {
  UNREACHABLE("SymbolTableBuilder::Visit(ProgramBody*)");
}

void Visitor::SymbolTableBuilder::Visit(Expr::This *this_expr) {
  LOG("this expr");
}

void Visitor::SymbolTableBuilder::Visit(MainClass *main_class) {
  main_class->GetMainFunction()->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Expr::New *new_expr) {
  new_expr->cls = symbol_table_->FindClass(new_expr->class_name);
}

void Visitor::SymbolTableBuilder::Visit(Expr::Call *call) {
  call->expr->Accept(this);
}

void Visitor::SymbolTableBuilder::Visit(Stmt::ExprStmt *stmt_expr) {
  stmt_expr->expr->Accept(this);
}
