//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once
#include "Symbol.h"
#include "Object/Object.h"

#include <vector>
#include <unordered_map>

class ScopeLayerTree;

class ScopeLayer {
 public:
  explicit ScopeLayer(ScopeLayer* parent);
  ScopeLayer() = default;
 
  bool Exists(Symbol symbol) const;
  void Set(Symbol symbol, std::shared_ptr<Object> object);
  std::shared_ptr<Object> Get(Symbol symbol) const;
  
  void Declare(Symbol symbol);
  
  void AddChild(ScopeLayer* child);
  ScopeLayer* GetChild(size_t index) const;
  ScopeLayer* GetParent() const;
  
 private:
  ScopeLayer* parent_{nullptr};
  std::vector<ScopeLayer*> children_;
  
  ScopeLayerTree& tree;
  
  std::unordered_map<Symbol, std::shared_ptr<Object>> value_;
  std::unordered_map<Symbol, size_t> offset_;
  std::vector<Symbol> symbols_;
  std::string layer_label_;
};
