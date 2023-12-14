#include "Mlfq.h"
#include <algorithm>

MLFQ::MLFQ(vector<queue<Process*>>& colas) : colas(colas) {}

void MLFQ::agregarProceso(Process* p) {
  int priority = p->getPriority(); 
  if (priority > MAX_PRIORITY) {
    priority = MAX_PRIORITY; 
  }

  colas[priority].push(p); // Agregar proceso a la cola correspondiente según su prioridad
}

void MLFQ::ejecutar() {
  vector<int> tiempoEspera(colas.size(), 0);
  vector<int> tiempoFinalizacion(colas.size(), 0);
  vector<int> procesosTerminados(colas.size(), 0);
  int tiempoActual = 0;

  while (true) {
    bool todasLasColasVacias = true;

    // Iterar sobre todas las colas de prioridad
    for (int i = 0; i < colas.size(); ++i) {
      if (!colas[i].empty()) {
        todasLasColasVacias = false;
        Process* procesoEjecutandose = colas[i].front();

        int tiempoRanura = procesoEjecutandose->getBurstTime();
        tiempoActual += tiempoRanura;

        procesoEjecutandose->setBurstTime(procesoEjecutandose->getBurstTime() - tiempoRanura);

        if (procesoEjecutandose->getBurstTime() == 0) {
          procesoEjecutandose->setCompletionTime(tiempoActual);
          procesosTerminados[i]++;
          tiempoFinalizacion[i] += tiempoActual - procesoEjecutandose->getArrivalTime() - tiempoEspera[i];
              colas[i].pop();
          } else {
              colas[i].pop();
              colas[i].push(procesoEjecutandose);
            }

            // Ajustar tiempos de espera para las colas
            for(int j = 0; j < colas.size(); ++j) {
                if (i != j && !colas[j].empty()) {
                  tiempoEspera[j] += tiempoRanura;
                }
            }
             break;
      }
    }

        if (todasLasColasVacias) {
          break;
        }
  }

    // Calcular tiempos promedio y mostrar resultados
  for (int i = 0; i < colas.size(); ++i) {
    double tiempoEsperaPromedio = tiempoEspera[i] / static_cast<double>(procesosTerminados[i]);
    double tiempoFinalizacionPromedio = tiempoFinalizacion[i] / static_cast<double>(procesosTerminados[i]);
    cout << "Cola " << i << ": Tiempo de espera promedio: " << tiempoEsperaPromedio << ", Tiempo de finalización promedio: " << tiempoFinalizacionPromedio << endl;
  }
}

MLFQ::~MLFQ(){}
