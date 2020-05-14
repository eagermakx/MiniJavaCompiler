//
// Created by Igor Maximov on 11.05.2020.
//

#include "Call.h"

namespace Expr {

Call::Call(Expr::Base* expr, std::string method, CallParamList* passed)
    : method_name(std::move(method)), expr(expr), passed_params(passed) {
}

void Call::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

}