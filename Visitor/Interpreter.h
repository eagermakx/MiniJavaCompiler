//
// Created by Igor Maximov on 02.05.2020.
//

#pragma once

#include "Visitor.h"

#include <ast_decl.h>
#include <SymbolTable/Symbol.h>
#include <unordered_map>
#include <Functions/CallFrame.h>

namespace Visitor {

class Interpreter : public Visitor::Base {
 public:
  Interpreter() = default;
  
  int Run(Program *program);
  
  int CalcExpr(Expr::Base* expr);
  
  // Variables
  void Assign(Symbol* var, std::shared_ptr<Object> value);
  void Decl(Symbol* var);
  std::shared_ptr<Object> Value(Symbol* var);
  
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
 
 private:
  std::shared_ptr<Object> CallMethod(Class* cls, ClassMethod* method, CallParamList *params, std::shared_ptr<Object> self = nullptr);
  
  std::vector<std::shared_ptr<Object>> EvaluateParams(CallParamList* params);
  
  std::unordered_map<std::string, int> vars_{};
  int return_value_{0};
  int temp_register_{0};
  
  std::shared_ptr<Object> temp_object_;
  
  CallFrame* current_frame{nullptr};
};
  
} // namespace Visitor