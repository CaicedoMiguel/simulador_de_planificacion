#ifndef SJN_H
#define SJN_H
#include "Process.h"
#include <vector>
using namespace std;

class Sjn{
  public:
  virtual void executeSJN(vector<Process>& processes);
};

#else
class Sjn;  
#endif