#include <iostream>
#include <driver.hh>

// Config to print ast : ../java_examples/if_else.java --ast ../TestOutput/if_else.dot

int main(int argc, char** argv) {
    int result = 0;
    Driver driver;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p")) {
            driver.trace_parsing = true;
        } else if (argv[i] == std::string("-s")) {
            driver.trace_scanning = true;
        } else if (argv[i] == std::string("--ast")) {
            driver.PrintAST(argv[i + 1]);
            ++i;
        } else if (!driver.parse(argv[i])) {
            std::cout << "[*] Parsed successfully (returned " << driver.result << ")" << std::endl;
            std::cout << "[*] Running... " << std::endl;
            
            int ret_value = driver.Run();
            std::cout << "Process finished with exit code " << ret_value << std::endl;
        } else {
            result = 1;
        }
    }

    return result;
}