#pragma once

#include "BaseExp.h"
#include "BaseStm.h"

namespace IR {

class Eseq : public BaseExp {
 public:
  Eseq(BaseStm* stm, BaseExp* exp) : stm_(stm), exp_(exp) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  BaseStm* stm_;
  BaseExp* exp_;
};

} // namespace IR