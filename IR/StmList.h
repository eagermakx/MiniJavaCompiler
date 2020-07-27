//
// Created by Igor Maximov on 27.07.2020.
//

#pragma once
#include "ir_nodes.h"

namespace IR {

class StmList {
 public:
  StmList();
  StmList(size_t num_stms, IR::BaseStm* root, IR::Seq* rightmost_seq);
  
  // Merge-constructor
  StmList(StmList& left, StmList& right);
  
  IR::BaseStm* Tree();
  void AddStm(IR::BaseStm* stm);
  void AddPrecedingStm(IR::BaseStm* stm);
  bool Empty() const;
  
 private:
  IR::BaseStm* root_ = nullptr;
  IR::Seq* rightmost_seq = nullptr;
  int num_statements_ = 0;
};

}