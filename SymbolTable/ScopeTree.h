//
// Created by Igor Maximov on 03.05.2020.
//


#pragma once

#include "Scope.h"
#include <unordered_map>
#include <string>
#include <stack>

class ScopeTree {
 public:
  explicit ScopeTree(Scope* root) : root(root) {}
  
  void DefineVariable(Scope* layer, const std::string& variable);
  Scope* TopDefinitionLayer(const std::string& variable);
  
  Scope* root;

  bool VariableDefined(const std::string& variable);
  
  std::unordered_map<std::string, std::stack<Scope*>> scope_shadowing_map_;
};