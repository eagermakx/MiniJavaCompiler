//
// Created by Igor Maximov on 31.07.2020.
//

#include "IR/ir_nodes.h"

#pragma once

namespace IR {

class Block {
 public:
  enum class BlockType { none, jump, cjump };
  
 public:
  Block(IR::SetLabel* set_label_stmt, BlockType type, Seq* start, Seq* end);
  
  void SetNext(Block* next);
  void SetCondNext(Block* true_block, Block* false_block);
  void SetLabel(IR::Label label);
  std::string ToString() const;
 
 public:
  IR::BaseNode* jump = nullptr;
  BlockType type = BlockType::none;
  IR::Label label;
  
  IR::Seq* start_;
  IR::Seq* end_;
};

}
