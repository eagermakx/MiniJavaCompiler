//
// Created by Igor Maximov on 27.07.2020.
//

#include "Linearizer.h"
#include <iostream>

IR::Visitor::Linearizer::List IR::Visitor::Linearizer::Run(IRMapping &method_trees) {
  for (auto& tree : method_trees) {
    auto method_name = tree.first;
    IR::BaseStm* code = tree.second;
    
    code->Accept(this);
    tree.second = tos_stm_list_->Tree();
  }
  
  Transform transform;
  transform.Run(method_trees);
  
  List linearizer_output;
  linearizer_output = std::move(transform.lin_out);
  
  return linearizer_output;
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

// Transform class

void IR::Visitor::Linearizer::Transform::Visit(IR::Binop *binop) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Call *call) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::CJump *cjump) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Const *cnst) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Eseq *eseq) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Exp *exp) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::ExpList *exp_list) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Jump *jump) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Mem *mem) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Move *move) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Name *name) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::Seq *seq) {
  stm_list.push_back(seq->first_);
  
  if (traits_.Type(seq->second_) != NodeTraits::NodeType::Seq) {
    stm_list.push_back(seq->second_);
    return;
  }
  
  seq->second_->Accept(this);
}

void IR::Visitor::Linearizer::Transform::Visit(IR::SetLabel *set_label) {
}

void IR::Visitor::Linearizer::Transform::Visit(IR::TempExp *temp_expr) {
}

void IR::Visitor::Linearizer::Transform::Run(IRMapping &method_trees) {
  for (auto& [method_name, stmts] : method_trees) {
    stm_list.clear();
    stmts->Accept(this);
    lin_out.emplace(method_name, std::move(stm_list));
  }
}
