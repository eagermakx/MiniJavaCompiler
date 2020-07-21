#pragma once

#include <string>

namespace IR {

class Label {
 public:
  Label();
  explicit Label(std::string labelname);
  
  std::string ToString() const;
 
 private:
  std::string labelname_;
};

}
