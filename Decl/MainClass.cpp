//
// Created by Igor Maximov on 10.05.2020.
//

#include "MainClass.h"
#include "ClassMethod.h"
#include "Functions/FuncParamList.h"
#include "Type/Void.h"

MainClass::MainClass(std::string name, Stmt::List *main_method) : Class(std::move(name)) {
  auto* empty_list = new FuncParamList;
  auto* method = new ClassMethod(new Void(), "main", empty_list, main_method, true);
  methods.push_back(method);
}

ClassMethod *MainClass::GetMainFunction() {
  return methods[0];
}

void MainClass::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}
