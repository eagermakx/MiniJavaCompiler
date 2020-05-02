//
// Created by Igor Maximov on 03.04.2020.
//

#include "BinaryOp.h"

ExprBinOp Expr::BinOpByType(Expr::BinOperationType type) {
  switch(type) {
    case BinOperationType::Add:
      return [] (int left, int right) -> int { return left + right; };
    case BinOperationType::Sub:
      return [] (int left, int right) -> int { return left - right; };
    case BinOperationType::Mul:
      return [] (int left, int right) -> int { return left * right; };
    case BinOperationType::Div:
      return [] (int left, int right) -> int { return left / right; };
    default:
      throw std::invalid_argument("Wrong operation type");
  }
}

void Expr::BinaryOp::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

int Expr::BinaryOp::eval() const {
  return op(left->eval(), right->eval());
}

Expr::BinaryOp *Expr::BinaryOp::Add(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::Add, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::Sub(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::Sub, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::Mul(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::Mul, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::Div(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::Div, left, right);
}

