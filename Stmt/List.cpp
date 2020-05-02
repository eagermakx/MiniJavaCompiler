//
// Created by Igor Maximov on 04.04.2020.
//

#include "List.h"

namespace Stmt {
  void List::Accept(Visitor::Base *visitor) {
    visitor->Visit(this);
  }
  
  void List::AddStmt(Stmt::Base *stmt) {
    list.push_back(stmt);
  }
}
