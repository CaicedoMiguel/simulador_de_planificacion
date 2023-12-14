#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include "Process.h"
#include "RoundRobin.h"

using namespace std;

void roundRobin::executeRoundRobin(vector<Process>& processes, int quantum) {

  // Ordenar los procesos por tiempo de llegada
  sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
    return a.getArrivalTime() < b.getArrivalTime();
  });
  deque<Process> readyQueue;
  // Añadir todos los procesos a la cola de listos
  for (auto& process : processes) {
    readyQueue.push_back(process);
  }

  // Variables de control
  int currentTime = 0;
  double totalWaitTime = 0;
  double totalTurnaroundTime = 0;

  // Bucle principal del algoritmo
  while (!readyQueue.empty()) {

    // Elegir el proceso de la cola de procesos listos con el tiempo de llegada más bajo
    Process currentProcess = readyQueue.front();
    readyQueue.pop_front();

    // Ejecutar el proceso por un quantum de tiempo
    int remainingTime = currentProcess.getBurstTime();
    for (int i = 0; i < quantum && remainingTime > 0; i++) {
      currentProcess.execute();
      remainingTime--;
      currentTime++;
    }

    // Si el proceso no se ha completado, lo vuelve a agregar a la cola de procesos listos
    if (remainingTime > 0) {
      readyQueue.push_back(currentProcess);
    } else {

      // Si el proceso se ha completado, calcula los tiempos de espera y retorno
      int waitTime = currentTime - currentProcess.getArrivalTime() - currentProcess.getBurstTime();
      if (waitTime > 0) {
        totalWaitTime += waitTime;
      }
      int turnaroundTime = currentTime - currentProcess.getArrivalTime();
      totalTurnaroundTime += turnaroundTime;

      // Verifica si hay más procesos para ejecutar
      if (readyQueue.empty()) {
        break;
      }
    }
  }

  // Calcular los tiempos promedio de espera y retorno
  if (!processes.empty()) {
    double averageWaitTime = totalWaitTime / processes.size();
    double averageTurnaroundTime = totalTurnaroundTime / processes.size();

    cout << "\nTiempo promedio de espera: " << averageWaitTime << "\n";
    cout << "Tiempo promedio de retorno: " << averageTurnaroundTime << "\n";
  } else {
    cout << "No hay procesos para calcular promedios." << endl;
  }
}
