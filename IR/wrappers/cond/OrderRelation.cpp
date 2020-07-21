#include "OrderRelation.h"

IR::OrderRelation::OrderRelation(LogicOpType o, BaseExp *lhs, BaseExp *rhs) : o(o), lhs_(lhs), rhs_(rhs) {}

IR::BaseStm* IR::OrderRelation::ToCond(Label ltrue, Label lfalse) {
  return new CJump(o, lhs_, rhs_, ltrue, lfalse);
}
