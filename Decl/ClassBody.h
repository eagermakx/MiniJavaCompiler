//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include "Base.h"

#include <string>
#include <vector>

class ClassBody {
 public:
  void AddMethod(ClassMethod*);
  void AddField(ClassField*);
 
 public:
  std::vector<ClassMethod*> methods;
  std::vector<ClassField*> fields;
};

