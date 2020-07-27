//
// Created by Igor Maximov on 26.07.2020.
//

#include "NodeTraits.h"

void IR::Visitor::NodeTraits::Visit(IR::Binop *binop) {
  latest_type = NodeType::Binop;
}

void IR::Visitor::NodeTraits::Visit(IR::Call *call) {
  latest_type = NodeType::Call;
}

void IR::Visitor::NodeTraits::Visit(IR::CJump *cjump) {
  latest_type = NodeType::CJump;
}

void IR::Visitor::NodeTraits::Visit(IR::Const *cnst) {
  latest_type = NodeType::Const;
}

void IR::Visitor::NodeTraits::Visit(IR::Eseq *eseq) {
  latest_type = NodeType::Eseq;
}

void IR::Visitor::NodeTraits::Visit(IR::Exp *exp) {
  latest_type = NodeType::Exp;
}

void IR::Visitor::NodeTraits::Visit(IR::ExpList *exp_list) {
  latest_type = NodeType::ExpList;
}

void IR::Visitor::NodeTraits::Visit(IR::Jump *jump) {
  latest_type = NodeType::Jump;
}

void IR::Visitor::NodeTraits::Visit(IR::Mem *mem) {
  latest_type = NodeType::Mem;
}

void IR::Visitor::NodeTraits::Visit(IR::Move *move) {
  latest_type = NodeType::Move;
}

void IR::Visitor::NodeTraits::Visit(IR::Name *name) {
  latest_type = NodeType::Name;
}

void IR::Visitor::NodeTraits::Visit(IR::Seq *seq) {
  latest_type = NodeType::Seq;
}

void IR::Visitor::NodeTraits::Visit(IR::SetLabel *set_label) {
  latest_type = NodeType::SetLabel;
}

void IR::Visitor::NodeTraits::Visit(IR::TempExp *temp_expr) {
  latest_type = NodeType::TempExp;
}

IR::Visitor::NodeTraits::NodeType IR::Visitor::NodeTraits::Type(IR::BaseNode* node) {
  node->Accept(this);
  return latest_type;
}
