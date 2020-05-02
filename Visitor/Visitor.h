//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "ast_decl.h"

namespace Visitor {
  class Base {
   public:
    virtual void Visit(Program* program) = 0;
    virtual void Visit(Entity::Const* constant) = 0;
    virtual void Visit(Entity::Id* ident) = 0;
    virtual void Visit(Expr::BinaryOp* binary_op) = 0;
    virtual void Visit(Expr::lvalue* lvalue) = 0;
    virtual void Visit(Expr::rvalue* rvalue) = 0;
    virtual void Visit(Expr::UnaryOp* unary_op) = 0;
    virtual void Visit(Stmt::Assign* assn) = 0;
    virtual void Visit(Stmt::Cond* cond) = 0;
    virtual void Visit(Stmt::Print* print) = 0;
    virtual void Visit(Stmt::Ret* ret) = 0;
    virtual void Visit(Stmt::List* list) = 0;
    virtual void Visit(Stmt::VarDecl* var_decl) = 0;
  };
}