//
// Created by Igor Maximov on 06.08.2020.
//

#include "Instr.h"
#include "log.h"
#include "error.h"

std::string FormatInstruction(const std::string& assem, const std::vector<IR::Temp> use, const std::vector<IR::Temp> def) {
  std::string output;
  
  int use_offset = 0;
  int def_offset = 0;
  int format_trigger = '$';
  
  char use_key = 's'; // src
  char def_key = 'd'; // dst
  
  for (int i = 0; i < assem.size(); ++i) {
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
        FAIL("not 's' nor 'd' after '%' in an assembly instruction");
      }
      
      ++i;
    } else {
      output += c;
    }
  }
  
  return output;
}


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

ASM::Oper::Oper(std::string assem, TempList use, TempList def)
    : Instr(std::move(assem)), use_(std::move(use)), def_(std::move(def)) {
}

ASM::Oper::Oper(std::string assem, TempList use, TempList def, LabelList targets)
    : Instr(std::move(assem)), use_(std::move(use)), def_(std::move(def)), targets_(std::move(targets)) {
}

std::string ASM::Instr::format() const {
  return FormatInstruction(assem, use(), def());
}
