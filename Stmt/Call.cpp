//
// Created by Igor Maximov on 11.05.2020.
//

#include "Call.h"

Stmt::Call::Call(Expr::Id *id, std::string method) : method(std::move(method)), id(id) {
}

void Stmt::Call::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}
