//
// Created by Igor Maximov on 02.05.2020.
//

#pragma once

#include "Visitor.h"
#include <ast_decl.h>
#include <unordered_map>
#include <IR/ir_nodes.h>
#include <SymbolTable/Symbol.h>
#include <IR/calls/Frame.h>
#include <IR/wrappers/SubtreeWrapper.h>

using IRMapping = std::unordered_map<std::string, IR::BaseStm*>;
using FrameMap = std::unordered_map<Symbol, IR::Frame*>;

namespace Visitor {

class IRTranslator : public Visitor::Base {
 public:
  IRTranslator() = default;
  
  int Run(Program *program);
  
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
  void Visit(Expr::New* new_expr) override;
  
  void Visit(Stmt::Assign* assn) override;
  void Visit(Stmt::Cond* cond) override;
  void Visit(Stmt::Print* print) override;
  void Visit(Stmt::Ret* ret) override;
  void Visit(Stmt::List* list) override;
  void Visit(Stmt::VarDecl* var_decl) override;
  void Visit(Stmt::ScopedList* scoped_list) override;
  void Visit(Stmt::ExprStmt* stmt_expr) override;
 
  IRMapping& GetMapping();
  
 private:
  IRMapping method_trees_;
  FrameMap frames_;
  
  IR::SubtreeWrapper* Translate(BaseNode* that);
  
  IR::SubtreeWrapper* temp_value_;
  
  IR::Frame* current_frame_;
};

} // namespace Visitor