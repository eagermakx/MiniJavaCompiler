//
// Created by Igor Maximov on 21.07.2020.
//

#pragma once
#include "IR/Visitors/Base.h"

namespace IR {

class BaseNode {
 public:
  virtual void Accept(IR::Visitor::Base* visitor) = 0;
  virtual ~BaseNode() = default;
};

}