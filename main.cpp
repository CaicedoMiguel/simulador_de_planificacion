#include <iostream>
#include <vector>
#include <queue>
#include "Process.h"
#include "Fifo.h"
#include "Sjn.h"
#include "RoundRobin.h"
#include "Mlfq.h"
#include "Mlq.h"

using namespace std;

int main() {
    int numProcesses=0;
    string algorithm;
    vector<Process> processes;
    processes.reserve(numProcesses);

    cout << "Ingrese el algoritmo a utilizar (FIFO / SJN / RR / MLFQ / MLQ): ";
    cin >> algorithm;

  if (algorithm == "FIFO") {
      cout << "Ingrese el número de procesos: ";
      cin >> numProcesses;

      vector<Process> processes;
      processes.reserve(numProcesses);

      for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime, burstTime;
          cout << "Ingrese el tiempo de llegada del proceso "<< i + 1 << ": ";
          cin >> arrivalTime;
        cout << "Ingrese el tiempo de ejecución del proceso" << i + 1 << ": ";
        cin >> burstTime;

          processes.emplace_back(i + 1, arrivalTime, burstTime);
      }
      Fifo fifoInstance;
      cout << "Ejecutando FIFO:\n";
      fifoInstance.executeFIFO(processes);
  } else if (algorithm == "SJN") {
      cout << "Ingrese el número de procesos: ";
      cin >> numProcesses;

      vector<Process> processes;
      processes.reserve(numProcesses);

      for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime, burstTime;
          cout << "Ingrese el tiempo de llegada del proceso "<< i + 1 << ": ";
          cin >> arrivalTime;
        cout << "Ingrese el tiempo de ejecución del proceso" << i + 1 << ": ";
        cin >> burstTime;

          processes.emplace_back(i + 1, arrivalTime, burstTime);
      }
      Sjn sjnInstance;
      cout << "Ejecutando FIFO:\n";
      sjnInstance.executeSJN(processes);
  }else if (algorithm == "RR") {
      int quantum;

      // Captura del quantum para Round Robin
      cout << "Ingrese el quantum para Round Robin: ";
      cin >> quantum;

      // Lógica para capturar los procesos
      int numProcesses;
      cout << "Ingrese el número de procesos: ";
      cin >> numProcesses;
      for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime, burstTime;
        cout << "Ingrese el tiempo de llegada del proceso "<< 
        i + 1 << ": ";
        cin >> arrivalTime;
        cout << "Ingrese el tiempo de ejecución del proceso"<< 
        i + 1 << ": ";
        cin >> burstTime;

        processes.emplace_back(i + 1, arrivalTime, burstTime);
      }
      vector<Process> processes;
      processes.reserve(numProcesses);
    
      roundRobin rrInstance;
      rrInstance.executeRoundRobin(processes, quantum);
    } else if (algorithm == "MLFQ") {
        // Lógica para el algoritmo MLFQ
        // ...
    } else if (algorithm == "MLQ") {
    int numQueues;
    cout << "Ingrese el número de colas para MLFQ: ";
    cin >> numQueues;

    cout << "Ingrese la máxima prioridad para MLFQ: ";
    int maxPriority;
    cin >> maxPriority;

    // Inicializar colas de prioridades
    queue<Process*> lowPriorityQueue;
    queue<Process*> mediumPriorityQueue;
    queue<Process*> highPriorityQueue;

    // Ingresar procesos y asignar prioridades
    for (int i = 0; i < numProcesses; ++i) {
      int arrivalTime, burstTime, priority;
      cout << "Ingrese el tiempo de llegada del proceso " << i + 1 << ": ";
      cin >> arrivalTime;
      cout << "Ingrese el tiempo de ejecución del proceso " << i + 1 << ": ";
      cin >> burstTime;
      cout << "Ingrese la prioridad del proceso " << i + 1 << ": ";
      cin >> priority;

      // Asignar proceso a la cola correspondiente
      processes.emplace_back(i + 1, arrivalTime, burstTime, priority);
      if (priority == maxPriority) {
        highPriorityQueue.push(&processes[i]);
      } else if (priority < maxPriority) {
        mediumPriorityQueue.push(&processes[i]);
      } else {
        lowPriorityQueue.push(&processes[i]);
      }
    }

    // Crear instancia de Mlfq y ejecutar
    Mlq mlfqInstance(numQueues);
    cout << "Ejecutando MLFQ:\n";
    mlfqInstance.executeMLQ(lowPriorityQueue, mediumPriorityQueue, highPriorityQueue);
    } else {
        cout << "Algoritmo no reconocido.\n";
    }
    
    return 0;
}