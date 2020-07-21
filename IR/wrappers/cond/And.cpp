//
// Created by Igor Maximov on 19.07.2020.
//

#include "And.h"

IR::And::And(IR::SubtreeWrapper *lhs, IR::SubtreeWrapper *rhs) : rhs(rhs), lhs(lhs) {}

IR::BaseStm *IR::And::ToCond(IR::Label ltrue, IR::Label lfalse) {
  Label intermediate;
  
  return new Seq(lhs->ToCond(intermediate, lfalse), new Seq(new SetLabel(intermediate), rhs->ToCond(ltrue, lfalse)));
}
