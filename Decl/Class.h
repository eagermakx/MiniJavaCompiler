//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include "Base.h"
#include "ClassMethod.h"
#include "ClassField.h"

#include <string>
#include <vector>

class Class : public Decl::Base {
 public:
  Class(std::string name, ClassBody* body);
  explicit Class(std::string name);
  
  void Accept(Visitor::Base *visitor) override;
 
 public:
  std::string name;
  std::vector<ClassMethod*> methods;
  std::vector<ClassField*> fields;
};
