#include "Process.h"

Process::Process(int id, int arrivalTime, int burstTime, int quantum, int priority)
    : id(id), arrivalTime(arrivalTime), burstTime(burstTime), quantum(quantum), priority(priority), completionTime(-1) {}

int Process::getId() const {
  return id;
}

void Process::setArrivalTime(int time) { 
  arrivalTime = time;
}

int Process::getArrivalTime() const {
  return arrivalTime;
}

int Process::getBurstTime() const {
  return burstTime;
}

int Process::getQuantum() const {
  return quantum;
}

void Process::setQuantum(int q) {
  quantum = q;
}

void Process::setBurstTime(int burst) {
  burstTime = burst;
}

int Process::getTurnAround() const {
  return burstTime;
}

int Process::getWaitingTime() const {
  return getTurnAround() - burstTime;
}

void Process::setPriority(int p) {
  if (p >= 0 && p <= MAX_PRIORITY) {
    priority = p;
  }
}

int Process::getPriority() const {
  return priority;
}

void Process::setCompletionTime(int time) {
  completionTime = time;
}

int Process::getCompletionTime() const {
  return completionTime;
}

void Process::incrementPriority() {
  if (priority < MAX_PRIORITY) {
    priority++;
  }
}

void Process::decrementPriority() {
  if (priority > 0) {
    priority--;
  }
}

void Process::execute(){
  burstTime--;
}

Process::~Process(){}
