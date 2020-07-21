//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once
#include "SymbolTable/Symbol.h"
#include "MemPtr.h"
#include "SymbolTable/Symbol.h"

#include <stack>

namespace IR {

class Frame {
 public:
  Frame(Symbol method);
  
  struct Scope {
    std::stack<Symbol> vars;
  };
  
  MemPtr* GetRetValueAddress() const;
  MemPtr* GetFramePointer() const;
  MemPtr* GetAddress(Symbol symbol) const;
  
  void AddVariable(Symbol symbol);
  
  void StartScope();
  void ExitScope();
  
  Scope GetCurrentScope();
 
 private:
  std::unordered_map<Symbol, MemPtr*> addresses_;
  
  std::stack<Scope> scopes_;
  
  void AddSymbolToCurrentScope(Symbol symbol);
  
  MemPtr* frame_pointer = nullptr;
  MemPtr* return_value_address = nullptr;
  MemPtr* return_address = nullptr;
  
  const int word_size = 8;
  const Symbol method;
  
  int current_offset = 3;
  
  int GetOffset() const;
};

}
