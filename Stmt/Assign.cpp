//
// Created by Igor Maximov on 03.04.2020.
//

#include "Assign.h"

void Stmt::Assign::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}
