//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once

#include "BaseCondWrapper.h"
#include "IR/wrappers/SubtreeWrapper.h"

namespace IR {

class OrderRelation : public BaseCondWrapper {
 public:
  OrderRelation(LogicOpType o, BaseExp* lhs, BaseExp* rhs);
  BaseStm* ToCond(Label ltrue, Label lfalse) override;
 
 private:
  LogicOpType o;
  BaseExp* lhs_;
  BaseExp* rhs_;
};

}
