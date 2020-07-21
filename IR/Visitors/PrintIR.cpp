//
// Created by Igor Maximov on 04.04.2020.
//

#include "IR/ir_nodes.h"
#include "PrintIR.h"
#include <iostream>

namespace IR {

Visitor::PrintIR::PrintIR(const std::string &filename) {
  stream_.open(filename, std::ios_base::out);
  GraphPrologue();
}

void Visitor::PrintIR::GraphPrologue() {
  const char *prologue = "digraph AST {"
                         "\tnode [ shape = rectangle ];"
                         "\tgraph [ dpi = 300 ];";
  stream_ << prologue;
}

void Visitor::PrintIR::GraphEpilogue() {
  const char *epilogue = "}";
  stream_ << epilogue;
}

int Visitor::PrintIR::NewNode() {
  return ++max_node;
}

void Visitor::PrintIR::PrintEdge(int from, int to) {
  stream_ << "\t" << std::to_string(from) << " -> " << std::to_string(to) << ";\n";
}

void Visitor::PrintIR::PrintNode(int node, const std::string &label) {
  stream_ << "\t" << std::to_string(node) << " [ label = \"" << label << "\" ]; \n";
}

Visitor::PrintIR::~PrintIR() {
  GraphEpilogue();
  stream_.close();
}

void Visitor::PrintIR::PushNode(int node) {
  node_stack_.push(node);
}

void Visitor::PrintIR::PopNode() {
  node_stack_.pop();
}

int Visitor::PrintIR::Parent() {
  return node_stack_.top();
}

int Visitor::PrintIR::CreateNodeAndLink(const std::string &label) {
  int node = NewNode();
  int parent = Parent();
  PrintNode(node, label);
  PrintEdge(parent, node);
  return node;
}

void Visitor::PrintIR::Visit(IR::Binop *binop) {
  int node = CreateNodeAndLink("BINOP");
  PushNode(node);
  binop->lhs->Accept(this);
  binop->rhs->Accept(this);
  PopNode();
}

void Visitor::PrintIR::Visit(IR::Call *call) {
  CreateNodeAndLink("Call to " + call->function.ToString());
}

void Visitor::PrintIR::Visit(IR::CJump *cjump) {
  int node = CreateNodeAndLink("Cjump t: " + cjump->ltrue.ToString() + ", f: " + cjump->lfalse.ToString());
  PushNode(node);
  
  cjump->lhs->Accept(this);
  cjump->rhs->Accept(this);
  
  PopNode();
}

void Visitor::PrintIR::Visit(IR::Const *cnst) {
  CreateNodeAndLink("Const(" + std::to_string(cnst->val_) + ")");
}

void Visitor::PrintIR::Visit(IR::Eseq *eseq) {
  int node = CreateNodeAndLink("ESEQ");
  PushNode(node);
  
  eseq->stm_->Accept(this);
  eseq->exp_->Accept(this);
  
  PopNode();
}

void Visitor::PrintIR::Visit(IR::Exp *exp) {
  int node = CreateNodeAndLink("Exp");
  PushNode(node);
  exp->GetExpr()->Accept(this);
  PopNode();
}

void Visitor::PrintIR::Visit(IR::ExpList *exp_list) {
  int node = CreateNodeAndLink("ExpList");
  PushNode(node);
  for (auto& exp : exp_list->list) {
    exp->Accept(this);
  }
  PopNode();
}

void Visitor::PrintIR::Visit(IR::Jump *jump) {
  CreateNodeAndLink("Jump to " + jump->label_.ToString());
}

void Visitor::PrintIR::Visit(IR::Mem *mem) {
  int node = CreateNodeAndLink("Mem");
  PushNode(node);
  mem->exp_->Accept(this);
  PopNode();
}

void Visitor::PrintIR::Visit(IR::Move *move) {
  int node = CreateNodeAndLink("Move");
  PushNode(node);
  move->from_->Accept(this);
  move->to_->Accept(this);
  PopNode();
}

void Visitor::PrintIR::Visit(IR::Name *name) {
  CreateNodeAndLink("Name: " + name->label_.ToString());
}

void Visitor::PrintIR::Visit(IR::Seq *seq) {
  int node = CreateNodeAndLink("Seq");
  PushNode(node);
  seq->first_->Accept(this);
  seq->second_->Accept(this);
  PopNode();
}

void Visitor::PrintIR::Visit(IR::SetLabel *set_label) {
  CreateNodeAndLink("Label: " + set_label->label_.ToString());
}

void Visitor::PrintIR::Visit(IR::TempExp *temp_expr) {
  int node = CreateNodeAndLink("TEMP(" + temp_expr->temp_.ToString() + ")");
}

void Visitor::PrintIR::Run(IRMapping method_trees) {
  for (auto pair : method_trees) {
    
    auto name = pair.first;
    auto stmts = pair.second;
  
    int node = NewNode();
    PrintNode(node, "Method " + name);
    PushNode(node);
    
    stmts->Accept(this);
    
    PopNode();
  }
}

}