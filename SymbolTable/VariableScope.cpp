//
// Created by Igor Maximov on 03.05.2020.
//

#include "VariableScope.h"
#include "error.h"
#include "Object/UninitObject.h"

VariableScope::VariableScope(VariableScope *parent) : Scope(parent) {
}

VariableScope::VariableScope() : Scope() {
}

bool VariableScope::Exists(const std::string& variable) const {
  return existing_variables_.find(variable) != existing_variables_.end();
}

void VariableScope::DefineVariable(const std::string &variable) {
  if (Exists(variable)) {
    ERROR("Redefenition of existing variable", "Scope::Declare");
  }
  
  existing_variables_.insert(variable);
  variables_.push_back(variable);
}



