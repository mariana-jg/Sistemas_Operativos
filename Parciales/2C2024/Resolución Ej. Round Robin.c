#include <stdio.h>  // Para printf
#include <stdlib.h> // Para rand(), srand()
#include <time.h>   // Para time()

#define RUNNING 1
#define RUNNABLE 2
#define BLOCKED 3

struct p {
    int status; // RUNNING, RUNNABLE, BLOCKED
    int proc;   // Identificador del proceso
};

struct p procesos[64]; // Tabla de procesos, máximo de 64 procesos

// Variable global para mantener el índice del último proceso seleccionado
int ultimo_proceso = -1;

struct p* elegir() {
    int i;
    int total_procesos = 64;

    // Comenzar a buscar desde el siguiente proceso después del último seleccionado
    for (i = 1; i <= total_procesos; i++) {
        int indice = (ultimo_proceso + i) % total_procesos; // Circular
        if (procesos[indice].status == RUNNABLE) {
            ultimo_proceso = indice; // Actualizamos el último proceso elegido
            return &procesos[indice];
        }
    }

    // Si no hay ningún proceso RUNNABLE, retornar NULL
    return NULL;
}

void idle() {
    // Función para manejar el estado inactivo del scheduler
    printf("No hay procesos RUNNABLE. Scheduler en estado inactivo.\n");
}

void scheduler() {
    for (;;) {
        struct p *candidato = elegir();
        if (candidato == NULL) {
            idle();
        } else {
            candidato->status = RUNNING;
            printf("Ejecutando proceso: %d\n", candidato->proc);
            // Aquí podrías simular ejecución y cambiar el estado de RUNNING a RUNNABLE
            candidato->status = RUNNABLE; // Volver a ponerlo como RUNNABLE después de simular
        }
    }
}

int main() {
    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Inicializar procesos con estados aleatorios
    for (int i = 0; i < 64; i++) {
        procesos[i].proc = i;
        // Asignar un estado aleatorio entre RUNNABLE y BLOCKED
        int random_status = rand() % 2 + 2; // 2 = RUNNABLE, 3 = BLOCKED
        procesos[i].status = random_status;
    }

    // Mostrar el estado inicial de los procesos
    printf("Estado inicial de los procesos:\n");
    for (int i = 0; i < 64; i++) {
        printf("Proceso %d: %s\n", procesos[i].proc,
               (procesos[i].status == RUNNABLE) ? "RUNNABLE" : "BLOCKED");
    }

    // Ejecutar el scheduler
    printf("\nEjecutando scheduler:\n");
    scheduler();

    return 0;
}