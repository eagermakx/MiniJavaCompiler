//
// Created by Igor Maximov on 03.05.2020.
//

#pragma once
#include "Object/Object.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

class ScopeTree;

using ScopeId = size_t;

class Scope {
 public:
  explicit Scope(Scope* parent);
  Scope() = default;
 
  bool Exists(const std::string&) const;
  void DefineVariable(const std::string &variable);
  
  const char* Label() const;
  void SetLabel(const char* new_label);
  
  ScopeId GetId() const;
 
 public:
  std::vector<std::string> variables_;
  
 private:
  ScopeId id_;
  
  Scope* parent_{nullptr};
  std::unordered_set<std::string> existing_variables_;
  
  // std::unordered_map<std::string, std::shared_ptr<Object>> variable_value_;
  // std::unordered_map<std::string, size_t> offset_;
  std::string layer_label_;
};
