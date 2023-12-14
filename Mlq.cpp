#include "Mlq.h"
#include "Process.h"
#include <iostream>

void Mlq::executeMLQ(queue<Process>& lowPriorityQueue,
                     queue<Process>& mediumPriorityQueue,
                     queue<Process>& highPriorityQueue)
{
  int currentTime = 0;

  while (!highPriorityQueue.empty() || !mediumPriorityQueue.empty() || !lowPriorityQueue.empty()) {
    Process* processToRun = nullptr;

    // Logica de planificación MLQ aquí
    if (!highPriorityQueue.empty()) {
        processToRun = &highPriorityQueue.front();
    } else if (!mediumPriorityQueue.empty() && mediumPriorityQueue.front().getArrivalTime() <= currentTime) {
        processToRun = &mediumPriorityQueue.front();
      } else if (!lowPriorityQueue.empty() && lowPriorityQueue.front().getArrivalTime() <= currentTime) {
          processToRun = &lowPriorityQueue.front();
        }

        if (!processToRun) {
          currentTime++;
          continue;
        }

    processToRun->setBurstTime(processToRun->getBurstTime() - 1);
    currentTime++;

    if (processToRun->getBurstTime() == 0) {
        processToRun->setCompletionTime(currentTime);
        cout << "Proceso " << processToRun->getId() << " completado en tiempo: " << processToRun->getCompletionTime() << std::endl;

        if (processToRun == &highPriorityQueue.front()) {
            highPriorityQueue.pop();
        } else if (processToRun == &mediumPriorityQueue.front()) {
              mediumPriorityQueue.pop();
          } else {
              lowPriorityQueue.pop();
          }
    }
  }
}
