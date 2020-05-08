#include "Symbol.h"

#include <iostream>

Symbol::Symbol(Scope* scope, std::string name) : parent_scope_(scope) {
  label_ = std::to_string(parent_scope_->GetId()) + "_" + scope->Label() + "::" + name;
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