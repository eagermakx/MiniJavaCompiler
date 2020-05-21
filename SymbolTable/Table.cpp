//
// Created by Igor Maximov on 03.05.2020.
//

#include "Table.h"
#include <iostream>

/*void Table::AddClassMethod(ClassMethod *method, Class *owner) {
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

void Table::AssignSymbol(Symbol *symbol, const std::string& name, VariableScope *parent) {
  symbol->Reset(parent, name);
}*/

void Table::AddClass(Class *cls) {
  defined_classes_.insert({cls->name, cls});
}

Class *Table::FindClass(const std::string &name) {
  assert(ClassExists(name));
  return defined_classes_.at(name);
}

bool Table::ClassExists(const std::string &name) {
  return defined_classes_.find(name) != defined_classes_.end();
}

void Table::PrintTable() {
  std::cout << "Defined classes: \n";
  for (auto pair : defined_classes_) {
    std::cout << "\tclass " << pair.first << std::endl;
  }
}

void Table::AddMethod(Class *owner, ClassMethod *method) {
  assert(owner && method);
  methods_.insert({MethodId(owner, method->name), method});
}

ClassMethod *Table::FindMethod(Class *owner, const std::string &method_name) {
  assert(MethodExists(owner, method_name));
  return methods_.at(MethodId(owner, method_name));
}

bool Table::MethodExists(Class *owner, const std::string &method_name) {
  return methods_.find(MethodId(owner, method_name)) != methods_.end();
}

std::string Table::MethodId(Class *owner, const std::string &method_name) {
  return owner->name + "::" + method_name;
}
