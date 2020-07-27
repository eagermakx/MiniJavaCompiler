//
// Created by Igor Maximov on 27.07.2020.
//

#include "StmList.h"

IR::BaseStm *IR::StmList::Tree() {
  return root_;
}

void IR::StmList::AddStm(IR::BaseStm *stm) {
  if (num_statements_ == 0) {
    root_ = stm;
    rightmost_seq = nullptr;
  } else if (num_statements_ == 1) {
    rightmost_seq = new IR::Seq(root_, stm);
    root_ = rightmost_seq;
  } else {
    auto s = rightmost_seq->second_;
    
    auto seq = new IR::Seq(s, stm);
    rightmost_seq->second_ = seq;
    rightmost_seq = seq;
  }
  
  ++num_statements_;
}

bool IR::StmList::Empty() const {
  return root_ == nullptr;
}

IR::StmList::StmList(size_t num_stms, IR::BaseStm *root, IR::Seq *rightmost_seq)
    : num_statements_(num_stms), root_(root), rightmost_seq(rightmost_seq) {
}

IR::StmList::StmList(IR::StmList &left, IR::StmList &right)
    : num_statements_(left.num_statements_ + right.num_statements_),
      root_(left.root_),
      rightmost_seq(right.rightmost_seq)
{
  left.AddStm(right.Tree());
}

void IR::StmList::AddPrecedingStm(IR::BaseStm *stm) {
  if (num_statements_ == 0) {
    root_ = stm;
    rightmost_seq = nullptr;
  } else if (num_statements_ == 1) {
    rightmost_seq = new IR::Seq(stm, root_);
    root_ = rightmost_seq;
  } else {
    root_ = new IR::Seq(stm, root_);
  }
  
  ++num_statements_;
}

IR::StmList::StmList() : root_(nullptr), num_statements_(0), rightmost_seq(nullptr) {
}
