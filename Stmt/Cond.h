//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

#include "Stmt.h"
#include "Expr/Expr.h"

namespace Stmt {
  class Cond : public Stmt::Base {
   public:
    Cond(Expr::Base* cond, Stmt::Base* stmt_true, Stmt::Base* stmt_false)
        : condition(cond), stmt_true(stmt_true), stmt_false(stmt_false) {}
  
    void Accept(Visitor::Base *visitor) override;
 
   public:
    Expr::Base* condition;
    Stmt::Base* stmt_true;
    Stmt::Base* stmt_false;
  };
}

