//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include "Base.h"
#include "ClassMethod.h"
#include "ClassField.h"

#include <string>
#include <vector>
#include <unordered_map>

class Class : public Decl::Base {
 public:
  Class(std::string name, ClassBody* body);
  explicit Class(std::string name);
  
  void Accept(Visitor::Base *visitor) override;
  
  size_t EvaluateObjectSize();
  
  bool FieldExists(ClassField* field) const;
  size_t GetFieldOffset(ClassField* field) const;
 
 public:
  std::string name;
  std::vector<ClassMethod*> methods;
  std::vector<ClassField*> fields;
 
 private:
  std::unordered_map<ClassField*, size_t> fields_offsets;
};
