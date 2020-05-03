//
// Created by Igor Maximov on 03.05.2020.
//

#include "ScopeLayer.h"

#pragma once

class ScopeLayerTree {
 public:
  explicit ScopeLayerTree(ScopeLayer* root) : root(root) {}
  
 public:
  ScopeLayer* root;
};