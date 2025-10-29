# Proyecto Sistemas Operativos - Retos con Hilos

Autor: **Yosefh Steven Pena Rodriguez**  
Clase: **Sistemas Operativos**  
Fecha: **28/10/2025**

## Descripcion general
Este proyecto contiene varios retos de programacion en lenguaje C que usan **hilos (threads)**, **mutex**, **variables de condicion** y **sincronizacion**.  
Cada archivo `RetoN.c` corresponde a un ejercicio independiente que demuestra un concepto especifico de programacion concurrente.

---

## Estructura del proyecto

```
Reto1.c   -> Creacion basica de hilos
Reto2.c   -> Sincronizacion con mutex y contador compartido
Reto3.c   -> Manejo de condiciones de carrera
Reto4.c   -> Variables de condicion y comunicacion entre hilos
Reto5.c   -> Sincronizacion avanzada con mutex y señales
Reto6.c   -> Coordinacion de ejecucion entre hilos
Reto7.c   -> Version corregida para resultado determinista
Makefile  -> Archivo para compilar y ejecutar todos los retos
```

---

## Compilacion y ejecucion

### Compilar todos los retos
```
make
```

### Compilar un reto especifico
Ejemplo para el reto 3:
```
make Reto3
```

### Ejecutar un reto especifico
Ejemplo para ejecutar el reto 3:
```
make run3
```

### Limpiar los archivos compilados
```
make clean
```

---

## Uso en Replit
1. Sube todos los archivos `Reto1.c` a `Reto7.c` y el archivo `Makefile` a tu proyecto de Replit.  
2. Abre la consola de Replit.  
3. Ejecuta el comando:
   ```
   make
   ```
4. Luego puedes correr cada reto con:
   ```
   make runN
   ```
   donde `N` es el numero del reto (por ejemplo `make run4`).

---

## Notas tecnicas
- Todos los retos se compilan con soporte **pthread**.  
- Las banderas de compilacion activan advertencias (`-Wall -Wextra`) y el estandar `C11`.  
- El proyecto demuestra conceptos como:
  - Creacion de hilos con `pthread_create`
  - Sincronizacion con `pthread_mutex_t`
  - Espera y senalizacion con `pthread_cond_t`
  - Manejo de variables globales seguras
  - Evitar condiciones de carrera

---

## Resultado esperado
Al ejecutar los retos se observaran diferentes comportamientos de sincronizacion.  
En el **Reto7**, el valor mostrado **siempre sera 20**, confirmando la correccion de la condicion de carrera del reto anterior.

---

## Comandos utiles
| Comando | Descripcion |
|----------|--------------|
| `make` | Compila todos los programas |
| `make RetoN` | Compila un reto especifico |
| `make runN` | Ejecuta el reto N |
| `make clean` | Elimina los ejecutables |

---

### Fin del documento
