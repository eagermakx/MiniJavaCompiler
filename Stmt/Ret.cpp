//
// Created by Igor Maximov on 03.04.2020.
//

#include "Ret.h"

namespace Stmt {
  void Ret::Accept(Visitor::Base *visitor) {
    visitor->Visit(this);
  }
}
