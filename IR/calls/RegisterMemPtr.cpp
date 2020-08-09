//
// Created by Igor Maximov on 19.07.2020.
//

#include <IR/TempExp.h>
#include "RegisterMemPtr.h"
#include <IR/Register.h>

IR::BaseExp *IR::RegisterMemPtr::ToExp() {
  return new Register(name_);
}
