//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "BaseNode.h"
#include "Visitor/Visitor.h"
#include "Type/Type.h"

namespace Expr {

class Base : public BaseNode {
 public:
  Type* type{nullptr};
};

}