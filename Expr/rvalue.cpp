//
// Created by Igor Maximov on 04.04.2020.
//

#include "rvalue.h"

namespace Expr {
  rvalue::rvalue(Entity::Id *id) : id(id), literal(nullptr), type(rvalue::Type::ident) {}
  
  rvalue::rvalue(Entity::Const *literal) : id(nullptr), literal(literal), type(rvalue::Type::constant) {}
  
  void rvalue::Accept(Visitor::Base *visitor) {
    visitor->Visit(this);
  }
  
  int rvalue::eval() const {
    return 0;
  }
}
