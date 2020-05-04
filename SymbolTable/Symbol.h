#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "SymbolTable/Scope.h"

class Symbol {
 public:
  using SymbolId = uint64_t;
  
 public:
  explicit Symbol(Scope* scope, std::string name);
  
  bool operator==(const Symbol& other) const;
  bool operator!=(const Symbol& other) const;
  
  const char* GetName() const;
  
 private:
  Scope* parent_scope_;
  std::string name_;
};

namespace std {
template<>
struct hash<Symbol>
{
  std::size_t operator()(const Symbol& other) const {
    return hash<string>()(other.GetName());
  }
};

}

