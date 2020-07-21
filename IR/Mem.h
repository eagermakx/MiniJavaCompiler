#pragma once

#include "BaseExp.h"

namespace IR {

class Mem : public BaseExp {
 public:
  explicit Mem(BaseExp* exp) : exp_(exp) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  BaseExp* exp_;
};

} // namespace IR