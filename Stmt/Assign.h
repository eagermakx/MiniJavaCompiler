//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Stmt/Stmt.h"
#include "Entity/Id.h"
#include "Expr/Expr.h"
#include "Visitor/Visitor.h"
#include "Expr/lvalue.h"

namespace Stmt {
  class Assign : public Stmt::Base {
   public:
    Assign(Expr::lvalue* lvalue, Expr::Base* expr) : lvalue(lvalue), expr(expr) {}
  
    void Accept(Visitor::Base *visitor) override;
 
   public:
    Expr::lvalue* lvalue;
    Expr::Base* expr;
  };
}
