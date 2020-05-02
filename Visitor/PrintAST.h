//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

#include "Visitor.h"
#include "BaseNode.h"
#include <string>
#include <fstream>
#include <stack>
#include "Program.h"

namespace Visitor {
  class PrintAST : public Visitor::Base {
   public:
    explicit PrintAST(const std::string& filename);
    ~PrintAST();
    
    void Run(Program* program);
  
    void Visit(Program* program) override;
    void Visit(Entity::Const* that) override;
    void Visit(Entity::Id* that) override;
    void Visit(Expr::BinaryOp* that) override;
    void Visit(Expr::lvalue* that) override;
    void Visit(Expr::rvalue* that) override;
    void Visit(Expr::UnaryOp* that) override;
    void Visit(Stmt::Assign* that) override;
    void Visit(Stmt::Cond* that) override;
    void Visit(Stmt::Print* that) override;
    void Visit(Stmt::Ret* that) override;
    void Visit(Stmt::List* that) override;
    void Visit(Stmt::VarDecl* that) override;
 
   private:
    void GraphPrologue();
    void GraphEpilogue();
    
    void PrintEdge(int from, int to);
    void PrintNode(int node, const std::string& label);
    
    int CreateNodeAndLink(const std::string& label);
    
    int NewNode();
    void PushNode(int node);
    void PopNode();
    int Parent();
    
    int max_node = 0;
    std::stack<int> node_stack_;
    std::ofstream stream_;
  };
}