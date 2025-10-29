/* 

  Nombre: Yosefh Steven Pena Rodriguez
  Clase: Sistemas Operativos
  Fecha: 28/10/2025
  
  Descripcion del codigo:
  Este programa muestra el uso de variables de condicion y mutex en hilos.
  Un hilo espera hasta que otro hilo cambie una variable y emita una senal.
  Se usa pthread_cond_wait y pthread_cond_signal para la sincronizacion.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;  // Variable de condicion
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex para controlar el acceso
int valor = 100;                                    // Valor inicial compartido
bool notificar = false;                             // Bandera para indicar si se debe continuar

// Hilo que espera hasta recibir una notificacion
void *reportar(void *arg) {
    pthread_mutex_lock(&mutex); // Bloquea el mutex antes de acceder a la variable

    // Espera mientras notificar sea falso
    while (!notificar) {
        pthread_cond_wait(&var_cond, &mutex); // Espera la senal de otro hilo
    }

    // Cuando el otro hilo senala, imprime el valor actualizado
    printf("El valor es %d\n", valor);

    pthread_mutex_unlock(&mutex); // Libera el mutex
    return NULL;
}

// Hilo que cambia el valor y envia la notificacion
void *asignar(void *arg) {
    pthread_mutex_lock(&mutex); // Bloquea el mutex para modificar la variable
    valor = 20;                 // Asigna nuevo valor
    notificar = true;           // Cambia la bandera para indicar que ya se puede continuar
    pthread_cond_signal(&var_cond); // Envia la senal al hilo que espera
    pthread_mutex_unlock(&mutex);   // Libera el mutex
    return NULL;
}

int main() {
    pthread_t reporte, asigne; // Identificadores de los hilos

    // Crea los dos hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    // Espera a que ambos hilos terminen
    pthread_join(reporte, NULL);
    pthread_join(asigne, NULL);

    return 0;
}
