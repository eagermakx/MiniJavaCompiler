//
// Created by Igor Maximov on 31.07.2020.
//

#include "BlockBuilder.h"

void IR::Visitor::BlockBuilder::Visit(IR::Binop *binop) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Call *call) {
}

void IR::Visitor::BlockBuilder::Visit(IR::CJump *cjump) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Const *cnst) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Eseq *eseq) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Exp *exp) {
}

void IR::Visitor::BlockBuilder::Visit(IR::ExpList *exp_list) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Jump *jump) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Mem *mem) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Move *move) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Name *name) {
}

void IR::Visitor::BlockBuilder::Visit(IR::Seq *seq) {
  bool block_finished = false;
  Block::BlockType type = Block::BlockType::none;
  
  if (traits_.Type(seq->first_) == NodeTraits::NodeType::SetLabel) {
    // Currently building a block
    if (block_start_) {
      IR::BaseStm* right_chain = seq->second_;
      IR::SetLabel* setlabel_stm = dynamic_cast<IR::SetLabel *>(seq->first_);
      
      seq->first_ = new IR::Jump(setlabel_stm->label_);
      seq->second_ = new IR::Seq(setlabel_stm, right_chain);
      
      block_finished = true;
      type = Block::BlockType::jump;
    } else {
      block_start_ = seq;
    }
  } else if (traits_.Type(seq->first_) == NodeTraits::NodeType::Jump) {
    if (!block_start_) {
      std::cerr << "Jump instruction out of the block" << std::endl;
      exit(1);
    }
  
    block_finished = true;
    type = Block::BlockType::jump;
  } else if (traits_.Type(seq->first_) == NodeTraits::NodeType::CJump) {
    if (!block_start_) {
      std::cerr << "CJump instruction out of the block" << std::endl;
      exit(1);
    }
  
    block_finished = true;
    type = Block::BlockType::cjump;
  }
  
  
  if (block_finished) {
    auto *current_block = new IR::Block(
      BlockSetLabelStm(block_start_),
      type,
      block_start_,
      seq
    );
  
    previous_block_ = current_block;
    blocks_.emplace_back(current_block);
    block_start_ = nullptr;
  }
  
  if (traits_.Type(seq->second_) != NodeTraits::NodeType::Seq) {
    seq->second_ = Finalize(seq->second_, current_method_name_);
    return;
  }
  
  seq->second_->Accept(this);
}

void IR::Visitor::BlockBuilder::Visit(IR::SetLabel *set_label) {
}

void IR::Visitor::BlockBuilder::Visit(IR::TempExp *temp_expr) {
}

std::vector<IR::Block*>& IR::Visitor::BlockBuilder::Run(IRMapping method_trees) {
  blocks_.clear();
  
  for (auto& method : method_trees) {
    auto m_name = method.first;
    auto statements = method.second;
    
    if (traits_.Type(statements) != NodeTraits::NodeType::Seq) {
      method.second = Finalize(statements, m_name);
      continue;
    }
    
    current_method_name_ = m_name;
    statements->Accept(this);
  }
  
  return blocks_;
}

IR::Seq * IR::Visitor::BlockBuilder::Finalize(BaseStm *last_stm, const std::string &method_name) {
  IR::Label done("__" + method_name + "_done");
  auto* final_seq = new IR::Seq(new IR::Jump(done), new IR::SetLabel(done));
  auto* block = new IR::Block(
    BlockSetLabelStm(block_start_),
    IR::Block::BlockType::jump,
    block_start_,
    final_seq
  );
  
  blocks_.emplace_back(block);
  block_start_ = nullptr;
  
  return new IR::Seq(last_stm, final_seq);
}

IR::SetLabel *IR::Visitor::BlockBuilder::BlockSetLabelStm(IR::Seq *block_start) {
  return dynamic_cast<IR::SetLabel*>(block_start->first_);
}
