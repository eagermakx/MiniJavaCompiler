//
// Created by Igor Maximov on 26.07.2020.
//

#include "CanonVisitor.h"
#include <IR/ir_nodes.h>
#include "CanonVisitor.h"
#include <iostream>
#include <IR/StmList.h>

namespace IR {

void Visitor::CanonVisitor::Visit(IR::Binop *binop) {
  parent_pointer_ref_.emplace((void**)&binop->lhs);
  binop->lhs->Accept(this);
  parent_pointer_ref_.pop();
  
  parent_pointer_ref_.emplace((void**)&binop->rhs);
  binop->rhs->Accept(this);
  parent_pointer_ref_.pop();
  
  bool left_eseq = traits_.Type(binop->lhs) == NodeTraits::NodeType::Eseq;
  bool right_eseq = traits_.Type(binop->rhs) == NodeTraits::NodeType::Eseq;
  
  IR::BaseStm* stm;
  IR::BaseExp* left_exp;
  IR::BaseExp* right_exp;
  
  // No actions need to be taken
  if (!left_eseq && !right_eseq) {
    return;
  }
  
  IR::Temp t;
  auto te = new IR::TempExp(t);
  
  if (left_eseq && right_eseq) {
    stm = new IR::Seq(
      new IR::Seq(
            dynamic_cast<IR::Eseq*>(binop->lhs)->stm_,
            new IR::Move(te, dynamic_cast<IR::Eseq*>(binop->lhs)->exp_)
          ),
          dynamic_cast<IR::Eseq*>(binop->rhs)->stm_
    );
    left_exp = te;
    right_exp = dynamic_cast<IR::Eseq*>(binop->rhs)->exp_;
  } else {
    if (left_eseq) {
      stm = dynamic_cast<IR::Eseq*>(binop->lhs)->stm_;
      left_exp = dynamic_cast<IR::Eseq*>(binop->lhs)->exp_;
      right_exp = binop->rhs;
    } else {
      stm = new IR::Seq(new IR::Move(te, binop->lhs), dynamic_cast<IR::Eseq*>(binop->rhs)->stm_);
      left_exp = binop->lhs;
      right_exp = dynamic_cast<IR::Eseq*>(binop->rhs)->exp_;
    }
  }
  
  auto parent_ref = reinterpret_cast<BaseNode **>(parent_pointer_ref_.top());
  binop->lhs = left_exp;
  binop->rhs = right_exp;
  
  // TODO: Check for usage of the same pointer in IR (except TempExp)
  *parent_ref = new IR::Eseq(stm, binop);
}

void Visitor::CanonVisitor::Visit(IR::Call *call) {
  ExpList* list = call->args;
  std::vector<bool> mask;
  
  int last_eseq = -1;
  for (int i = 0; i < list->list.size(); ++i) {
    bool is_eseq = traits_.Type(list->list[i]) == NodeTraits::NodeType::Eseq;
    
    if (is_eseq) {
      last_eseq = i;
    }
    
    mask.push_back(is_eseq);
  }
  
  // No action
  if (last_eseq == -1) {
    return;
  }
  
  IR::StmList prologue;
  std::vector<IR::Temp> temps(last_eseq + 1);
  
  for (int i = 0; i <= last_eseq; ++i) {
    IR::BaseExp* expr;
    
    if (mask[i]) {
      expr = dynamic_cast<IR::Eseq*>(list->list[i])->exp_;
      prologue.AddStm(dynamic_cast<IR::Eseq*>(list->list[i])->stm_);
    } else {
      expr = list->list[i];
    }
  
    prologue.AddStm(
      new IR::Move(new IR::TempExp(temps[i]), expr)
    );
    
    list->list[i] = new IR::TempExp(temps[i]);
  }
  
  auto parent_ref = reinterpret_cast<BaseNode **>(parent_pointer_ref_.top());
  *parent_ref = new IR::Eseq(prologue.Tree(), call);
}

void Visitor::CanonVisitor::Visit(IR::CJump *cjump) {
  parent_pointer_ref_.emplace((void**)&cjump->lhs);
  cjump->lhs->Accept(this);
  parent_pointer_ref_.pop();
  
  parent_pointer_ref_.emplace((void**)&cjump->rhs);
  cjump->rhs->Accept(this);
  parent_pointer_ref_.pop();
  
  bool left_eseq = traits_.Type(cjump->lhs) == NodeTraits::NodeType::Eseq;
  bool right_eseq = traits_.Type(cjump->rhs) == NodeTraits::NodeType::Eseq;
  
  IR::BaseStm* stm;
  IR::BaseExp* left_exp;
  IR::BaseExp* right_exp;
  
  // No actions need to be taken
  if (!left_eseq && !right_eseq) {
    return;
  }
  
  IR::Temp t;
  auto te = new IR::TempExp(t);
  
  if (left_eseq && right_eseq) {
    stm = new IR::Seq(
      new IR::Seq(
        dynamic_cast<IR::Eseq*>(cjump->lhs)->stm_,
        new IR::Move(te, dynamic_cast<IR::Eseq*>(cjump->lhs)->exp_)
      ),
      dynamic_cast<IR::Eseq*>(cjump->rhs)->stm_
    );
    left_exp = te;
    right_exp = dynamic_cast<IR::Eseq*>(cjump->rhs)->exp_;
  } else {
    if (left_eseq) {
      stm = dynamic_cast<IR::Eseq*>(cjump->lhs)->stm_;
      left_exp = dynamic_cast<IR::Eseq*>(cjump->lhs)->exp_;
      right_exp = cjump->rhs;
    } else {
      stm = new IR::Seq(new IR::Move(te, cjump->lhs), dynamic_cast<IR::Eseq*>(cjump->rhs)->stm_);
      left_exp = cjump->lhs;
      right_exp = dynamic_cast<IR::Eseq*>(cjump->rhs)->exp_;
    }
  }
  
  auto parent_ref = reinterpret_cast<BaseNode **>(parent_pointer_ref_.top());
  cjump->lhs = left_exp;
  cjump->rhs = right_exp;
  
  // TODO: Check for usage of the same pointer in IR (except TempExp)
  *parent_ref = new IR::Seq(stm, cjump);
}

void Visitor::CanonVisitor::Visit(IR::Const *cnst) {

}

void Visitor::CanonVisitor::Visit(IR::Eseq *eseq) {
  parent_pointer_ref_.emplace((void**)&eseq->stm_);
  eseq->stm_->Accept(this);
  parent_pointer_ref_.pop();
  parent_pointer_ref_.emplace((void**)&eseq->exp_);
  eseq->exp_->Accept(this);
  parent_pointer_ref_.pop();
  
  /**
   *   Eseq                      Eseq
   *   /    \                   /    \
   *  s1    Eseq     –>       Seq     e
   *        /   \            /   \
   *      s2     e          s1    s2
   *
   *      With no ESEQ's in <e>
   */
  IR::BaseNode* right_child = eseq->exp_;
  if (traits_.Type(right_child) == NodeTraits::NodeType::Eseq) {
    auto parent_ref = reinterpret_cast<BaseNode **>(parent_pointer_ref_.top());
    
    auto s1 = eseq->stm_;
    auto s2 = dynamic_cast<IR::Eseq*>(eseq->exp_)->stm_;
    auto e = dynamic_cast<IR::Eseq*>(eseq->exp_)->exp_;
    
    eseq->stm_ = new IR::Seq(s1, s2);
    eseq->exp_ = e;
  }
}

void Visitor::CanonVisitor::Visit(IR::Exp *exp) {
  parent_pointer_ref_.emplace((void**)&exp->exp_);
  exp->exp_->Accept(this);
  parent_pointer_ref_.pop();
  
  if (traits_.Type(exp->exp_) == NodeTraits::NodeType::Eseq) {
    auto parent_ref = reinterpret_cast<BaseNode **>(parent_pointer_ref_.top());
    
    auto e = dynamic_cast<IR::Eseq*>(exp->exp_)->exp_;
    auto s = dynamic_cast<IR::Eseq*>(exp->exp_)->stm_;
    
    exp->exp_ = e;
    *parent_ref = new IR::Seq(s, exp);
  }
}

void Visitor::CanonVisitor::Visit(IR::ExpList *exp_list) {
  // unreachable
}

void Visitor::CanonVisitor::Visit(IR::Jump *jump) {
}

void Visitor::CanonVisitor::Visit(IR::Mem *mem) {
  parent_pointer_ref_.emplace((void**)&mem->exp_);
  mem->exp_->Accept(this);
  parent_pointer_ref_.pop();
  
  if (traits_.Type(mem->exp_) == NodeTraits::NodeType::Eseq) {
    auto parent_ref = reinterpret_cast<BaseNode **>(parent_pointer_ref_.top());
    auto s = dynamic_cast<IR::Eseq*>(mem->exp_)->stm_;
    auto e = dynamic_cast<IR::Eseq*>(mem->exp_)->exp_;
    
    *parent_ref = new IR::Eseq(s, new IR::Mem(e));
  }
}

void Visitor::CanonVisitor::Visit(IR::Move *move) {
  parent_pointer_ref_.emplace((void**)&move->to_);
  move->to_->Accept(this);
  parent_pointer_ref_.pop();
  
  parent_pointer_ref_.emplace((void**)&move->from_);
  move->from_->Accept(this);
  parent_pointer_ref_.pop();
  
  bool left_eseq = traits_.Type(move->to_) == NodeTraits::NodeType::Eseq;
  bool right_eseq = traits_.Type(move->from_) == NodeTraits::NodeType::Eseq;
  
  IR::BaseStm* stm;
  IR::BaseExp* left_exp;
  IR::BaseExp* right_exp;
  
  // No actions need to be taken
  if (!left_eseq && !right_eseq) {
    return;
  }
  
  if (left_eseq && right_eseq) {
    stm = new IR::Seq(dynamic_cast<IR::Eseq*>(move->to_)->stm_, dynamic_cast<IR::Eseq*>(move->from_)->stm_);
    left_exp = dynamic_cast<IR::Eseq*>(move->to_)->exp_;
    right_exp = dynamic_cast<IR::Eseq*>(move->from_)->exp_;
  } else {
    if (left_eseq) {
      stm = dynamic_cast<IR::Eseq*>(move->to_)->stm_;
      left_exp = dynamic_cast<IR::Eseq*>(move->to_)->exp_;
      right_exp = move->from_;
    } else {
      stm = dynamic_cast<IR::Eseq*>(move->from_)->stm_;
      left_exp = move->to_;
      right_exp = dynamic_cast<IR::Eseq*>(move->from_)->exp_;
    }
  }
  
  auto parent_ref = reinterpret_cast<BaseNode **>(parent_pointer_ref_.top());
  *parent_ref = new IR::Seq(stm, new IR::Move(left_exp, right_exp));
}

void Visitor::CanonVisitor::Visit(IR::Name *name) {

}

void Visitor::CanonVisitor::Visit(IR::Seq *seq) {
  parent_pointer_ref_.emplace((void**)&seq->first_);
  seq->first_->Accept(this);
  parent_pointer_ref_.pop();
  
  parent_pointer_ref_.emplace((void**)&seq->second_);
  seq->second_->Accept(this);
  parent_pointer_ref_.pop();
}

void Visitor::CanonVisitor::Visit(IR::SetLabel *set_label) {

}

void Visitor::CanonVisitor::Visit(IR::TempExp *temp_expr) {

}

void Visitor::CanonVisitor::Run(IRMapping& method_trees) {
  for (auto& pair : method_trees) {
    
    auto name = pair.first;
    auto stmts = pair.second;

    stmts->Accept(this);
  }
}
  
}