//
// Created by Igor Maximov on 02.04.2020.
//

#pragma once

#include "ast_decl.h"
#include <vector>

class Class;
class ProgramBody;
class MainClass;

class Program {
 public:
  explicit Program(MainClass* main, ProgramBody* class_decls);
  
 public:
  std::vector<Class*> classes;
  MainClass* main_class;
};
