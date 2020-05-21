//
// Created by Igor Maximov on 11.05.2020.
//

#include "ExprStmt.h"

namespace Stmt {

void ExprStmt::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

}
