//
// Created by Igor Maximov on 19.07.2020.
//

#include "ExpWrapper.h"

namespace IR {

BaseExp* IR::ExpWrapper::ToExp() {
  return exp_;
}

BaseStm *IR::ExpWrapper::ToStm() {
  return new IR::Exp(exp_);
}

BaseStm* IR::ExpWrapper::ToCond(Label true_label, Label false_label) {
  return new IR::CJump(LogicOpType::NE, exp_, new IR::Const(0), true_label, false_label);
}

ExpWrapper::ExpWrapper(BaseExp *exp) : exp_(exp) {
}

}
