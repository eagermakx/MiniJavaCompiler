#pragma once

namespace IR {

class Const : public BaseExp {
 public:
  explicit Const(int val) : val_(val) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  const int val_;
};

} // namespace IR