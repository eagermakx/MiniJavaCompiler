//
// Created by Igor Maximov on 10.05.2020.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

class ScopeTree;

using ScopeId = size_t;

class Scope {
 public:
  explicit Scope(Scope* parent);
  Scope();
  
  std::string GetName() const;
  std::string GetFullLabel() const;
  
  void SetLabel(const char* new_label);
  void GenerateFullLabel();
  
  ScopeId GetId() const;
 private:
  ScopeId id_;
  Scope* parent_{nullptr};
  
  std::string name_;
  std::string full_path_;
};