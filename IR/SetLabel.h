#pragma once

#include "generators/Label.h"

namespace IR {

class SetLabel : public BaseStm {
 public:
  explicit SetLabel(Label label) : label_(std::move(label)) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  Label label_;
};

} // namespace IR