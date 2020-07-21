//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once

#include "BaseCondWrapper.h"
#include "IR/wrappers/SubtreeWrapper.h"

namespace IR {

class And : public BaseCondWrapper {
 public:
  And(SubtreeWrapper* lhs, SubtreeWrapper* rhs);
  BaseStm* ToCond(Label ltrue, Label lfalse) override;
 
 public:
  SubtreeWrapper* lhs;
  SubtreeWrapper* rhs;
};

}
