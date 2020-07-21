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
  return new IR::CJump(LogicOpType::E, exp_, new IR::Const(0), false_label, true_label);
}

ExpWrapper::ExpWrapper(BaseExp *exp) : exp_(exp) {
}

}
