#ifndef MLQ_H
#define MLQ_H

#include <vector>
#include <queue>
#include "Process.h" 

using namespace std;
class Mlq {
  public:
  virtual void executeMLQ(queue<Process>&     
  lowPriorityQueue,queue<Process>& 
  mediumPriorityQueue,queue<Process>& highPriorityQueue);
};

#else
class Mlq;  
#endif
