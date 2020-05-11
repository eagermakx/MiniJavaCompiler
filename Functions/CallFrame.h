//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include <Decl/ClassMethod.h>
#include <Decl/Class.h>

#include <Object/Object.h>
#include <unordered_map>

class CallFrame {
 public:
  CallFrame(Class* cls, ClassMethod* method);
  
  void PassParameters(std::vector<std::shared_ptr<Object>>&& parameters);
  void SetThis(std::shared_ptr<Object> object);
  void SetParentFrame(CallFrame* parent);
  
  void VarSet(std::shared_ptr<Object> new_val, const std::string &name);
  std::shared_ptr<Object> VarGet(const std::string& name);
  bool VarExists(const std::string& name);
  void AddVariable(const std::string& name);
  
  void SetReturnValue(std::shared_ptr<Object> object);
 
 public:
  std::shared_ptr<Object> return_value{nullptr};
  
 private:
  std::unordered_map<std::string, std::shared_ptr<Object>> variables_;
  std::shared_ptr<Object> self_{nullptr};
  
  CallFrame* parent_{nullptr};
  
  ClassMethod* method_;
  Class* cls_;
};