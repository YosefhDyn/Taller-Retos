/* 

  Nombre: Yosefh Steven Pena Rodriguez
  Clase: Sistemas Operativos
  Fecha: 28/10/2025
  
  Descripcion del codigo:
  Este programa muestra el uso correcto de variables de condicion y mutex.
  El hilo reportar siempre espera a que el hilo asignar actualice el valor.
  Con esta sincronizacion el resultado siempre sera consistente y predecible.

  Cambio realizado:
  En la version anterior existia una condicion de carrera donde el hilo reportar 
  podia leer el valor antes de que el hilo asignar lo actualizara. 
  Se corrigio agregando una espera controlada con pthread_cond_wait 
  y asegurando el orden de ejecucion con el uso apropiado del mutex.
  Adicionalmente se agrego una pequena pausa antes de crear el hilo asignar 
  para garantizar que el hilo reportar entre en espera antes de la notificacion.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;  // Variable de condicion
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex para acceso controlado
int valor = 100;                                    // Valor compartido
bool notificar = false;                             // Bandera de control

// Hilo que espera la notificacion para leer el valor actualizado
void *reportar(void *arg) {
    pthread_mutex_lock(&mutex); // Bloquea el acceso

    // Espera hasta que notificar sea verdadero
    while (!notificar) {
        pthread_cond_wait(&var_cond, &mutex); // Espera senal de asignar
    }

    // Cuando el otro hilo senala imprime el valor actualizado
    printf("El valor es %d\n", valor);

    pthread_mutex_unlock(&mutex); // Libera el acceso
    return NULL;
}

// Hilo que cambia el valor y notifica al otro hilo
void *asignar(void *arg) {
    pthread_mutex_lock(&mutex); // Bloquea antes de modificar

    valor = 20;                 // Actualiza el valor compartido
    notificar = true;           // Cambia la bandera
    pthread_cond_signal(&var_cond); // Envia senal al hilo reportar

    pthread_mutex_unlock(&mutex);   // Libera el acceso
    return NULL;
}

int main() {
    pthread_t reporte, asigne;

    // Crea primero el hilo que esperara la notificacion
    pthread_create(&reporte, NULL, reportar, NULL);

    // Pequeña pausa para asegurar que el hilo reportar este esperando
    // Este cambio ayuda a evitar condiciones de carrera durante la creacion de hilos
    struct timespec t = {0, 10000000}; // 10 milisegundos
    nanosleep(&t, NULL);

    // Crea el hilo que actualiza el valor y envia la senal
    pthread_create(&asigne, NULL, asignar, NULL);

    // Espera a que ambos hilos terminen
    pthread_join(reporte, NULL);
    pthread_join(asigne, NULL);

    return 0;
}


