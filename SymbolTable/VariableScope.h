//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "Scope.h"

class VariableScope : public Scope {
 public:
  explicit VariableScope(VariableScope* parent);
  VariableScope();
 
  bool Exists(const std::string&) const;
  void DefineVariable(const std::string &variable);
 
 public:
  std::vector<std::string> variables_;
  
 private:
  std::unordered_set<std::string> existing_variables_;
};
