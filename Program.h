//
// Created by Igor Maximov on 02.04.2020.
//

#pragma once

#include "Stmt/List.h"

class Program {
 public:
  explicit Program(Stmt::List* list) : list(list) {}
  
 public:
  Stmt::List* list;
};
