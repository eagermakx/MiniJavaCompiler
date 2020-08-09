//
// Created by Igor Maximov on 06.08.2020.
//

#pragma once
#include "IR/generators/Temp.h"
#include "IR/generators/Label.h"
#include <string>
#include <vector>

namespace ASM {

using TempList = std::vector<IR::Temp>;
using LabelList = std::vector<IR::Label>;
using Targets = LabelList;

class Instr {
 public:
  explicit Instr(std::string assem) : assem(std::move(assem)) {}
  
  virtual TempList use() const = 0;
  virtual TempList def() const = 0;
  virtual Targets jumps() const = 0;
  std::string format() const;
  
 public:
  std::string assem;
};

class Oper : public Instr {
 public:
  Oper(std::string assem, TempList use, TempList def);
  Oper(std::string assem, TempList use, TempList def, LabelList targets);
  TempList use() const override;
  TempList def() const override;
  Targets jumps() const override;
 
 private:
  TempList use_;
  TempList def_;
  LabelList targets_;
};

class Move : public Instr {
 public:
  Move(std::string assem, IR::Temp src, IR::Temp trg);
  
  TempList use() const override;
  TempList def() const override;
  Targets jumps() const override;
 
 private:
  IR::Temp src;
  IR::Temp trg;
};

class Label : public Instr {
 public:
  Label(std::string assem, IR::Label label);
  
  TempList use() const override;
  TempList def() const override;
  Targets jumps() const override;
 
 private:
  IR::Label label_;
};

}
