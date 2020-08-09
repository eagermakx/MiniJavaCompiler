//
// Created by Igor Maximov on 19.07.2020.
//

#pragma once
#include "MemPtr.h"
#include "IR/generators/Temp.h"

namespace IR {

class RegisterMemPtr : public MemPtr {
 public:
  explicit RegisterMemPtr(std::string name) : name_(std::move(name)) {}
  BaseExp* ToExp() override;
 
 private:
  std::string name_;
};

}
