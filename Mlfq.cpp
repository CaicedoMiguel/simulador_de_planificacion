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

    // Asumiendo que tienes una estructura de datos para almacenar los procesos y sus tiempos de llegada
    vector<pair<int, Process*>> procesos;

    // Ordena la lista de procesos por tiempo de llegada
    sort(procesos.begin(), procesos.end());

    // Añade los procesos a las colas en el orden correcto de llegada
    for (int i = 0; i < procesos.size(); ++i) {
        int prioridad = procesos[i].second->getPriority();
        colas[prioridad].push(procesos[i].second);
    }

    // Calcular totalBurstTime al inicio
    int totalBurstTime = 0;
    for (int i = 0; i < colas.size(); ++i) {
        queue<Process*> colaCopia = colas[i];
        while (!colaCopia.empty()) {
            Process* proceso = colaCopia.front();
            totalBurstTime += proceso->getBurstTime();
            colaCopia.pop();
        }
    }

    // Bucle principal
    while (totalBurstTime > 0) {
        bool procesoEjecutado = false; // Bandera para verificar si se ejecutó un proceso en esta iteración

        // Iterar sobre todas las colas de prioridad en orden descendente
        for (int i = colas.size() - 1; i >= 0; --i) {
            if (!colas[i].empty()) {
                Process* procesoEjecutandose = colas[i].front();
                colas[i].pop();

                int quantum = max(1, procesoEjecutandose->getPriority()); // Asegurar que el quantum sea al menos 1
                int tiempoRanura = min(quantum, procesoEjecutandose->getBurstTime());
                tiempoActual += tiempoRanura;

                procesoEjecutandose->setBurstTime(procesoEjecutandose->getBurstTime() - tiempoRanura);

                if (procesoEjecutandose->getBurstTime() == 0) {
                    procesoEjecutandose->setCompletionTime(tiempoActual);
                    procesosTerminados[i]++;
                    tiempoFinalizacion[i] += tiempoActual - procesoEjecutandose->getArrivalTime() - tiempoEspera[i];
                } else {
                    colas[i].push(procesoEjecutandose);
                }

                for (int j = 0; j < colas.size(); ++j) {
                    if (i != j && !colas[j].empty()) {
                        tiempoEspera[j] += tiempoRanura;
                    }
                }

                totalBurstTime -= tiempoRanura; // Actualizar totalBurstTime
                procesoEjecutado = true; // Se ejecutó un proceso en esta iteración
                break;
            }
        }

        if (!procesoEjecutado) {
            tiempoActual++; // Incrementar tiempo si no se ejecutó ningún proceso
        }
    }

    // Mostrar resultados
    for (int i = 0; i < colas.size(); ++i) {
        if (procesosTerminados[i] > 0) {
            double tiempoEsperaPromedio = tiempoEspera[i] / static_cast<double>(procesosTerminados[i]);
            double tiempoFinalizacionPromedio = tiempoFinalizacion[i] / static_cast<double>(procesosTerminados[i]);
            cout << "Cola " << i << ": Tiempo de espera promedio: " << tiempoEsperaPromedio << ", Tiempo de finalización promedio: " << tiempoFinalizacionPromedio << endl;
        } else {
            cout << "Cola " << i << ": No se terminó ningún proceso en esta cola." << endl;
        }
    }
}


MLFQ::~MLFQ(){}
