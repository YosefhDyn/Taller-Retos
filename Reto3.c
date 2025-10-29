/* 

  Nombre: Yosefh Steven Pena Rodriguez
  Clase: Sistemas Operativos
  Fecha: 28/10/2025
  
  Descripcion del codigo:
  Este programa calcula la suma de los cuadrados de varios numeros usando hilos.
  Se usa un mutex para evitar condiciones de carrera cuando los hilos acceden 
  a la variable global compartida. Cada hilo calcula el cuadrado de su numero 
  y lo acumula en una variable comun de manera segura.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define NHILOS 20 // Numero total de hilos a crear

pthread_mutex_t acumuladoMutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para proteger el acceso a la variable compartida
int acumulado = 0; // Variable global compartida donde se acumularan los resultados

// Funcion que ejecutara cada hilo
void *cuadrado(void *x) {
    int i = (intptr_t)x; // Convierte el argumento a entero
    int xi = i * i;      // Calcula el cuadrado del numero

    pthread_mutex_lock(&acumuladoMutex);  // Bloquea el mutex para acceso exclusivo
    acumulado += xi;                      // Suma el cuadrado al acumulador global
    pthread_mutex_unlock(&acumuladoMutex); // Libera el mutex

    return NULL; // No retorna ningun valor
}

int main() {
    pthread_t hilos[NHILOS]; // Arreglo para almacenar los identificadores de los hilos
    int i;

    // Crea NHILOS hilos que ejecutan la funcion cuadrado
    for (i = 0; i < NHILOS; i++) {
        if (pthread_create(&hilos[i], NULL, cuadrado, (void *)(intptr_t)(i + 1)) != 0) {
            perror("pthread_create"); // Muestra mensaje de error si falla la creacion del hilo
            exit(1);
        }
    }

    // Espera a que todos los hilos terminen su ejecucion
    for (i = 0; i < NHILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Imprime el resultado final acumulado
    printf("Suma de cuadrados %d\n", acumulado);

    return 0;
}
