//
// Created by Igor Maximov on 31.07.2020.
//

#include "Block.h"

IR::Block::Block(IR::SetLabel* set_label_stmt, BlockType type, Seq* start, Seq* end)
    : label(set_label_stmt->label_), start_(start), end_(end), type(type) {
}

void IR::Block::SetNext(IR::Block *next) {
  assert(type == BlockType::jump);
  
  dynamic_cast<IR::Jump*>(jump)->label_ = next->label;
  end_->second_ = next->start_;
}

void IR::Block::SetCondNext(IR::Block *t, IR::Block *f) {
  assert(type == BlockType::cjump);
  
  dynamic_cast<IR::CJump*>(jump)->ltrue = t->label;
  dynamic_cast<IR::CJump*>(jump)->lfalse = f->label;
}

void IR::Block::SetLabel(IR::Label l) {
  label = std::move(l);
}

std::string IR::Block::ToString() const {
  std::string output = "[ " + label.ToString() + ", ";
  
  if (type == BlockType::none) {
    std::cerr << "type 'BlockType::none' of an existing block" << std::endl;
    exit(1);
  } else if (type == BlockType::jump) {
    output += "jump to " + dynamic_cast<IR::Jump*>(end_->first_)->label_.ToString() + " ]";
  } else {
    // CJump
    auto* cjump = dynamic_cast<IR::CJump*>(end_->first_);
    output += "cjump t: " + cjump->ltrue.ToString() + ", f: " + cjump->lfalse.ToString() + " ]";
  }
  
  return output;
}
