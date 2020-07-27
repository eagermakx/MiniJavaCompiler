//
// Created by Igor Maximov on 27.07.2020.
//

#include "Linearizer.h"
#include <iostream>

void IR::Visitor::Linearizer::Run(IRMapping &method_trees) {
  for (auto& tree : method_trees) {
    auto method_name = tree.first;
    IR::BaseStm* code = tree.second;
    
    code->Accept(this);
    tree.second = tos_stm_list_->Tree();
  }
}

void IR::Visitor::Linearizer::Visit(IR::Binop *binop) {
}

void IR::Visitor::Linearizer::Visit(IR::Call *call) {
}

void IR::Visitor::Linearizer::Visit(IR::CJump *cjump) {
  tos_stm_list_ = nullptr;
}

void IR::Visitor::Linearizer::Visit(IR::Const *cnst) {
}

void IR::Visitor::Linearizer::Visit(IR::Eseq *eseq) {
  std::cerr << "ESEQ node found. Use canonizer first." << std::endl;
  exit(1);
}

void IR::Visitor::Linearizer::Visit(IR::Exp *exp) {
  tos_stm_list_ = nullptr;
}

void IR::Visitor::Linearizer::Visit(IR::ExpList *exp_list) {
}

void IR::Visitor::Linearizer::Visit(IR::Jump *jump) {
  tos_stm_list_ = nullptr;
}

void IR::Visitor::Linearizer::Visit(IR::Mem *mem) {
}

void IR::Visitor::Linearizer::Visit(IR::Move *move) {
  tos_stm_list_ = nullptr;
}

void IR::Visitor::Linearizer::Visit(IR::Name *name) {
}

void IR::Visitor::Linearizer::Visit(IR::Seq *seq) {
  parent_pointer_ref_.emplace((void**)&seq->first_);
  seq->first_->Accept(this);
  parent_pointer_ref_.pop();
  
  IR::StmList* left = tos_stm_list_;
  
  parent_pointer_ref_.emplace((void**)&seq->second_);
  seq->second_->Accept(this);
  parent_pointer_ref_.pop();
  
  IR::StmList* right = tos_stm_list_;
  
  if (!left && !right) {
    tos_stm_list_ = new IR::StmList(2, seq, seq);
    return;
  }
  
  if (left && right) {
    tos_stm_list_ = new IR::StmList(*left, *right);
    return;
  }
  
  if (left) {
    left->AddStm(seq->second_);
    tos_stm_list_ = left;
  } else {
    right->AddPrecedingStm(seq->first_);
    tos_stm_list_ = right;
  }
}

void IR::Visitor::Linearizer::Visit(IR::SetLabel *set_label) {
  tos_stm_list_ = nullptr;
}

void IR::Visitor::Linearizer::Visit(IR::TempExp *temp_expr) {
}
