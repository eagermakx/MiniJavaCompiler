#pragma once

#include <string>

namespace IR {

class Temp {
 public:
  
  Temp();
  explicit Temp(std::string name);
  
  std::string ToString() const;
 
 private:
  std::string name_;
};

}
