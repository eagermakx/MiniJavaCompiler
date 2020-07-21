//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once
#include "MemPtr.h"

namespace IR {

class FrameMemPtr : public MemPtr {
 public:
  FrameMemPtr(MemPtr* frame_ptr, int offset);
  ~FrameMemPtr() = default;
  BaseExp* ToExp() override;
 
 private:
  MemPtr* frame_ptr_;
  int offset_;
};

}
