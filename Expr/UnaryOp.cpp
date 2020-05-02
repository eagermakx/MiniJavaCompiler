//
// Created by Igor Maximov on 04.04.2020.
//

#include "UnaryOp.h"

int Expr::UnaryOp::eval() const {
  return op(expr->eval());
}

void Expr::UnaryOp::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

Expr::UnaryOp *Expr::UnaryOp::Not(Expr::Base *expr) {
  return new UnaryOp(UnOperationType::Not, expr);
}

Expr::UnaryOp *Expr::UnaryOp::Minus(Expr::Base *expr) {
  return new UnaryOp(UnOperationType::Minus, expr);
}

Expr::UnOp Expr::UnOpByType(Expr::UnOperationType type) {
  switch(type) {
    case UnOperationType::Not:
      return [] (int x) -> int { return !x; };
    case UnOperationType::Minus:
      return [] (int x) -> int { return -x; };
  }
}
