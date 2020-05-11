//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include "VariableScope.h"
#include "ScopeTree.h"
#include "Symbol.h"
#include "Decl/ClassMethod.h"
#include "Decl/ClassField.h"
#include "Decl/Class.h"

#include <unordered_map>

class Table {
 public:
  Table() = default;
  
  void AddClass(Class* cls);
  Class* FindClass(const std::string &name);
  bool ClassExists(const std::string &name);
  
  void AddMethod(Class* owner, ClassMethod* method);
  ClassMethod* FindMethod(Class* owner, const std::string& method_name);
  bool MethodExists(Class* owner, const std::string& method_name);
  
  void PrintTable();
 
 private:
  std::string MethodId(Class* owner, const std::string& method_name);
  
 private:
  std::unordered_map<std::string, Class*> defined_classes_;
  std::unordered_map<std::string, ClassMethod*> methods_;
};

