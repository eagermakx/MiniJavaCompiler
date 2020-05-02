//
// Created by Igor Maximov on 04.04.2020.
//

#include "lvalue.h"

namespace Expr {
  lvalue::lvalue(Entity::Id *id) : id(id) {}
  
  void lvalue::Accept(Visitor::Base *visitor) {
    visitor->Visit(this);
  }
  
  int lvalue::eval() const {
    return 0;
  }
}
