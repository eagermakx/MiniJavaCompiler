//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once

class ClassMember {
 public:
  enum class Type {
    Method,
    Field
  };
  
  explicit ClassMember(Type type) : type(type) {}
  
 public:
  Type type;
};
