//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include <Decl/Class.h>
#include "Object.h"

class ClassObject : public Object {
 public:
  explicit ClassObject(Class* class_);
  ~ClassObject() override = default;
  
  std::shared_ptr<Object> AccessField(ClassField* field);
  
  int ToInt() override;
 
 public:
  Class* instance_of;
 
 private:
  std::vector<std::shared_ptr<Object>> fields;
};
