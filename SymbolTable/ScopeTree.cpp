//
// Created by Igor Maximov on 03.05.2020.
//

#include "ScopeTree.h"
#include "error.h"

void ScopeTree::DefineVariable(Scope *layer, const std::string& variable) {
  if (!VariableDefined(variable)) {
    // Add to stack
    scope_shadowing_map_.insert({variable, std::stack<Scope*>()});
  }
  
  layer->DefineVariable(variable);
  scope_shadowing_map_[variable].push(layer);
}

Scope *ScopeTree::TopDefinitionLayer(const std::string& variable) {
  if (!VariableDefined(variable)) {
    ERROR("Undefined variable", "ScopeLayerTree::TopDefinitionLayer");
  }
  
  return scope_shadowing_map_[variable].top();
}

bool ScopeTree::VariableDefined(const std::string& variable) {
  return scope_shadowing_map_.find(variable) != scope_shadowing_map_.end();
}
