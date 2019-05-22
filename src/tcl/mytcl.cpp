#include "mytcl.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace Tcl;

std::string GetLineFromCin() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void hello() { std::cout << "Hello C++/Tcl!" << std::endl; }

TCLInterpreter::TCLInterpreter(){
  future = std::async(std::launch::async, GetLineFromCin);
  Tcl_Interp * interp = Tcl_CreateInterpWithStubs("8.6", 0);
	i = Tcl::Interpreter(interp, true);
	i.def("hello", hello);
}

TCLInterpreter::update(){
  if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    auto line = future.get();     
    future = std::async(std::launch::async, GetLineFromCin);
    i.eval(line);
  }
}
