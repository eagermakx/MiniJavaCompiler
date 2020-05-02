//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Stmt.h"
#include "Expr/Expr.h"

namespace Stmt {
  class Ret : public Stmt::Base {
   public:
    explicit Ret(Expr::Base *expr) : expr(expr) {}
    
    void Accept(Visitor::Base *visitor) override;
   
   public:
    Expr::Base *expr;
  };
}
