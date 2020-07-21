//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once

#include "BaseCondWrapper.h"
#include "IR/wrappers/SubtreeWrapper.h"

namespace IR {

class Or : public BaseCondWrapper {
 public:
  Or(SubtreeWrapper* lhs, SubtreeWrapper* rhs);
  BaseStm* ToCond(Label ltrue, Label lfalse) override;
 
 private:
  SubtreeWrapper* lhs_;
  SubtreeWrapper* rhs_;
};

}
