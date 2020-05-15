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
    case BinOperationType::E:
      return [] (int left, int right) -> int { return left == right; };
    case BinOperationType::NE:
      return [] (int left, int right) -> int { return left != right; };
    case BinOperationType::GT:
      return [] (int left, int right) -> int { return left > right; };
    case BinOperationType::LT:
      return [] (int left, int right) -> int { return left < right; };
    case BinOperationType::GE:
      return [] (int left, int right) -> int { return left >= right; };
    case BinOperationType::LE:
      return [] (int left, int right) -> int { return left <= right; };
    default:
      throw std::invalid_argument("Wrong operation type");
  }
}

void Expr::BinaryOp::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
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

Expr::BinaryOp *Expr::BinaryOp::GT(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::GT, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::LT(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::LT, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::GE(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::GE, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::LE(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::LE, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::E(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::E, left, right);
}

Expr::BinaryOp *Expr::BinaryOp::NE(Expr::Base *left, Expr::Base *right) {
  return new Expr::BinaryOp(BinOperationType::NE, left, right);
}

bool Expr::IsBoolOperation(Expr::BinOperationType type) {
  return (type == Expr::BinOperationType::E || type == Expr::BinOperationType::NE || type == Expr::BinOperationType::LT || type == Expr::BinOperationType::GT || type == Expr::BinOperationType::LE || type == Expr::BinOperationType::GE);
}
