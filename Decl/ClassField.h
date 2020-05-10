//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include "Base.h"
#include "ClassMember.h"

#include <string>

class ClassField : public Decl::Base {
 public:
  ClassField(Type* type, std::string label);
  
  void Accept(Visitor::Base *visitor) override;
 
 public:
  std::string name;
  Type* type;
};

