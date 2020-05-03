//
// Created by Igor Maximov on 03.05.2020.
//

#include "ScopedList.h"

void Stmt::ScopedList::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}
