//
// Created by Igor Maximov on 11.05.2020.
//

#include "Call.h"

namespace Expr {

Call::Call(Expr::Id *id, std::string method) : method(std::move(method)), id(id) {
}

void Call::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

}