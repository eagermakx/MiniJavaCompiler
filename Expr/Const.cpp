//
// Created by Igor Maximov on 09.05.2020.
//

#include "Const.h"

void Expr::Const::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}