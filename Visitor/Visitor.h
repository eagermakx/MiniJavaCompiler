//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "ast_decl.h"

namespace Visitor {
  class Base {
   public:
    virtual void Visit(Program* program) = 0;
    
    virtual void Visit(Class* class_decl) = 0;
    virtual void Visit(ClassMethod* method) = 0;
    virtual void Visit(ClassField* field) = 0;
    virtual void Visit(ProgramBody* body) = 0;
    
    virtual void Visit(Expr::BinaryOp* binary_op) = 0;
    virtual void Visit(Expr::Const* const_expr) = 0;
    virtual void Visit(Expr::Id* rvalue) = 0;
    virtual void Visit(Expr::This* this_expr) = 0;
    virtual void Visit(Expr::UnaryOp* unary_op) = 0;
    
    virtual void Visit(Stmt::Assign* assn) = 0;
    virtual void Visit(Stmt::Cond* cond) = 0;
    virtual void Visit(Stmt::Print* print) = 0;
    virtual void Visit(Stmt::Ret* ret) = 0;
    virtual void Visit(Stmt::List* list) = 0;
    virtual void Visit(Stmt::VarDecl* var_decl) = 0;
    virtual void Visit(Stmt::ScopedList* scoped_list) = 0;
  };
}