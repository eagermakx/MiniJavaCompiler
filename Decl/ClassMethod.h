//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include "Base.h"
#include "ClassMember.h"
#include "Functions/FuncParameter.h"

#include <string>

class Class;

class ClassMethod : public Decl::Base {
 public:
  ClassMethod(Type* out, std::string name, FuncParamList* params, Stmt::List* list, bool is_static = false);
  
  void Accept(Visitor::Base *visitor) override;
  
  std::string Representation();
 
 public:
  Type* out;
  std::string name;
  std::vector<FuncParameter> parameters;
  Stmt::List* statements;
  
  bool is_static{false};
};
