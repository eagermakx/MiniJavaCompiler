//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include <Decl/Class.h>
#include "Object.h"

class ClassObject {
 public:
  explicit ClassObject(Class* class_);
  ~ClassObject() = default;
  
  std::shared_ptr<Object> AccessField(ClassField* field);
 
  static std::shared_ptr<Object> ObjectFromType(Type* type);
  
 public:
  Class* instance_of;
 
 private:
  std::vector<std::shared_ptr<Object>> fields;
};
