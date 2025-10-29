/* 

  Nombre: Yosefh Steven Pena Rodriguez
  Clase: Sistemas Operativos
  Fecha: 28/10/2025
  
  Descripcion del codigo:
  Programa que crea tres hilos y muestra inicio y fin de cada trabajo
  Se usa un mutex para asignar un id seguro a cada hilo y evitar condiciones de carrera
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NJOBS 3

pthread_t tid[NJOBS];                 // Arreglo con los identificadores de hilos
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex para seccion critica
int counter = 0;                      // Contador global para asignar id de trabajo

// Funcion que ejecuta cada hilo
void *compute(void *arg) {
    unsigned long i = 0;              // Variable para bucle de trabajo simulado
    int my_id;                        // Id unico del trabajo

    pthread_mutex_lock(&lock);        // Entra a la seccion critica
    counter += 1;                     // Incrementa el contador global
    my_id = counter;                  // Copia el valor para uso local
    pthread_mutex_unlock(&lock);      // Sale de la seccion critica

    printf("\nJob %d has started\n", my_id);   // Reporta el inicio del trabajo

    for (i = 0; i < 0x0FFFFFFFul; i++) {       // Trabajo simulado
        // no op
    }

    printf("\nJob %d has finished\n", my_id);  // Reporta el fin del trabajo
    return NULL;                       // No retorna valor
}

int main(void) {
    int i = 0;                         // Indice del bucle
    int error;                         // Codigo de error de pthread_create

    // Crea NJOBS hilos que ejecutan compute
    while (i < NJOBS) {
        error = pthread_create(&tid[i], NULL, compute, NULL); // Crea el hilo i
        if (error != 0) {
            printf("\nThread cant be created [%d]\n", error); // Mensaje si falla
            exit(1);                    // Termina el programa en caso de error
        }
        i++;                            // Pasa al siguiente hilo
    }

    // Espera a que todos los hilos terminen
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    return 0;                           // Fin del programa principal
}

