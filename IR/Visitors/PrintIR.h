//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

#include <string>
#include <fstream>
#include <stack>
#include <Visitor/IRTranslator.h>
#include "Base.h"

namespace IR {

namespace Visitor {
class PrintIR : public IR::Visitor::Base {
 public:
  explicit PrintIR(const std::string &filename);
  
  void Run(IRMapping method_trees);
  
  ~PrintIR();
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
 
 private:
  void GraphPrologue();
  void GraphEpilogue();
  
  void PrintEdge(int from, int to);
  void PrintNode(int node, const std::string &label);
  int CreateNodeAndLink(const std::string &label);
  int NewNode();
  
  void PushNode(int node);
  void PopNode();
  int Parent();
  
  int max_node = 0;
  std::stack<int> node_stack_;
  std::ofstream stream_;
};
}

}