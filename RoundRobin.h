#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H
#include <vector>
#include "Process.h"
using namespace std;

class roundRobin{
  public:
  virtual void executeRoundRobin(vector<Process>& processes, int  quantum);
};

#else
class roundRobin;  
#endif
