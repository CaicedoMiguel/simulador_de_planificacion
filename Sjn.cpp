#include "Sjn.h"
#include "Process.h"
#include <algorithm>
#include <iostream>

void Sjn::executeSJN(vector<Process>& processes) {
  sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
  return a.getBurstTime() < b.getBurstTime();
  });

  int currentTime = 0;
  double totalWaitTime = 0;
  double totalTurnaroundTime = 0;

  cout << "Proceso\tAT\tBT\tWT\tTAT\tCT\n";

  for(auto& process : processes) {
    if(process.getArrivalTime() > currentTime) {
        currentTime = process.getArrivalTime();
    }

    cout << process.getId() << "\t" << process.getArrivalTime() << "\t" << process.getBurstTime() << "\t";

    double waitTime = currentTime - process.getArrivalTime();
    totalWaitTime += waitTime;

    double turnaroundTime = waitTime + process.getBurstTime();
    totalTurnaroundTime += turnaroundTime;

    cout << waitTime << "\t" << turnaroundTime << "\t";

    currentTime += process.getBurstTime();
    cout << currentTime << "\n";

    process.setCompletionTime(currentTime); // Actualizar el tiempo de completación del proceso
  }

  double averageWaitTime = totalWaitTime / processes.size();
  double averageTurnaroundTime = totalTurnaroundTime / processes.size();

  cout << "\nTiempo promedio de espera: " << averageWaitTime << "\n";
  cout << "Tiempo promedio de retorno: " << averageTurnaroundTime << "\n";
}
