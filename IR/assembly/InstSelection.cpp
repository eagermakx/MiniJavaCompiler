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

/*
std::string FormatInstruction(const std::string& assem, const std::vector<IR::Temp> use, const std::vector<IR::Temp> def) {
  std::string output;
  
  int use_offset = 0;
  int def_offset = 0;
  int format_trigger = '$';
  
  char use_key = 's'; // src
  char def_key = 'd'; // dst
  
  for (int i = 0; i < output.size(); ++i) {
    char c = assem[i];
    
    if (c == format_trigger) {
      char next = assem[i + 1];
      
      if (next == use_key) {
        output += use[use_offset].ToString();
        ++use_offset;
      } else if (next == def_key) {
        output += def[def_offset].ToString();
        ++def_offset;
      } else {
        FAIL("not 's' nor 'd' after '$' in an assembly instruction");
      }
      
      ++i;
    } else {
      output += c;
    }
  }
  
  return output;
}
*/

//////////////////////
///// Expressions ////

IR::Temp Munch(IR::Mem* mem);
IR::Temp Munch(IR::Binop* binop);
IR::Temp Munch(IR::Call* call);
IR::Temp Munch(IR::Const* cnst);
IR::Temp Munch(IR::Register* reg);
IR::Temp Munch(IR::TempExp* temp_exp);
void MunchExpList(IR::ExpList* list);

IR::Temp Munch(IR::BaseExp* exp) {
  switch(traits.Type(exp)) {
    case NodeTraits::NodeType::Mem: return Munch(dynamic_cast<IR::Mem*>(exp));
    case NodeTraits::NodeType::Binop: return Munch(dynamic_cast<IR::Binop*>(exp));
    case NodeTraits::NodeType::Call: return Munch(dynamic_cast<IR::Call*>(exp));
    case NodeTraits::NodeType::Const: return Munch(dynamic_cast<IR::Const*>(exp));
    case NodeTraits::NodeType::Register: return Munch(dynamic_cast<IR::Register*>(exp));
    case NodeTraits::NodeType::TempExp: return Munch(dynamic_cast<IR::TempExp*>(exp));
    default:
      FAIL("unexpected node type in Munch(exp)");
  }
}

IR::Temp Munch(IR::TempExp* temp_exp) {
  return temp_exp->temp_;
}

IR::Temp Munch(IR::Register* reg) {
  return IR::Temp(reg->name_);
}

IR::Temp Munch(IR::Mem* mem) {
  IR::Temp ret;
  
  if (traits.Type(mem->exp_) == NodeTraits::NodeType::Binop) {
    auto* binop = dynamic_cast<IR::Binop*>(mem->exp_);
    
    if (binop->o == IR::BinaryOpType::PLUS || binop->o == IR::BinaryOpType::MINUS) {
      if (traits.Type(binop->lhs) == NodeTraits::NodeType::Const) {
        emit(new ASM::Oper("load $d M[$s + " + std::to_string(dynamic_cast<IR::Const*>(binop->lhs)->val_) + "]", L(Munch(binop->rhs)), L(ret)));
        return ret;
      } else if (traits.Type(binop->rhs) == NodeTraits::NodeType::Const) {
        emit(new ASM::Oper("load $d M[$s + " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_) + "]", L(Munch(binop->lhs)), L(ret)));
        return ret;
      }
    }
  } else if (traits.Type(mem->exp_) == NodeTraits::NodeType::Const) {
    auto* cnst = dynamic_cast<IR::Const*>(mem->exp_);
    emit(new ASM::Oper("load $d M[" + std::to_string(cnst->val_) + "]", empty_list, L(ret)));
    return ret;
  }
  
  emit(new ASM::Oper("load $d $s", L(ret), L(Munch(mem->exp_))));
  return ret;
}

