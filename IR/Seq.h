#pragma once

namespace IR {

class Seq : public BaseStm {
 public:
  Seq(BaseStm* first, BaseStm* second) : first_(first), second_(second) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  BaseStm* first_;
  BaseStm* second_;
};

} // namespace IR