#include "Symbol.h"

#include <iostream>

Symbol::Symbol(Scope* scope, std::string name) : parent_scope_(scope) {
  label_ = std::to_string(scope->GetId()) + "_" + scope->Label() + "::" + name;
}

// Symbol::Symbol(const Symbol& symbol): name_(symbol.name_) {}

bool Symbol::operator==(const Symbol& other) const {
  return label_ == other.label_;
}

bool Symbol::operator!=(const Symbol& other) const {
  return label_ != other.label_;
}

const char* Symbol::GetName() const {
  return label_.c_str();
}

void Symbol::Reset(Scope *scope, std::string name) {
  parent_scope_ = scope;
  label_ = std::to_string(scope->GetId()) + "_" + scope->Label() + "::" + name;
}

Scope *Symbol::GetParentScope() const {
  return parent_scope_;
}

void Symbol::AssignLabel(std::string new_label) {
  label_ = std::move(new_label);
}

const char* Symbol::GetLabel() {
  return label_.c_str();
}
