//
// Created by Igor Maximov on 06.08.2020.
//

#include "Instr.h"

ASM::TempList ASM::Move::use() const {
  TempList list;
  list.push_back(src);
  return list;
}

ASM::TempList ASM::Move::def() const {
  TempList list;
  list.push_back(trg);
  return list;
}

ASM::Targets ASM::Move::jumps() const {
  return ASM::Targets();
}

std::string ASM::Move::format() const {
  return std::string();
}

ASM::Move::Move(std::string assem, IR::Temp src, IR::Temp trg)
    : Instr(std::move(assem)), src(std::move(src)), trg(std::move(trg)) {
}

ASM::TempList ASM::Label::use() const {
  return ASM::TempList();
}

ASM::TempList ASM::Label::def() const {
  return ASM::TempList();
}

ASM::Targets ASM::Label::jumps() const {
  return ASM::Targets();
}

std::string ASM::Label::format() const {
  return std::string();
}

ASM::Label::Label(std::string assem, IR::Label label) : Instr(std::move(assem)), label_(std::move(label)) {
}

ASM::TempList ASM::Oper::use() const {
  return use_;
}

ASM::TempList ASM::Oper::def() const {
  return def_;
}

ASM::Targets ASM::Oper::jumps() const {
  return targets_;
}

std::string ASM::Oper::format() const {
  return std::string();
}

ASM::Oper::Oper(std::string assem, TempList use, TempList def)
    : Instr(std::move(assem)), use_(std::move(use)), def_(std::move(def)) {
}

ASM::Oper::Oper(std::string assem, TempList use, TempList def, LabelList targets)
    : Instr(std::move(assem)), use_(std::move(use)), def_(std::move(def)), targets_(std::move(targets)) {
}
