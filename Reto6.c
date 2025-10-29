/* 

  Nombre: Yosefh Steven Pena Rodriguez
  Clase: Sistemas Operativos
  Fecha: 28/10/2025
  
  Descripcion del codigo:
  Dos hilos incrementan un contador global
  Uno de los hilos espera con variable de condicion cuando el contador esta en un rango
  El otro hilo envia senales cuando el contador sale de ese rango
  Se usan dos mutex para separar espera y actualizacion del contador
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;      // Protege la variable count
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;  // Protege la espera de la condicion
pthread_cond_t  condition_cond = PTHREAD_COND_INITIALIZER;    // Variable de condicion

int count = 0;          // Contador global compartido

#define COUNT_DONE  15  // Valor final para detener hilos
#define COUNT_HALT1 4   // Inicio del rango de pausa
#define COUNT_HALT2 11  // Fin del rango de pausa

// Hilo 1 espera mientras count este dentro del rango de pausa
void *count01(void *arg) {
    for (;;) {

        // Espera mientras el contador este entre COUNT_HALT1 y COUNT_HALT2
        pthread_mutex_lock(&condition_mutex);
        while (count >= COUNT_HALT1 && count <= COUNT_HALT2) {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);

        // Seccion critica para incrementar el contador
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount 01 %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        // Condicion de salida
        if (count >= COUNT_DONE) return NULL;
    }
}

// Hilo 2 senala cuando el contador esta fuera del rango de pausa
void *count02(void *arg) {
    for (;;) {

        // Si el contador esta fuera del rango se envia una senal
        pthread_mutex_lock(&condition_mutex);
        if (count < COUNT_HALT1 || count > COUNT_HALT2) {
            pthread_cond_signal(&condition_cond);
        }
        pthread_mutex_unlock(&condition_mutex);

        // Seccion critica para incrementar el contador
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount 02 %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        // Condicion de salida
        if (count >= COUNT_DONE) return NULL;
    }
}

int main(void) {
    pthread_t thread1, thread2;

    // Crea los dos hilos
    pthread_create(&thread1, NULL, count01, NULL);
    pthread_create(&thread2, NULL, count02, NULL);

    // Espera a que ambos hilos terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

