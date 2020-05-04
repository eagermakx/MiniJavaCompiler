#include "Symbol.h"

#include <iostream>

Symbol::SymbolId GenerateId() {
  static Symbol::SymbolId current_id = 0;
  return current_id++;
}

Symbol::Symbol(Scope* scope, std::string name) : parent_scope_(scope), id_(GenerateId()) {
  name_ = std::to_string(id_) + "_" + scope->Label() + "::" + name;
}

// Symbol::Symbol(const Symbol& symbol): name_(symbol.name_) {}

bool Symbol::operator==(const Symbol& other) const {
  return name_ == other.name_;
}

bool Symbol::operator!=(const Symbol& other) const {
  return name_ != other.name_;
}

const char* Symbol::GetName() const {
  return name_.c_str();
}
