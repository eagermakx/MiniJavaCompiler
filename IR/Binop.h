#pragma once

#include "ir_nodes.h"
#include "types/BinaryOp.h"

namespace IR {

class Binop : public BaseExp {
 public:
  Binop(BinaryOpType o, BaseExp* lhs, BaseExp* rhs) : o(o), lhs(lhs), rhs(rhs) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  BinaryOpType o;
  BaseExp* lhs;
  BaseExp* rhs;
};

} // namespace IR