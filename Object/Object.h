//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include <Type/Type.h>

class Object {
 public:
  // explicit Object(Type* type) : type(type) {}
  Object() = default;
  
  virtual ~Object() = default;
  
  virtual int ToInt() = 0;
};
