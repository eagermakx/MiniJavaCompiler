//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Expr.h"
#include <functional>

using ExprBinOp = std::function<int(int, int)>;

namespace Expr {
  enum BinOperationType {
    Add,
    Sub,
    Mul,
    Div
  };
  
  ExprBinOp BinOpByType(BinOperationType type);
  
  class BinaryOp : public Expr::Base {
   public:
    BinaryOp(BinOperationType type, Expr::Base* left, Expr::Base* right)
      : op(BinOpByType(type)), type(type), left(left), right(right) {}
      
    ~BinaryOp() override = default;
    
    static BinaryOp* Add(Expr::Base* left, Expr::Base* right);
    static BinaryOp* Sub(Expr::Base* left, Expr::Base* right);
    static BinaryOp* Mul(Expr::Base* left, Expr::Base* right);
    static BinaryOp* Div(Expr::Base* left, Expr::Base* right);
 
    void Accept(Visitor::Base* visitor) override;

    int eval() const override;
 
   public:
    Expr::Base* left;
    Expr::Base* right;
    
    BinOperationType type;
    ExprBinOp op;
  };
  
}

