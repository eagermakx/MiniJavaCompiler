//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once

#include "IR/BaseExp.h"
namespace IR {

class MemPtr {
 public:
  virtual ~MemPtr() = default;
  virtual BaseExp* ToExp() = 0;
};

}
