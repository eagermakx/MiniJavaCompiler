//
// Created by Igor Maximov on 31.07.2020.
//

#pragma once

#include "IR/Visitors/Base.h"
#include "IR/ir_nodes.h"
#include "NodeTraits.h"
#include "IR/blocks/Block.h"
#include "Visitor/IRTranslator.h"

namespace IR {
namespace Visitor {

class BlockBuilder : public IR::Visitor::Base {
 public:
  std::vector<IR::Block*>& Run(IRMapping method_trees);
  
  void Visit(Binop *binop) override;
  void Visit(Call *call) override;
  void Visit(CJump *cjump) override;
  void Visit(Const *cnst) override;
  void Visit(Eseq *eseq) override;
  void Visit(Exp *exp) override;
  void Visit(ExpList *exp_list) override;
  void Visit(Jump *jump) override;
  void Visit(Mem *mem) override;
  void Visit(Move *move) override;
  void Visit(Name *name) override;
  void Visit(Seq *seq) override;
  void Visit(SetLabel *set_label) override;
  void Visit(TempExp *temp_expr) override;
 
 private:
  IR::Seq *Finalize(BaseStm *last_stm, const std::string &method_name);
  static IR::SetLabel* BlockSetLabelStm(IR::Seq* block_start);
  
  NodeTraits traits_;
  std::vector<IR::Block*> blocks_;
  std::string current_method_name_;
  
  IR::Seq* block_start_ = nullptr;
  IR::Block* previous_block_ = nullptr;
};

} // namespace Visitor
} // namespace IR
