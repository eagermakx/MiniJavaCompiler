#pragma once

namespace IR {

class Exp : public BaseStm {
 public:
  explicit Exp(BaseExp* exp) : exp_(exp) {}
  BaseExp* GetExpr() { return exp_; }
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
 
 public:
  BaseExp* exp_;
};

} // namespace IR