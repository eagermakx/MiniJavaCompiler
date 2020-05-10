//
// Created by Igor Maximov on 03.05.2020.
//

#include "Scope.h"
#include "error.h"
#include "Object/UninitObject.h"

ScopeId GenerateId() {
  static ScopeId current_id = 0;
  return current_id++;
}

Scope::Scope(Scope *parent) : parent_(parent), id_(GenerateId()) {
}

bool Scope::Exists(const std::string& variable) const {
  return existing_variables_.find(variable) != existing_variables_.end();
}

void Scope::DefineVariable(const std::string &variable) {
  if (Exists(variable)) {
    ERROR("Redefenition of existing variable", "Scope::Declare");
  }
  
  existing_variables_.insert(variable);
  variables_.push_back(variable);
}

const char* Scope::Label() const {
  return layer_label_.c_str();
}

void Scope::SetLabel(const char* new_label) {
  layer_label_ = new_label;
}

ScopeId Scope::GetId() const {
  return id_;
}


