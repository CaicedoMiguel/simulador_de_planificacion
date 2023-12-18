#include "Mlq.h"
#include "Process.h"
#include <iostream>

void Mlq::executeMLQ(queue<Process>& lowPriorityQueue,
                     queue<Process>& mediumPriorityQueue,
                     queue<Process>& highPriorityQueue)
{
  int currentTime = 0;
  double totalWaitingTime = 0;
  double totalTurnaroundTime = 0;
  int totalProcesses = highPriorityQueue.size() + mediumPriorityQueue.size() + lowPriorityQueue.size();

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

        // Calcula el tiempo de espera y el tiempo de retorno para el proceso actual
        int waitingTime = processToRun->getCompletionTime() - processToRun->getArrivalTime() - processToRun->getBurstTime();
        int turnaroundTime = processToRun->getCompletionTime() - processToRun->getArrivalTime();

        // Acumula los tiempos de espera y de retorno
        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;

        if (processToRun == &highPriorityQueue.front()) {
            highPriorityQueue.pop();
        } else if (processToRun == &mediumPriorityQueue.front()) {
              mediumPriorityQueue.pop();
          } else {
              lowPriorityQueue.pop();
          }
    }
  }


  double averageWaitingTime = totalWaitingTime / totalProcesses;
  double averageTurnaroundTime = totalTurnaroundTime / totalProcesses;

  cout << "Tiempo de espera promedio: " << averageWaitingTime << endl;
  cout << "Tiempo de retorno promedio: " << averageTurnaroundTime << endl;
}

