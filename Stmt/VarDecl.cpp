//
// Created by Igor Maximov on 03.04.2020.
//

#include "VarDecl.h"

namespace Stmt {
  void VarDecl::Accept(Visitor::Base *visitor) {
    visitor->Visit(this);
  }
}