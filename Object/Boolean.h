//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include "Object.h"

class Boolean : public Object {
 public:
  explicit Boolean(bool val) : value_(val) {}
  
  int ToInt() override;
 
 private:
  bool value_;
};
