#pragma once

namespace IR {

class Move : public BaseStm {
 public:
  Move(BaseExp* to, BaseExp* from) : from_(from), to_(to) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  BaseExp* from_;
  BaseExp* to_;
};

} // namespace IR