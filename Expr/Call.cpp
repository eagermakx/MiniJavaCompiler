//
// Created by Igor Maximov on 11.05.2020.
//

#include "Call.h"

namespace Expr {

Call::Call(Expr::Base* expr, std::string method) : method_name(std::move(method)), expr(expr) {
}

void Call::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

}