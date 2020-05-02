//
// Created by Igor Maximov on 04.04.2020.
//

#include "Cond.h"

void Stmt::Cond::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}
