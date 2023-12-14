#ifndef FIFO_H
#define FIFO_H
#include "Process.h"
#include <vector>
using namespace std;

class Fifo {
  public:
  virtual void executeFIFO(vector<Process>& processes);
};

#else
class Fifo;  
#endif

