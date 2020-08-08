//
// Created by Igor Maximov on 07.08.2020.
//

#include "InstSelection.h"
#include "IR/Visitors/NodeTraits.h"
#include "log.h"
#include "error.h"

std::vector<ASM::Instr*> buffer;
IR::Visitor::NodeTraits traits;
using namespace IR::Visitor;

const ASM::TempList empty_list;

ASM::LabelList L(IR::Label l) {
  ASM::LabelList list;
  list.emplace_back(std::move(l));
  
  return list;
}

ASM::LabelList L(IR::Label l, ASM::LabelList list) {
  list.emplace_back(std::move(l));
  return list;
}

ASM::TempList L(IR::Temp t) {
  ASM::TempList list;
  list.emplace_back(std::move(t));
  
  // RVO?
  return list;
}

ASM::TempList L(IR::Temp t, ASM::TempList list) {
  list.emplace_back(std::move(t));
  return list;
}

void emit(ASM::Instr* that) {
  buffer.emplace_back(that);
}

void clear_buffer() {
  buffer.clear();
}

//////////////////////
///// Expressions ////

IR::Temp Munch(IR::Mem* mem);
IR::Temp Munch(IR::Binop* binop);
IR::Temp Munch(IR::Call* call);
IR::Temp Munch(IR::Const* cnst);

IR::Temp Munch(IR::BaseExp* exp) {
  switch(traits.Type(exp)) {
    case NodeTraits::NodeType::Mem: return Munch(dynamic_cast<IR::Mem*>(exp));
    case NodeTraits::NodeType::Binop: return Munch(dynamic_cast<IR::Binop*>(exp));
    case NodeTraits::NodeType::Call: return Munch(dynamic_cast<IR::Call*>(exp));
    case NodeTraits::NodeType::Const: return Munch(dynamic_cast<IR::Const*>(exp));
    default:
      FAIL("unexpected failure in Munch(exp)");
  }
}

IR::Temp Munch(IR::Mem* mem) {
  IR::Temp ret;
  
  if (traits.Type(mem->exp_) == NodeTraits::NodeType::Binop) {
    auto* binop = dynamic_cast<IR::Binop*>(mem->exp_);
    
    if (binop->o == IR::BinaryOpType::PLUS || binop->o == IR::BinaryOpType::MINUS) {
      if (traits.Type(binop->lhs) == NodeTraits::NodeType::Const) {
        emit(new ASM::Oper("load %s M[%s + " + std::to_string(dynamic_cast<IR::Const*>(binop->lhs)->val_) + "]", L(Munch(binop->rhs)), L(ret)));
        return ret;
      } else if (traits.Type(binop->rhs) == NodeTraits::NodeType::Const) {
        emit(new ASM::Oper("load %s M[%s + " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_) + "]", L(Munch(binop->lhs)), L(ret)));
        return ret;
      }
    }
  } else if (traits.Type(mem->exp_) == NodeTraits::NodeType::Const) {
    auto* cnst = dynamic_cast<IR::Const*>(mem->exp_);
    emit(new ASM::Oper("load %s M[" + std::to_string(cnst->val_) + "]", empty_list, L(ret)));
    return ret;
  }
  
  emit(new ASM::Oper("load %s %s", L(ret), L(Munch(mem->exp_))));
  return ret;
}

IR::Temp Munch(IR::Binop* binop) {
  IR::Temp ret;
  
  if (traits.Type(binop->rhs) == NodeTraits::NodeType::Const) {
    if (binop->o == IR::BinaryOpType::PLUS) {
      emit(new ASM::Oper("addi %s %s " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_), L(Munch(binop->lhs)), L(ret)));
      return ret;
    } else if (binop->o == IR::BinaryOpType::MINUS) {
      emit(new ASM::Oper("subi %s %s " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_), L(Munch(binop->lhs)), L(ret)));
      return ret;
    }
  } else if (traits.Type(binop->lhs) == NodeTraits::NodeType::Const) {
    if (binop->o == IR::BinaryOpType::PLUS) {
      emit(new ASM::Oper("addi %s %s " + std::to_string(dynamic_cast<IR::Const*>(binop->lhs)->val_), L(Munch(binop->rhs)), L(ret)));
      return ret;
    }
  }
  
  std::string op;
  switch (binop->o) {
    case IR::BinaryOpType::PLUS:
      op = "add";
      break;
    case IR::BinaryOpType::MINUS:
      op = "sub";
      break;
    case IR::BinaryOpType::MUL:
      op = "mul";
      break;
    default:
      FAIL("'div/and/or' ops not supported during ASM generation yet");
  }
  
  emit(new ASM::Oper(op + " %s %s %s", L(Munch(binop->rhs), L(Munch(binop->lhs))), L(ret)));
  return ret;
}

