//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include "Object.h"

class Integer : public Object {
 public:
  explicit Integer(int val) : value_(val) {}
  
  int ToInt() override;
  
 private:
  int value_;
};
