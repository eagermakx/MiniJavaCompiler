//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "BaseNode.h"
#include "Visitor/Visitor.h"

namespace Expr {
  class Base : public BaseNode {
   public:
    virtual int eval() const = 0;
  };
}