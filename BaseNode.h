//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once
#include "Visitor/Visitor.h"

class BaseNode {
 public:
  virtual void Accept(Visitor::Base* visitor) = 0;
  virtual ~BaseNode() = default;
};
