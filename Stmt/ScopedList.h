//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include <vector>
#include "Stmt.h"

class Scope;

namespace Stmt {

class ScopedList : public Stmt::Base {
 public:
  explicit ScopedList(Stmt::List *list) : list(list) {}
  
  void Accept(Visitor::Base *visitor) override;
 
 public:
  Stmt::List *list;
  Scope* scope;
};

} // namespace Stmt