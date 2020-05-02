//
// Created by Igor Maximov on 03.04.2020.
//

#include "Print.h"

namespace Stmt {
  void Print::Accept(Visitor::Base *visitor) {
    visitor->Visit(this);
  }
}