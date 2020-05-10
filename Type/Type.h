//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once

class Void;
class Int;
class Bool;

struct Type {
  enum class PossibleTypes {
    Int,
    Bool,
    Void,
    UserClass
  };
  
  explicit Type(PossibleTypes type) : type(type) {}
  
  PossibleTypes type;
};