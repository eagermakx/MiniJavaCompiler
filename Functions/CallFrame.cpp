//
// Created by Igor Maximov on 08.05.2020.
//

#include "CallFrame.h"

#include <iostream>
#include <Object/UninitObject.h>

CallFrame::CallFrame(Class *cls, ClassMethod *method) : cls_(cls), method_(method) {
}

void CallFrame::PassParameters(std::vector<std::shared_ptr<Object>>&& parameters) {
  auto params = std::move(parameters);
  
  int num_params_passed = params.size();
  int num_params_real = method_->parameters.size();
  
  if (num_params_passed != num_params_real) {
    std::cerr << cls_->name << "." << method_->name << " : expected "
              << num_params_real << " params, got " << num_params_passed << std::endl;
  }
  
  for (int i = 0; i < num_params_real; ++i) {
    assert(SameType(params[i]->type, method_->parameters[i].type));
    AddVariable(method_->parameters[i].name);
    VarSet(params[i], method_->parameters[i].name);
  }
}

void CallFrame::SetThis(std::shared_ptr<Object> object) {
  self_ = std::move(object);
}

void CallFrame::SetParentFrame(CallFrame *parent) {
  parent_ = parent;
}

void CallFrame::VarSet(std::shared_ptr<Object> new_val, const std::string &name) {
  if (!VarExists(name)) {
    std::cerr << "Variable not found in call frame. Something went horribly wrong." << std::endl;
    exit(1);
  }
  
  variables_[name] = std::move(new_val);
}

std::shared_ptr<Object> CallFrame::VarGet(const std::string &name) {
  if (!VarExists(name)) {
    std::cerr << "Variable not found in call frame. Something went horribly wrong." << std::endl;
    exit(1);
  }
  
  return variables_.at(name);
}

bool CallFrame::VarExists(const std::string &name) {
  return variables_.find(name) != variables_.end();
}

void CallFrame::AddVariable(const std::string &name) {
  variables_.insert({name, std::make_shared<UninitObject>()});
}

void CallFrame::SetReturnValue(std::shared_ptr<Object> object) {
  return_value = std::move(object);
}
