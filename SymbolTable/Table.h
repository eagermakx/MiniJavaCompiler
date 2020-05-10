//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once

#include "Scope.h"
#include "ScopeTree.h"
#include "Symbol.h"
#include "Decl/ClassMethod.h"
#include "Decl/ClassField.h"
#include "Decl/Class.h"

#include <unordered_map>

class Table {
 public:
  struct SymbolInfo {
    BaseNode* assigned_node;
    Symbol::SymbolType type;
  };
  
 public:
  Table() = default;
  
  void AddClassMethod(ClassMethod* method, Class* owner);
  void AddClassField(ClassField* field, Class* owner);
  void AddClass(Class* c);
  
  bool IsDefined(Symbol* symbol, Symbol::SymbolType type);
 
 private:
  void AddSymbol(Symbol* symbol, BaseNode* node, Symbol::SymbolType type);
  void AssignSymbol(Symbol* symbol, const std::string& name, Scope* parent);
  
 private:
  std::unordered_map<Symbol, SymbolInfo> hash_map_;
};

