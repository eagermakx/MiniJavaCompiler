//
// Created by Igor Maximov on 09.08.2020.
//

#pragma once
#include <IR/BaseExp.h>
#include <string>
#include <IR/Visitors/Base.h>

namespace IR {

class Register : public IR::BaseExp {
 public:
  explicit Register(const std::string& name) : name_(name) {}
  std::string name_;
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
};

}