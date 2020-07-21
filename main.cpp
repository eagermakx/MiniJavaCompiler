#include <iostream>
#include <driver.hh>
#include "SymbolTable/Symbol.h"
#include "log.h"

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
    bool print_ir = false;
    std::string ast_output;
    std::string ir_output;

    for (int i = 2; i < argc; ++i) {
        if (argv[i] == std::string("-p")) {
          driver.trace_parsing = true;
        } else if (argv[i] == std::string("-s")) {
          driver.trace_scanning = true;
        } else if (argv[i] == std::string("--ast")) {
          print_ast = true;
          ast_output = argv[i + 1];
          ++i;
        } else if (argv[i] == std::string("--ir")) {
          print_ir = true;
          ir_output = argv[i + 1];
          ++i;
        }
    }
    
    if (!driver.Parse(source_file)) {
      LOG("[*] Parsed successfully (returned " << driver.result << ")");
      
      if (print_ast || print_ir) {
        
        if (print_ast) {
          LOG("[*] Processing AST... ");
          driver.PrintAST(ast_output);
        }
        
        if (print_ir) {
          LOG("[*] Processing IR... ");
          driver.PrintIR(ir_output);
        }
        
        result = 0;
        
      } else {
        LOG("[*] Running... ");
        result = driver.Run();
        std::cout << "Process finished with exit code " << result << std::endl;
      }
      
    } else {
      std::cerr << "[!] Compilation failed" << std::endl;
      return 1;
    }

    return 0;
}