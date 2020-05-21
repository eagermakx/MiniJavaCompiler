//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include "Object.h"
#include <Type/Types.h>

class Boolean : public Object {
 public:
  explicit Boolean(bool val) : Object(new Bool()), value_(val) {}
  
  int ToInt() override;
 
 private:
  bool value_;
};