IR::Temp Munch(IR::Binop* binop) {
  IR::Temp ret;
  
  if (traits.Type(binop->rhs) == NodeTraits::NodeType::Const) {
    if (binop->o == IR::BinaryOpType::PLUS) {
      emit(new ASM::Oper("addi $d $s " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_), L(Munch(binop->lhs)), L(ret)));
      return ret;
    } else if (binop->o == IR::BinaryOpType::MINUS) {
      emit(new ASM::Oper("subi $d $s " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_), L(Munch(binop->lhs)), L(ret)));
      return ret;
    }
  } else if (traits.Type(binop->lhs) == NodeTraits::NodeType::Const) {
    if (binop->o == IR::BinaryOpType::PLUS) {
      emit(new ASM::Oper("addi $d $s " + std::to_string(dynamic_cast<IR::Const*>(binop->lhs)->val_), L(Munch(binop->rhs)), L(ret)));
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
  
  emit(new ASM::Oper(op + " $d $s $s", L(Munch(binop->rhs), L(Munch(binop->lhs))), L(ret)));
  return ret;
}

IR::Temp Munch(IR::Call* call) {
  emit(new ASM::Oper("push %fp", empty_list, empty_list));
  emit(new ASM::Oper("mov %fp %sp", empty_list, empty_list));
  
  MunchExpList(call->args);
  emit(new ASM::Oper("jmp " + call->function.ToString(), empty_list, empty_list, L(call->function)));
  
  IR::Temp t;
  // return value;
  emit(new ASM::Oper("load $d M[%fp + 2]", empty_list, L(t)));
  emit(new ASM::Oper("pop %fp", empty_list, empty_list));
  
  return t;
}

// TODO: определить новый класс MoveConst или заменить Temp -> Temp*
IR::Temp Munch(IR::Const* cnst) {
  IR::Temp t;
  ASM::TempList def;
  def.push_back(t);
  emit(new ASM::Oper("mov $d " + std::to_string(cnst->val_), ASM::TempList(), def));
  return t;
}

// Лень
void MunchExpList(IR::ExpList* list) {
  const int default_frame_offset = 4;
  
  for (int i = 0; i < list->list.size(); ++i) {
    auto* exp = list->list[i];
    emit(new ASM::Oper("store [%fp + " + std::to_string(i + default_frame_offset) + "] $s", L(Munch(exp)), empty_list));
  }
}

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
          emit(new ASM::Oper("store M[$s + " + std::to_string(dynamic_cast<IR::Const*>(binop->lhs)->val_) + "] $s", L(Munch(move->from_), L(Munch(binop->rhs))), empty_list));
          return;
        } else if (traits.Type(binop->rhs) == NodeTraits::NodeType::Const) {
          emit(new ASM::Oper("store M[$s + " + std::to_string(dynamic_cast<IR::Const*>(binop->rhs)->val_) + "] $s", L(Munch(move->from_), L(Munch(binop->lhs))), empty_list));
          return;
        }
      }
    } else if (traits.Type(mem->exp_) == NodeTraits::NodeType::Const) {
      auto* cnst = dynamic_cast<IR::Const*>(mem->exp_);
      emit(new ASM::Oper("store M[" + std::to_string(cnst->val_) + "] $s", L(Munch(move->from_)), empty_list));
      return;
    }
  
    emit(new ASM::Oper("store M[$s] $s", L(Munch(move->to_), L(Munch(move->from_))), empty_list));
  }
  
  if (traits.Type(move->to_) != NodeTraits::NodeType::TempExp) {
    UNREACHABLE("InstSelection: expected mem or tempexp on the left hand side");
  }
  
  emit(new ASM::Oper("mov $d $s", L(Munch(move->from_)), L(Munch(move->to_))));
}

void MunchJump(IR::Jump* j) {
  emit(new ASM::Oper("jmp " + j->label_.ToString(), empty_list, empty_list, L(j->label_)));
}

void MunchSetLabel(IR::SetLabel* s) {
  emit(new ASM::Label(s->label_.ToString() + ":", s->label_));
}

void MunchCJump(IR::CJump* cj) {
  emit(new ASM::Oper("cmp $s 0", L(Munch(cj->lhs)), empty_list));
  emit(new ASM::Oper("j" + AsmRepr(cj->o) + " " + cj->ltrue.ToString(), empty_list, empty_list, L(cj->ltrue)));
}

void MunchExp(IR::Exp* exp) {
  Munch(exp->exp_);
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
    case NodeTraits::NodeType::Exp:
      MunchExp((IR::Exp*)stm);
      break;
    default: FAIL("Unexpected???? node type at Munch(stm)");
  }
}