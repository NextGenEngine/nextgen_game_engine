#include "lib/std_ext.h"

class Job : nextgen::lib::std_ext::InterfaceBase {
 public:
  virtual void execute() = 0;  // Pure virtual function making Job an interface
};
