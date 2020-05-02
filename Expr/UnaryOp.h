//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Expr.h"
#include <functional>

namespace Expr {
  enum class UnOperationType {
    Not,
    Minus
  };
  
  using UnOp = std::function<int(int)>;
  
  UnOp UnOpByType(UnOperationType type);
  
  class UnaryOp : public Expr::Base {
   public:
    UnaryOp(UnOperationType type, Expr::Base* expr) : op(UnOpByType(type)), type(type), expr(expr) {}
    
    static UnaryOp* Not(Expr::Base* expr);
    static UnaryOp* Minus(Expr::Base* expr);
  
    int eval() const override;
  
    void Accept(Visitor::Base *visitor) override;
 
   public:
    UnOperationType type;
    UnOp op;
    Expr::Base* expr;
  };
}
