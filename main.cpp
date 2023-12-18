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

  if (algorithm == "FIFO" or algorithm=="fifo") {
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
  } else if (algorithm == "SJN" or algorithm=="sjn") {
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
  }else if (algorithm == "RR" or algorithm=="rr") {
      int quantum;

      // Captura del quantum para Round Robin
      cout << "Ingrese el quantum para Round Robin: ";
      cin >> quantum;

      // Lógica para capturar los procesos
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

      roundRobin rrInstance;
      rrInstance.executeRoundRobin(processes, quantum);
  } else if (algorithm == "MLQ" or algorithm=="mlq") {
      int userPriority;
      cout << "Ingrese el número de procesos: ";
      cin >> numProcesses;

      queue<Process> lowPriorityQueue, mediumPriorityQueue, highPriorityQueue;

      for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime, burstTime;
        cout << "Ingrese el tiempo de llegada del proceso "<< i + 1 << ": ";
        cin >> arrivalTime;
        cout << "Ingrese el tiempo de ejecución del proceso" << i + 1 << ": ";
        cin >> burstTime;
        cout << "Ingrese la prioridad del proceso (1 - baja, 2 - media, 3 - alta): ";
        cin >> userPriority;

        Process newProcess(i + 1, arrivalTime, burstTime);

        switch(userPriority) {
          case 1:
            lowPriorityQueue.push(newProcess);
            break;
          case 2:
            mediumPriorityQueue.push(newProcess);
            break;
          case 3:
            highPriorityQueue.push(newProcess);
            break;
          default:
            cout << "Prioridad no reconocida. Se asignará baja prioridad por defecto.\n";
            lowPriorityQueue.push(newProcess);
        }
      }

      Mlq mlqInstance;
      cout << "Ejecutando MLQ:\n";
      mlqInstance.executeMLQ(lowPriorityQueue, mediumPriorityQueue, highPriorityQueue);
  } else if (algorithm == "MLFQ" or algorithm=="mlfq") {
      int numColas;
      cout << "Ingrese el número de colas de prioridad: ";
      cin >> numColas;

      // Crear un vector de colas de prioridad
      vector<queue<Process*>> colas(numColas);
      vector<Process*> procesos;

      cout << "Ingrese el número de procesos: ";
      cin >> numProcesses;

      for (int i = 0; i < numProcesses; ++i) {
          int arrivalTime, burstTime, priority;
          cout << "Ingrese el tiempo de llegada del proceso "<< i + 1 << ": ";
          cin >> arrivalTime;
          cout << "Ingrese el tiempo de ejecución del proceso" << i + 1 << ": ";
          cin >> burstTime;
          cout << "Ingrese la prioridad del proceso (0 - " << numColas - 1 << "): ";
          cin >> priority;

          Process* newProcess = new Process(i + 1, arrivalTime, burstTime, priority);
          procesos.push_back(newProcess);
      }

      // Pasar el vector al constructor de MLFQ
      MLFQ mlfqInstance(colas);

      // Agregar los procesos a la instancia de MLFQ
      for (int i = 0; i < numProcesses; ++i) {
          mlfqInstance.agregarProceso(procesos[i]);
      }

      // Ejecutar MLFQ
      cout << "Ejecutando MLFQ:\n";
      mlfqInstance.ejecutar(); 
  } else {
        cout << "Algoritmo no reconocido.\n";
    }
    
    return 0;
}