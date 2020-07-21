//
// Created by Igor Maximov on 19.07.2020.
//

#include "FrameMemPtr.h"
#include "IR/ir_nodes.h"

IR::FrameMemPtr::FrameMemPtr(IR::MemPtr *frame_ptr, int offset) : frame_ptr_(frame_ptr), offset_(offset) {
}

IR::BaseExp *IR::FrameMemPtr::ToExp() {
  BaseExp* offset_exp;
  
  if (offset_ != 0) {
    offset_exp = new IR::Binop(BinaryOpType::PLUS, frame_ptr_->ToExp(), new Const(offset_));
  } else {
    offset_exp = frame_ptr_->ToExp();
  }
  
  return new IR::Mem(offset_exp);
}
