//
// Created by Igor Maximov on 02.08.2020.
//

#include "BasicBlockScheduling.h"
#include "Visitors/NodeTraits.h"

namespace IR {

using namespace Visitor;

std::unordered_map<std::string, IR::BasicBlock> BasicBlocksSplit(const std::unordered_map<std::string, std::vector<IR::BaseStm*>>& linearizer_output) {
  NodeTraits traits;
  BasicBlock* current_block = nullptr;
  std::vector<IR::BasicBlock> blocks;
  
  for (auto [method_name, statements] : linearizer_output) {
    for (size_t i = 0; i < statements.size(); ++i) {
      IR::BaseStm *current_stm = statements[i];
      bool block_finished = false;
    
      if (traits.Type(current_stm) == NodeTraits::NodeType::SetLabel) {
        // Currently building a block
        if (current_block) {
          auto *setlabel_stm = dynamic_cast<IR::SetLabel *>(current_stm);
          current_block->AddStm(new IR::Jump(setlabel_stm->label_));
          current_block->SetType(BasicBlock::BlockType::jump);
          blocks.emplace_back(std::move(*current_block));
        }
        
        // Start a new block with that label
        current_block = new IR::BasicBlock();
      }
      
      if (current_block) {
        current_block->AddStm(current_stm);
      }
      
      if (traits.Type(current_stm) == NodeTraits::NodeType::Jump) {
        if (!current_block) {
          std::cerr << "Jump instruction out of the block" << std::endl;
          exit(1);
        }
      
        block_finished = true;
        current_block->SetType(BasicBlock::BlockType::jump);
      } else if (traits.Type(current_stm) == NodeTraits::NodeType::CJump) {
        if (!current_block) {
          std::cerr << "CJump instruction out of the block" << std::endl;
          exit(1);
        }
      
        block_finished = true;
        current_block->SetType(BasicBlock::BlockType::cjump);
      }
      
      if (block_finished) {
        blocks.emplace_back(std::move(*current_block));
        current_block = nullptr;
      }
    
      // last statement
      if (i == statements.size() - 1) {
        IR::Label done("__" + method_name + "_done");
        
        if (!current_block) {
          current_block = new IR::BasicBlock();
          current_block->AddStm(current_stm);
        }
  
        // assert(traits.Type(current_stm) == NodeTraits::NodeType::SetLabel);
  
        current_block->SetType(BasicBlock::BlockType::jump);
        current_block->AddStm(new IR::Jump(done));
        blocks.emplace_back(std::move(*current_block));
        current_block = nullptr;
      }
    }
  }
  
  std::unordered_map<std::string, IR::BasicBlock> result;
  
  for (auto& block : blocks) {
    result.emplace(block.GetLabelName(), std::move(block));
  }
  
  return result;
}

void TraceReschedule_impl(const std::string& label,
                          BlockMapping& blocks,
                          std::unordered_map<std::string, bool>& used,
                          std::unordered_map<std::string, bool>& cjumped,
                          std::vector<IR::BasicBlock>& answer)
{
  if (used[label] || !blocks[label].IsComplete()) {
    return;
  }
  
  auto& block = blocks[label];
  answer.push_back(block);
  used[label] = true;
  
  if (block.IsCondJump() || (!block.IsCondJump() && !cjumped[block.GetJumpLabel()])) {
    if (block.IsCondJump()) {
      auto [label_true, label_false] = block.GetCJumpLabels();
      TraceReschedule_impl(label_false, blocks, used, cjumped, answer);
      TraceReschedule_impl(label_true, blocks, used, cjumped, answer);
    } else {
      TraceReschedule_impl(block.GetJumpLabel(), blocks, used, cjumped, answer);
    }
  }
}

void TraceReschedule_fill_maps(std::unordered_map<std::string, bool>& used,
                               std::unordered_map<std::string, bool>& cjumped,
                               int& jumped,
                               BlockMapping& map) {
  for (auto& [label, block] : map) {
    used[label] = false;
    cjumped[label] = false;
  }
  
  for (auto& [label, block] : map) {
    if (block.IsComplete()) {
      if (block.IsCondJump()) {
        auto [label_true, label_false] = block.GetCJumpLabels();
        cjumped[label_false] = true;
      } else {
        ++jumped;
      }
    }
  }
}

std::vector<IR::BasicBlock> TraceReschedule(BlockMapping map, const std::vector<std::string>& method_labels) {
  std::unordered_map<std::string, bool> used;
  std::unordered_map<std::string, bool> cjumped;
  int jumped = 0;
  TraceReschedule_fill_maps(used, cjumped, jumped, map);
  
  std::vector<IR::BasicBlock> answer;
  
  for (auto& label : method_labels) {
    TraceReschedule_impl(label, map, used, cjumped, answer);
  }
  
  return answer;
}

std::vector<std::string> GetMethodLabels(const IR::Visitor::Linearizer::List& lin_out) {
  std::vector<std::string> ans;
  
  for (auto& [label, stmts] : lin_out) {
    ans.push_back(label);
  }
  
  return ans;
}

}
