#include <iostream>
#include <driver.hh>
#include "SymbolTable/Symbol.h"

// Config to print ast : ../java_examples/if_else.java --ast ../TestOutput/if_else.dot

int main(int argc, char** argv) {
    int result = 0;
    Driver driver;
    
    if (argc < 2) {
      std::cout << "Usage: <source> <parameters>" << std::endl;
      exit(1);
    }
    
    std::string source_file;
    source_file = argv[1];
    
    bool print_ast = false;
    std::string ast_output;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p")) {
          driver.trace_parsing = true;
        } else if (argv[i] == std::string("-s")) {
          driver.trace_scanning = true;
        } else if (argv[i] == std::string("--ast")) {
          print_ast = true;
          ast_output = argv[i + 1];
        }
    }
    
    if (!driver.Parse(source_file)) {
      std::cout << "[*] Parsed successfully (returned " << driver.result << ")" << std::endl;
      
      if (print_ast) {
        std::cout << "[*] Processing AST... " << std::endl;
        driver.PrintAST(ast_output);
        result = 0;
      } else {
        std::cout << "[*] Running... " << std::endl;
        result = driver.Run();
        std::cout << "Process finished with exit code " << result << std::endl;
      }
    } else {
      std::cerr << "[!] Compilation failed" << std::endl;
      return 1;
    }

    return 0;
}