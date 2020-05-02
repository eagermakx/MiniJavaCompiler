//
// Created by Igor Maximov on 04.04.2020.
//

#include "ast.h"
#include "PrintAST.h"

Visitor::PrintAST::PrintAST(const std::string &filename) {
  stream_.open(filename, std::ios_base::out);
  GraphPrologue();
}

void Visitor::PrintAST::GraphPrologue() {
  const char* prologue = "digraph nfa {"
                         "\tnode [ shape = rectangle ];"
                         "\tgraph [ dpi = 300 ];";
  stream_ << prologue;
}

void Visitor::PrintAST::GraphEpilogue() {
  const char* epilogue = "}";
  stream_ << epilogue;
}

int Visitor::PrintAST::NewNode() {
  return ++max_node;
}

void Visitor::PrintAST::PrintEdge(int from, int to) {
  stream_ << "\t" << std::to_string(from) << " -> " << std::to_string(to) << ";\n";
}

void Visitor::PrintAST::PrintNode(int node, const std::string& label) {
  stream_ << "\t" << std::to_string(node) << " [ label = \"" << label << "\" ]; \n";
}

Visitor::PrintAST::~PrintAST() {
  GraphEpilogue();
  stream_.close();
}

void Visitor::PrintAST::Run(Program *program) {
  Visit(program);
}

void Visitor::PrintAST::Visit(Program *program) {
  int node = NewNode();
  PrintNode(node, "Program");
  
  PushNode(node);
  program->list->Accept(this);
  PopNode();
}


void Visitor::PrintAST::Visit(Entity::Const *that) {
  CreateNodeAndLink(std::to_string(that->value));
}

void Visitor::PrintAST::Visit(Entity::Id *that) {
  CreateNodeAndLink(that->identifier);
}

std::string Repr(Expr::BinOperationType type) {
  switch (type) {
    case Expr::BinOperationType::Add:
      return "Add";
    case Expr::BinOperationType::Sub:
      return "Sub";
    case Expr::BinOperationType::Mul:
      return "Mul";
    case Expr::BinOperationType::Div:
      return "Div";
  }
}

std::string Repr(Expr::UnOperationType type) {
  switch(type) {
    case Expr::UnOperationType::Minus:
      return "-";
    case Expr::UnOperationType::Not:
      return "!";
  }
}

void Visitor::PrintAST::Visit(Expr::BinaryOp *that) {
  int node = CreateNodeAndLink(Repr(that->type));
  
  PushNode(node);
  that->left->Accept(this);
  that->right->Accept(this);
  PopNode();
}

void Visitor::PrintAST::Visit(Expr::lvalue *that) {
  int node = CreateNodeAndLink("lvalue");
  
  PushNode(node);
  that->id->Accept(this);
  PopNode();
}

void Visitor::PrintAST::Visit(Expr::rvalue *that) {
  int node = CreateNodeAndLink("rvalue");
  
  PushNode(node);
  if (that->id != nullptr) {
    that->id->Accept(this);
  }
  if (that->literal != nullptr) {
    that->literal->Accept(this);
  }
  PopNode();
}

void Visitor::PrintAST::Visit(Expr::UnaryOp *that) {
  int node = CreateNodeAndLink(Repr(that->type));
  
  PushNode(node);
  that->expr->Accept(this);
  PopNode();
}

void Visitor::PrintAST::Visit(Stmt::Assign *that) {
  int node = CreateNodeAndLink("=");
  
  PushNode(node);
  that->lvalue->Accept(this);
  that->expr->Accept(this);
  PopNode();
}

void Visitor::PrintAST::Visit(Stmt::Cond *that) {
  int node = CreateNodeAndLink("IfElse");
  
  PushNode(node);
  that->condition->Accept(this);
  that->stmt_true->Accept(this);
  if (that->stmt_false) {
    that->stmt_false->Accept(this);
  }
  PopNode();
}

void Visitor::PrintAST::Visit(Stmt::Print *that) {
  int node = CreateNodeAndLink("println");
  
  PushNode(node);
  that->expr->Accept(this);
  PopNode();
}

void Visitor::PrintAST::Visit(Stmt::Ret *that) {
  int node = CreateNodeAndLink("return");
  
  PushNode(node);
  that->expr->Accept(this);
  PopNode();
}

void Visitor::PrintAST::Visit(Stmt::List *that) {
  int node = CreateNodeAndLink("StmtList");
  
  PushNode(node);
  for (Stmt::Base* stmt : that->list) {
    stmt->Accept(this);
  }
  PopNode();
}

void Visitor::PrintAST::Visit(Stmt::VarDecl *that) {
  int node = CreateNodeAndLink("VarDecl");
  PushNode(node);
  that->ident->Accept(this);
  PopNode();
}

void Visitor::PrintAST::PushNode(int node) {
  node_stack_.push(node);
}

void Visitor::PrintAST::PopNode() {
  node_stack_.pop();
}

int Visitor::PrintAST::Parent() {
  return node_stack_.top();
}

int Visitor::PrintAST::CreateNodeAndLink(const std::string &label) {
  int node = NewNode();
  int parent = Parent();
  PrintNode(node, label);
  PrintEdge(parent, node);
  return node;
}




