//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Stmt/Stmt.h"
#include "Expr/Id.h"
#include "Expr/Expr.h"
#include "Visitor/Visitor.h"

namespace Stmt {
  class Assign : public Stmt::Base {
   public:
    Assign(Expr::Id* id, Expr::Base* expr) : lhs(id), rhs(expr) {}
  
    void Accept(Visitor::Base *visitor) override;
 
   public:
    Expr::Id* lhs;
    Expr::Base* rhs;
  };
}
