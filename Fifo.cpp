#include "Fifo.h"
#include "Process.h"
#include <algorithm>
#include <iostream>

void Fifo::executeFIFO(vector<Process>& processes) {
  sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
        return a.getArrivalTime() < b.getArrivalTime();
  });

  int currentTime = 0;
  double totalWaitTime = 0;
  double totalTurnaroundTime = 0;

  cout << "Proceso\tAT\tBT\tWT\tTAT\tCT\n";

  for(auto& process : processes) {
    if (process.getArrivalTime() > currentTime) {
      currentTime = process.getArrivalTime();
    }

  cout << process.getId() << "\t" << process.getArrivalTime() << "\t" << process.getBurstTime() << "\t";

  double waitTime = currentTime - process.getArrivalTime();
  totalWaitTime += waitTime;

  double turnaroundTime = waitTime + process.getBurstTime();
  totalTurnaroundTime += turnaroundTime;

  cout << waitTime << "\t" << turnaroundTime << "\t";

  currentTime += process.getBurstTime();
  process.setCompletionTime(currentTime); // Actualizar el tiempo de completación del proceso
  cout << currentTime << "\n";
  }

  double averageWaitTime = totalWaitTime / processes.size();
  double averageTurnaroundTime = totalTurnaroundTime / processes.size();

  cout << "\nTiempo promedio de espera: " << averageWaitTime << "\n";
  cout << "Tiempo promedio de retorno: " << averageTurnaroundTime << "\n";
}
