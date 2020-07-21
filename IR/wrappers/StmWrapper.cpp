//
// Created by Igor Maximov on 19.07.2020.
//

#include "StmWrapper.h"
#include "IR/ir_nodes.h"

namespace IR {

StmWrapper::StmWrapper(BaseStm *stm) : stm_(stm) {}

IR::BaseExp *IR::StmWrapper::ToExp() {
  std::cerr << "[!] stm -> exp, invalid\n"; exit(1);
  return nullptr;
}

IR::BaseStm *IR::StmWrapper::ToStm() {
  return stm_;
}

IR::BaseStm *IR::StmWrapper::ToCond(IR::Label true_label, IR::Label false_label) {
  std::cerr << "[!] stm -> cond, invalid\n"; exit(1);
  return nullptr;
}

}
