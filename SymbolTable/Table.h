//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include "Scope.h"
#include "ScopeTree.h"
#include "Symbol.h"

#include <unordered_map>

class Table {
 public:
  class SymbolInfo {
    off_t offset;
    int type;
  };
  
 public:
  Table() = default;
  
 private:
  ScopeTree* tree_;
  
  std::vector<Symbol> symbols_;
  std::unordered_map<Symbol, SymbolInfo> hash_map_;
};

