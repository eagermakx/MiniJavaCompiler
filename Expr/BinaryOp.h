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
    Div,
    GT,
    LT,
    LE,
    GE,
    E,
    NE
  };
  
  ExprBinOp BinOpByType(BinOperationType type);
  
  class BinaryOp : public Expr::Base {
   public:
    BinaryOp(BinOperationType type, Expr::Base* left, Expr::Base* right)
      : op(BinOpByType(type)), operation_type(type), left(left), right(right) {}
      
    ~BinaryOp() override = default;
    
    static BinaryOp* Add(Expr::Base* left, Expr::Base* right);
    static BinaryOp* Sub(Expr::Base* left, Expr::Base* right);
    static BinaryOp* Mul(Expr::Base* left, Expr::Base* right);
    static BinaryOp* Div(Expr::Base* left, Expr::Base* right);
    static BinaryOp* GT(Expr::Base* left, Expr::Base* right);
    static BinaryOp* LT(Expr::Base* left, Expr::Base* right);
    static BinaryOp* GE(Expr::Base* left, Expr::Base* right);
    static BinaryOp* LE(Expr::Base* left, Expr::Base* right);
    static BinaryOp* E(Expr::Base* left, Expr::Base* right);
    static BinaryOp* NE(Expr::Base* left, Expr::Base* right);
 
    void Accept(Visitor::Base* visitor) override;
 
   public:
    Expr::Base* left;
    Expr::Base* right;
    
    BinOperationType operation_type;
    ExprBinOp op;
  };
  
  bool IsBoolOperation(BinOperationType type);
}

