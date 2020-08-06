//
// Created by Igor Maximov on 03.08.2020.
//

#include "BasicBlock.h"

IR::BasicBlock::BasicBlock(int start, int end, const std::vector<IR::BaseStm*>& superstring) {
  for (int i = start; i < end; ++i) {
    statements_.emplace_back(superstring[i]);
  }
}

void IR::BasicBlock::SetType(BlockType type) {
  type_ = type;
}

void IR::BasicBlock::AddStm(IR::BaseStm *stm) {
  statements_.push_back(stm);
}

std::string IR::BasicBlock::ToString() const {
  IR::Label label = dynamic_cast<IR::SetLabel*>(statements_[0])->label_;
  std::string output = "[ " + label.ToString() + ", ";
  
  size_t end = statements_.size() - 1;
  IR::BaseStm* last_stm = statements_[end];
  
  if (type_ == BlockType::none) {
    std::cerr << "type 'BlockType::none' of an existing block" << std::endl;
    exit(1);
  } else if (type_ == BlockType::jump) {
    output += "jump to " + dynamic_cast<IR::Jump*>(last_stm)->label_.ToString() + " ]";
  } else {
    // CJump
    auto* cjump = dynamic_cast<IR::CJump*>(last_stm);
    output += "cjump t: " + cjump->ltrue.ToString() + ", f: " + cjump->lfalse.ToString() + " ]";
  }
  
  return output;
}

std::string IR::BasicBlock::GetLabelName() const {
  return dynamic_cast<IR::SetLabel*>(statements_[0])->label_.ToString();
}

bool IR::BasicBlock::IsCondJump() const {
  return type_ == BlockType::cjump;
}

std::pair<std::string, std::string> IR::BasicBlock::GetCJumpLabels() const {
  assert(IsCondJump());
  
  auto* cjump = dynamic_cast<IR::CJump*>(statements_[statements_.size() - 1]);
  return { cjump->ltrue.ToString(), cjump->lfalse.ToString() };
}

std::string IR::BasicBlock::GetJumpLabel() const {
  assert(!IsCondJump());
  
  auto* jump = dynamic_cast<IR::Jump*>(statements_[statements_.size() - 1]);
  return jump->label_.ToString();
}

bool IR::BasicBlock::IsComplete() const {
  return type_ != BlockType::none;
}
