#include <driver.hh>
#include <parser.hh>
#include <Visitor/PrintAST.h>
#include <Visitor/Executor.h>
#include <Visitor/SymbolTableBuilder.h>
#include <Visitor/TypeChecker.h>
#include <log.h>

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
    variables["one"] = 1;
    variables["two"] = 2;
}


int Driver::Parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end();
  
    Table symbol_table;
    
    Visitor::SymbolTableBuilder symtable_builder(&symbol_table);
    symtable_builder.Process(program);
    
    Visitor::TypeChecker type_checker(&symbol_table);
    type_checker.Run(program);
    
    return res;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);
    LOG(file);
    scanner.yyrestart(&stream);
  }
}


void Driver::scan_end()
{
    stream.close();
}

void Driver::PrintAST(const std::string& filename) {
  Visitor::PrintAST printer(filename);
  printer.Run(program);
}

int Driver::Run() {
  Visitor::Executor interpreter;
  return interpreter.Run(program);
}

