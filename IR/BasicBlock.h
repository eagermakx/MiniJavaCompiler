//
// Created by Igor Maximov on 03.08.2020.
//

#pragma once
#include "ir_nodes.h"

namespace IR {

class BasicBlock {
 public:
  enum class BlockType { none, jump, cjump };
  
  BasicBlock() = default;
  BasicBlock(int start, int end, const std::vector<IR::BaseStm*>& superstring);
  
  void SetType(BlockType type);
  void AddStm(IR::BaseStm* stm);
  
  bool IsCondJump() const;
  bool IsComplete() const;
  
  std::pair<std::string, std::string> GetCJumpLabels() const;
  std::string GetJumpLabel() const;
  
  std::string ToString() const;
  std::string GetLabelName() const;
 
 private:
  std::vector<IR::BaseStm *> statements_;
  BlockType type_{BlockType::none};
};

}