#pragma once

#include "types/LogicOpType.h"

namespace IR {

class CJump : public BaseStm {
 public:
  CJump(LogicOpType o, BaseExp* lhs, BaseExp* rhs, Label ltrue, Label lfalse)
      : o(o), lhs(lhs), rhs(rhs), ltrue(ltrue), lfalse(lfalse) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  LogicOpType o;
  BaseExp* lhs;
  BaseExp* rhs;
  Label ltrue;
  Label lfalse;
};

} // namespace IR