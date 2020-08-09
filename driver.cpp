#include <driver.hh>
#include <parser.hh>
#include <Visitor/PrintAST.h>
#include <Visitor/Interpreter.h>
#include <Visitor/SymbolTableBuilder.h>
#include <Visitor/TypeChecker.h>
#include <log.h>

#include <IR/Visitors/PrintIR.h>
#include <IR/Visitors/CanonVisitor.h>
#include <IR/Visitors/Linearizer.h>
#include <IR/Visitors/DoubleCallElimination.h>
#include <IR/Visitors/BlockBuilder.h>
#include <IR/StmList.h>
#include <Visitor/IRTranslator.h>
#include <IR/BasicBlockScheduling.h>
#include <IR/assembly/InstSelection.h>

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
  Visitor::Interpreter interpreter;
  return interpreter.Run(program);
}

void Driver::PrintIR(const std::string &filename, bool canonize) {
  Visitor::IRTranslator translator;
  translator.Run(program);
  
  if (canonize) {
    IR::Visitor::DoubleCallElimination eliminator;
    eliminator.Run(translator.GetMapping());
  
    IR::Visitor::CanonVisitor canonizer;
    canonizer.Run(translator.GetMapping());
  
    IR::Visitor::Linearizer linearizer;
    IR::Visitor::Linearizer::List lin_out = linearizer.Run(translator.GetMapping());
    
    
    auto mapping = IR::BasicBlocksSplit(lin_out);
  
    for (auto& [label, block] : mapping) {
      std::cout << block.ToString() << std::endl;
    }
    
    std::cout << "Rescheduled:" << std::endl;
    
    std::vector<std::string> method_labels = IR::GetMethodLabels(lin_out);
    auto reordered = IR::TraceReschedule(mapping, method_labels);
    
    for (auto& block : reordered) {
      std::cout << block.ToString() << std::endl;
    }
    
    std::cout << "\n=== Assembly ===\n";
  
    for (auto& block : reordered) {
      for (auto& stm : block.Stmts()) {
        for (auto& inst : ASM::SelectInstructions(stm)) {
          std::cout << inst->format() << std::endl;
        }
      }
    }
  }
  
  IR::Visitor::PrintIR printer(filename);
  printer.Run(translator.GetMapping());
}

