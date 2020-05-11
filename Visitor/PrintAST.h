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
  
    void Visit(Class* class_decl) override;
    void Visit(ClassMethod* method) override;
    void Visit(ClassField* field) override;
    void Visit(ProgramBody* body) override;
    void Visit(MainClass* main_class) override;
  
    void Visit(Expr::BinaryOp* binary_op) override;
    void Visit(Expr::Const* const_expr) override;
    void Visit(Expr::Id* rvalue) override;
    void Visit(Expr::This* this_expr) override;
    void Visit(Expr::UnaryOp* unary_op) override;
    void Visit(Expr::Call* call) override;
  
    void Visit(Stmt::Assign* assn) override;
    void Visit(Stmt::Cond* cond) override;
    void Visit(Stmt::Print* print) override;
    void Visit(Stmt::Ret* ret) override;
    void Visit(Stmt::List* list) override;
    void Visit(Stmt::VarDecl* var_decl) override;
    void Visit(Stmt::ScopedList* scoped_list) override;
    void Visit(Expr::New* new_stmt) override;
 
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