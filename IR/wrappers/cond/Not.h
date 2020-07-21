#pragma once

#include "BaseCondWrapper.h"

namespace IR {

class Not : public BaseCondWrapper {
 public:
  explicit Not(SubtreeWrapper* exp);
  BaseStm* ToCond(Label ltrue, Label lfalse) override;
  
 private:
  SubtreeWrapper* exp_;
};

}
