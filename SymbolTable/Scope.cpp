//
// Created by Igor Maximov on 10.05.2020.
//

#include "Scope.h"

ScopeId GenerateId() {
  static ScopeId current_id = 0;
  return current_id++;
}

Scope::Scope(Scope *parent) : id_(GenerateId()), parent_(parent) {
  GenerateFullLabel();
}

Scope::Scope() : id_(GenerateId()) {
  GenerateFullLabel();
}

std::string Scope::GetName() const {
  return name_;
}

void Scope::SetLabel(const char *new_label) {
  name_ = new_label;
  GenerateFullLabel();
}

ScopeId Scope::GetId() const {
  return id_;
}

std::string Scope::GetFullLabel() const {
  return full_path_;
}

void Scope::GenerateFullLabel() {
  std::string prefix = parent_ ? parent_->GetFullLabel() : "";
  if (!prefix.empty()) {
    prefix += "::";
  }
  
  std::string suffix = name_.empty() ? std::to_string(id_) : name_;
  
  full_path_ = prefix + suffix;
}

