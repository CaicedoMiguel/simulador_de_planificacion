#ifndef MLFQ_H
#define MLFQ_H

#include <iostream>
#include <queue>
#include <vector>
#include "Process.h"
using namespace std;

class MLFQ {
  private:
    vector<queue<Process*>>& colas;
    //int totalBurstTime;
  public:
    MLFQ(vector<queue<Process*>>& colas);
    virtual ~MLFQ();
    virtual void agregarProceso(Process* p);
    virtual void ejecutar();
};

#else
class MLFQ;  
#endif