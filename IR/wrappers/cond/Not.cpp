//
// Created by Igor Maximov on 19.07.2020.
//

#include "Not.h"

IR::Not::Not(IR::SubtreeWrapper *exp) : exp_(exp) {}

IR::BaseStm *IR::Not::ToCond(IR::Label ltrue, IR::Label lfalse) {
  return exp_->ToCond(lfalse, ltrue);
}
