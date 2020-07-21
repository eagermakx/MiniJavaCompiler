//
// Created by Igor Maximov on 20.07.2020.
//

#include "FrameMemPtr.h"
#include "IR/ir_nodes.h"
#include "AbsMemPtr.h"


IR::AbsMemPtr::AbsMemPtr() {
}

IR::BaseExp *IR::AbsMemPtr::ToExp() {
  return new IR::Const(1000);
}
