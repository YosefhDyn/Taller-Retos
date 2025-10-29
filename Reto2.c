/* 

  Nombre: Yosefh Steven Pena Rodriguez
  Clase: Sistemas Operativos
  Fecha: 28/10/2025
  
  Descripcion del codigo:
  Este programa crea multiples hilos que incrementan un contador global. 
  Se utiliza un mutex para evitar condiciones de carrera al modificar 
  el contador. Todos los hilos son unidos con pthread_join antes de 
  mostrar el valor final del contador.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 10  // Numero de hilos que se crearan

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; // Inicializa el mutex
int counter = 0; // Variable global compartida entre los hilos

// Funcion que ejecutara cada hilo
void *thread_function(void *arg) {
    int i = *(int *)arg; // Convierte el argumento a entero para identificar el hilo

    pthread_mutex_lock(&mtx);  // Bloquea el mutex antes de acceder al recurso compartido
    counter++;                 // Incrementa el contador global
    printf("thread number %d  thread id %lu\n", i, (unsigned long)pthread_self()); // Imprime informacion del hilo
    pthread_mutex_unlock(&mtx); // Libera el mutex para que otro hilo pueda acceder

    pthread_exit(NULL); // Termina el hilo de forma segura
}

int main() {
    pthread_t thread_id[NTHREADS]; // Arreglo para almacenar los identificadores de los hilos
    int i;
    int idx[NTHREADS]; // Arreglo con los indices que se pasaran a cada hilo

    // Crea todos los hilos
    for (i = 0; i < NTHREADS; i++) {
        idx[i] = i + 1; // Asigna un numero identificador a cada hilo
        // Crea un hilo que ejecutara la funcion thread_function
        if (pthread_create(&thread_id[i], NULL, thread_function, &idx[i]) != 0) {
            perror("pthread_create"); // Muestra error si la creacion del hilo falla
            exit(1);
        }
    }

    // Espera a que todos los hilos terminen su ejecucion
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Imprime el valor final del contador despues de que todos los hilos han terminado
    printf("Final counter value %d\n", counter);

    return 0;
}
