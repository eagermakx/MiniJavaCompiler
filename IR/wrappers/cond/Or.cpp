//
// Created by Igor Maximov on 19.07.2020.
//

#include "Or.h"

IR::Or::Or(IR::SubtreeWrapper *lhs, IR::SubtreeWrapper *rhs) : rhs_(rhs), lhs_(lhs) {}

IR::BaseStm *IR::Or::ToCond(IR::Label ltrue, IR::Label lfalse) {
  Label intermediate;
  
  return new Seq(lhs_->ToCond(ltrue, intermediate), new Seq(new SetLabel(intermediate), rhs_->ToCond(ltrue, lfalse)));
}
