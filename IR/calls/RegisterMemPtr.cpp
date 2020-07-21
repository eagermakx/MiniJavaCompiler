//
// Created by Igor Maximov on 19.07.2020.
//

#include <IR/TempExp.h>
#include "RegisterMemPtr.h"

IR::RegisterMemPtr::RegisterMemPtr(const Temp &temp) : temp_(temp) {
}

IR::BaseExp *IR::RegisterMemPtr::ToExp() {
  return new IR::TempExp(temp_);
}
