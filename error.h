//
// Created by Igor Maximov on 04.05.2020.
//

#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>
#include <iostream>

/*
class compilation_error : public std::exception {
 public:
  explicit compilation_error(std::string msg) : err_msg_(std::move(msg)) {}
  
  const char* what() const noexcept override;
  
 private:
  std::string err_msg_;
};

const char *compilation_error::what() const noexcept {
  return err_msg_.c_str();
}*/

#define ERROR(msg, loc) { std::cerr << "[!] " << msg << " at \'" << loc << "\'" << std::endl; exit(1); }

#endif // ERROR_H