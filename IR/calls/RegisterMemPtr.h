//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once
#include "MemPtr.h"
#include "IR/generators/Temp.h"

namespace IR {

class RegisterMemPtr : public MemPtr {
 public:
  explicit RegisterMemPtr(const Temp& temp);
  BaseExp* ToExp() override;
 
 private:
  Temp temp_;
};

}
