//
// Created by Igor Maximov on 20.07.2020.
//

#pragma once
#include "MemPtr.h"

namespace IR {

class AbsMemPtr : public MemPtr {
 public:
  AbsMemPtr();
  ~AbsMemPtr() override = default;
  BaseExp* ToExp() override;
 
 private:
  void* ptr = nullptr;
};

}
