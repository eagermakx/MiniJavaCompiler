//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include <Type/Type.h>

class Object {
 public:
  explicit Object(Type* type) : type(type) {}
  
  virtual ~Object() = default;
  virtual int ToInt() = 0;
  
  Type* type;
};

std::shared_ptr<Object> CreateObjectFromType(Type *type);

std::shared_ptr<Object> CreateObjectFromType(Type *type, int value);

