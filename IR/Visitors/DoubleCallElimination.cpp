//
// Created by Igor Maximov on 28.07.2020.
//

#include "DoubleCallElimination.h"

void IR::Visitor::DoubleCallElimination::Run(IRMapping &method_trees) {
  for (auto& method : method_trees) {
    auto name = method.first;
    auto stmts = method.second;
    
    stmts->Accept(this);
  }
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Binop *binop) {
  binop->lhs->Accept(this);
  binop->rhs->Accept(this);
  
  bool left_call = traits_.Type(binop->lhs) == NodeTraits::NodeType::Call;
  bool right_call = traits_.Type(binop->rhs) == NodeTraits::NodeType::Call;
  
  if (left_call) {
    WrapCall(&binop->lhs);
  }
  
  if (right_call) {
    WrapCall(&binop->rhs);
  }
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Call *call) {
  call->args->Accept(this);
  
  /*for (int i = 0; i < call->args->list.size(); ++i) {
    if (traits_.Type(call->args->list[i]) == NodeTraits::NodeType::Call) {
      IR::Temp temp;
      auto temp_e = new IR::TempExp(temp);
      auto e = call->args->list[i];
  
      call->args->list[i] = new IR::Eseq(new IR::Move(temp_e, e), temp_e);
    }
  }*/
}

void IR::Visitor::DoubleCallElimination::Visit(IR::CJump *cjump) {
  cjump->lhs->Accept(this);
  cjump->rhs->Accept(this);
  
  bool left_call = traits_.Type(cjump->lhs) == NodeTraits::NodeType::Call;
  bool right_call = traits_.Type(cjump->rhs) == NodeTraits::NodeType::Call;
  
  if (left_call) {
    WrapCall(&cjump->lhs);
  }
  
  if (right_call) {
    WrapCall(&cjump->rhs);
  }
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Const *cnst) {
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Eseq *eseq) {
  eseq->stm_->Accept(this);
  eseq->exp_->Accept(this);
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Exp *exp) {
  exp->exp_->Accept(this);
}

void IR::Visitor::DoubleCallElimination::Visit(IR::ExpList *exp_list) {
  for (auto* exp : exp_list->list) {
    exp->Accept(this);
  }
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Jump *jump) {
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Mem *mem) {
  mem->exp_->Accept(this);
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Move *move) {
  move->to_->Accept(this);
  move->from_->Accept(this);
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Name *name) {
}

void IR::Visitor::DoubleCallElimination::Visit(IR::Seq *seq) {
  seq->first_->Accept(this);
  seq->second_->Accept(this);
}

void IR::Visitor::DoubleCallElimination::Visit(IR::SetLabel *set_label) {
}

void IR::Visitor::DoubleCallElimination::Visit(IR::TempExp *temp_expr) {
}

void IR::Visitor::DoubleCallElimination::WrapCall(IR::BaseExp **node) {
  IR::Temp temp;
  auto temp_exp = new IR::TempExp(temp);
  
  auto e = new IR::Eseq(new IR::Move(temp_exp, *node), temp_exp);
  *node = e;
}
