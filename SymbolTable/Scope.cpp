//
// Created by Igor Maximov on 03.05.2020.
//

#include "Scope.h"
#include "error.h"
#include "Object/UninitObject.h"

Scope::Scope(Scope *parent) : parent_(parent), tree_(parent->tree_) {
}

Scope::Scope(ScopeTree& tree) : tree_(tree) {
}

bool Scope::Exists(const std::string& variable) const {
  return variable_value_.find(variable) != variable_value_.end();
}

void Scope::Set(const std::string& variable, std::shared_ptr<Object> object) {
  if (!Exists(variable)) {
    ERROR("Assignment to undefined variable", "Scope::Set");
  }
  
  variable_value_[variable] = std::move(object);
}

std::shared_ptr<Object> Scope::Get(const std::string &variable) const {
  if (!Exists(variable)) {
    ERROR("Access to undefined variable", "Scope::Get");
  }
  
  return variable_value_.at(variable);
}

void Scope::DefineVariable(const std::string &variable) {
  if (Exists(variable)) {
    ERROR("Redefenition of existing variable", "Scope::Declare");
  }
  
  variable_value_.insert({variable, std::make_shared<UninitObject>()});
  variables_.push_back(variable);
}

void Scope::AddChild(Scope *child) {
  children_.push_back(child);
}

Scope *Scope::GetChild(size_t index) const {
  return children_[index];
}

Scope *Scope::GetParent() const {
  return parent_;
}

const char* Scope::Label() const {
  return layer_label_.c_str();
}

void Scope::SetLabel(const char* new_label) {
  layer_label_ = new_label;
}

