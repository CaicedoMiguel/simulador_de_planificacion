#ifndef PROCESS_H
#define PROCESS_H

const int MAX_PRIORITY = 10; // Valor máximo de prioridad

#include <string>
using namespace std;

class Process {
  private:
    int id;
    int arrivalTime;
    int burstTime;
    int quantum;
    int priority;
    int completionTime;
  public:
    Process(int id, int arrivalTime, int burstTime, int quantum=0, int priority=0);
    virtual ~Process();
    virtual void setBurstTime(int burst);
    virtual void setQuantum(int q);
    virtual void setPriority(int p);
    virtual void setCompletionTime(int time);
    virtual void incrementPriority();
    virtual void decrementPriority();
    virtual int getId() const;
    virtual int getArrivalTime() const;
    virtual void setArrivalTime(int time);
    virtual  int getBurstTime() const;
    virtual int getQuantum() const;
    virtual int getTurnAround() const;
    virtual int getWaitingTime() const;
    virtual int getPriority() const;
    virtual void execute();
    virtual int getCompletionTime() const;
};

#else
class Process;  
#endif