IR::Temp Munch(IR::Call* call) {
  UNREACHABLE("Munch(call)");
}

// TODO: определить новый класс MoveConst или заменить Temp -> Temp*
IR::Temp Munch(IR::Const* cnst) {
  IR::Temp t;
  ASM::TempList def;
  def.push_back(t);
  emit(new ASM::Oper("mov %s " + std::to_string(cnst->val_), ASM::TempList(), def));
  return t;
}

// Лень
void MunchExpList(IR::ExpList* list);

/*std::vector<ASM::Instr*> SelectInstructions(IR::BaseExp* exp) {
  clear_buffer();
  Munch(exp);
  return buffer;
}*/


//////////////////////
///// Statements /////

void Munch(IR::BaseStm* stm);

std::vector<ASM::Instr*> ASM::SelectInstructions(IR::BaseStm* stm) {
  clear_buffer();
  Munch(stm);
  return buffer;
}



void MunchMove(IR::Move* move) {
  if (traits.Type(move->to_) == NodeTraits::NodeType::Mem) {
    auto* mem = (IR::Mem*)(move->to_);
  
    if (traits.Type(mem->exp_) == NodeTraits::NodeType::Binop) {
      auto* binop = dynamic_cast<IR::Binop*>(mem->exp_);
    
      if (binop->o == IR::BinaryOpType::PLUS || binop->o == IR::BinaryOpType::MINUS) {
        if (traits.Type(binop->lhs) == NodeTraits::NodeType::Const) {
          emit(new ASM::Oper("store M[%s + " + std::to_string(dynamic_cast<IR::Const*>(binop->lhs)->val_) + "] %s", L(Munch(move->from_), L(Munch(binop->rhs))), empty_list));
          return;
        } else if (traits.Type(binop->rhs) == NodeTraits::NodeType::Const) {
          emit(new ASM::Oper("store M[%s + " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_) + "] %s", L(Munch(move->from_), L(Munch(binop->lhs))), empty_list));
          return;
        }
      }
    } else if (traits.Type(mem->exp_) == NodeTraits::NodeType::Const) {
      auto* cnst = dynamic_cast<IR::Const*>(mem->exp_);
      emit(new ASM::Oper("store M[" + std::to_string(cnst->val_) + "] %s", L(Munch(move->from_)), empty_list));
      return;
    }
  
    emit(new ASM::Oper("store M[%s] %s", L(Munch(move->to_), L(Munch(move->from_))), empty_list));
  }
  
  if (traits.Type(move->to_) != NodeTraits::NodeType::TempExp) {
    UNREACHABLE("InstSelection: expected mem or tempexp on the left hand side");
  }
  
  emit(new ASM::Oper("mov %s %s", L(Munch(move->from_)), L(Munch(move->to_))));
}

void MunchJump(IR::Jump* j) {
  emit(new ASM::Oper("jmp " + j->label_.ToString(), empty_list, empty_list, L(j->label_)));
}

void MunchSetLabel(IR::SetLabel* s) {
  emit(new ASM::Label(s->label_.ToString() + ":", s->label_));
}

void MunchCJump(IR::CJump* cj) {
  emit(new ASM::Oper("j" + AsmRepr(cj->o) + " " + cj->ltrue.ToString(), empty_list, empty_list, L(cj->ltrue)));
}

void Munch(IR::BaseStm* stm) {
  switch(traits.Type(stm)) {
    case NodeTraits::NodeType::Move:
      MunchMove((IR::Move*)stm);
      break;
    case NodeTraits::NodeType::SetLabel:
      MunchSetLabel((IR::SetLabel*)stm);
      break;
    case NodeTraits::NodeType::Jump:
      MunchJump((IR::Jump*)stm);
      break;
    case NodeTraits::NodeType::CJump:
      MunchCJump((IR::CJump*)stm);
      break;
    /*case NodeTraits::NodeType::Exp:
      MunchExp((IR::Exp*)stm);
      break;*/
    default: FAIL("Unexpected???? node type at Munch(stm)");
  }
}