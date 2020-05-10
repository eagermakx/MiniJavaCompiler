//
// Created by Igor Maximov on 03.05.2020.
//

#include "Table.h"

void Table::AddClassMethod(ClassMethod *method, Class *owner) {
  if (!IsDefined(&owner->symbol, Symbol::SymbolType::Class)) {
    exit(1);
  }
  
  AssignSymbol(&method->symbol, method->name, owner->symbol.GetParentScope());
  AddSymbol(&method->symbol, method, Symbol::SymbolType::Method);
}

void Table::AddClassField(ClassField *field, Class *owner) {
  if (!IsDefined(&owner->symbol, Symbol::SymbolType::Class)) {
    exit(1);
  }
  
  AssignSymbol(&field->symbol, field->name, owner->symbol.GetParentScope());
  AddSymbol(&field->symbol, field, Symbol::SymbolType::Field);
}

void Table::AddClass(Class *c) {
  AssignSymbol(&c->symbol, c->name, nullptr);
  AddSymbol(&c->symbol, c, Symbol::SymbolType::Class);
}

bool Table::IsDefined(Symbol* symbol, Symbol::SymbolType type) {
  return (hash_map_.find(*symbol) != hash_map_.end());
}

void Table::AddSymbol(Symbol* symbol, BaseNode *node, Symbol::SymbolType type) {
  hash_map_.insert({*symbol, {node, type}});
}

void Table::AssignSymbol(Symbol *symbol, const std::string& name, Scope *parent) {
  symbol->Reset(parent, name);
}
