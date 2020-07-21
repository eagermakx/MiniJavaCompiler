#pragma once

#include "generators/Temp.h"
#include "ir_nodes.h"

namespace IR {

class TempExp : public BaseExp {
 public:
  explicit TempExp(const Temp& temp) : temp_(temp) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  Temp temp_;
};

} // namespace IR