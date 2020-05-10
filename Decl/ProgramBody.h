//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include "Class.h"

class ProgramBody {
 public:
  ProgramBody() = default;
  
  void AddClassDecl(Class* class_decl);
  
  std::vector<Class*> classes;
};
