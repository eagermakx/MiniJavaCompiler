//
// Created by Igor Maximov on 09.05.2020.
//

#include "This.h"

void Expr::This::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}
