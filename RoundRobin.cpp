#include "Process.h"
#include "RoundRobin.h"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

bool compareByArrivalTime(const Process &a, const Process &b) {
  return a.getArrivalTime() < b.getArrivalTime();
}

void roundRobin::executeRoundRobin(vector<Process>& processes, int quantum) {
  
  // Ordenar los procesos por tiempo de llegada
  sort(processes.begin(), processes.end(), compareByArrivalTime);
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
    
    // Calcular el tiempo de espera para este ciclo
    int waitTime = currentTime - currentProcess.getArrivalTime();
    if (waitTime > 0) {
      totalWaitTime += waitTime;
    }

    // Ejecutar el proceso por un quantum de tiempo
    int executionTime = min(currentProcess.getBurstTime(), quantum);
    for (int i = 0; i < executionTime; i++) {
      currentProcess.execute();
      currentTime++;
    }

    // Actualizar el tiempo de llegada para el próximo ciclo
    currentProcess.setArrivalTime(currentTime);

    // Si el proceso no se ha completado, lo vuelve a agregar a la cola de procesos listos
    if (currentProcess.getBurstTime() > 0) {
      readyQueue.push_back(currentProcess);
    } else {
      // Si el proceso se ha completado, calcula el tiempo de retorno
      int turnaroundTime = currentProcess.getArrivalTime() - executionTime ;
       totalTurnaroundTime += turnaroundTime;
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

  

