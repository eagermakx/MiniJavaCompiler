#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "SymbolTable/Scope.h"

class Symbol {
 public:
  using SymbolId = uint64_t;
  
  enum class SymbolType {
    Var,
    Field,
    Method,
    Class
  };
  
 public:
  explicit Symbol(Scope* scope, std::string name);
  
  Symbol() = default;
  Symbol(Symbol&& other) noexcept = default;
  Symbol(const Symbol& other) = default;
  
  Symbol& operator= (Symbol&& other) = default;
  
  void Reset(Scope* parent_scope, std::string new_label);
  
  bool operator==(const Symbol& other) const;
  bool operator!=(const Symbol& other) const;
  
  const char* GetName() const;
  Scope* GetParentScope() const;
  
 private:
  Scope* parent_scope_{nullptr};
  std::string label_;
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

