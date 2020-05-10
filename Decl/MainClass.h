//
// Created by Igor Maximov on 10.05.2020.
//

#pragma once
#include "Class.h"

class MainClass : public Class {
 public:
  MainClass(std::string name, Stmt::List* main_method);
  
  ClassMethod* GetMainFunction();
};
