#include "cpptcl.h"
#include <future>

class TCLInterpreter {
  private: 
    Tcl::interpreter* i;
    std::future<std::invoke_result_t<
     
    
  public:
    TCLInterpreter();
    void update();
}
