//
// Created by Igor Maximov on 26.07.2020.
//

#pragma once

#include <string>
#include <fstream>
#include <stack>
#include <Visitor/IRTranslator.h>
#include "Base.h"

namespace IR {

namespace Visitor {

/**
 * Eliminates ESEQ nodes of the IR tree
 */
class NodeTraits : public IR::Visitor::Base {
 public:
  NodeTraits() = default;
  ~NodeTraits() = default;
  
  enum class NodeType {
    Binop,
    Call,
    CJump,
    Const,
    Eseq,
    Exp,
    ExpList,
    Jump,
    Mem,
    Move,
    Name,
    Seq,
    SetLabel,
    TempExp,
    ERR
  };
  
  void Visit(IR::Binop *binop) override;
  void Visit(IR::Call *call) override;
  void Visit(IR::CJump *cjump) override;
  void Visit(IR::Const *cnst) override;
  void Visit(IR::Eseq *eseq) override;
  void Visit(IR::Exp *exp) override;
  void Visit(IR::ExpList *exp_list) override;
  void Visit(IR::Jump *jump) override;
  void Visit(IR::Mem *mem) override;
  void Visit(IR::Move *move) override;
  void Visit(IR::Name *name) override;
  void Visit(IR::Seq *seq) override;
  void Visit(IR::SetLabel *set_label) override;
  void Visit(IR::TempExp *temp_expr) override;
  
  NodeType Type(IR::BaseNode* node);
 
 public:
  
  NodeType latest_type = NodeType::ERR;
};
  
}
  
}