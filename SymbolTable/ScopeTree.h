//
// Created by Igor Maximov on 03.05.2020.
//


#pragma once

#include "VariableScope.h"
#include <unordered_map>
#include <string>
#include <stack>

class ScopeTree {
 public:
  explicit ScopeTree(VariableScope* root) : root(root) {}
  
  void DefineVariable(VariableScope* layer, const std::string& variable);
  VariableScope* TopDefinitionLayer(const std::string& variable);
  
  VariableScope* root;

  bool VariableDefined(const std::string& variable);
  
  std::unordered_map<std::string, std::stack<VariableScope*>> scope_shadowing_map_;
};