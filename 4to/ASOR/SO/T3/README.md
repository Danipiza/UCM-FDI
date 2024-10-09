# UCM

### Políticas de planificación

#### Ejercicio 01.
La política de planificación y la prioridad de un proceso puede consultarse y modificarse con chrt(1). Adicionalmente, nice(1) y renice(1) permiten ajustar el valor de nice de un proceso. Consultar la página de manual de ambos comandos y comprobar su funcionamiento cambiando el valor de nice de la shell a -10 y después cambiando su política de planificación a SCHED_FIFO con prioridad 12.
:-----

```
ps -ln                 // para ver los procesos ejecutados
renice -10 <pid>       // cambiar el valor nice
chrt -f -p 12 <pid>    // -f especifica SCHED_FIFO, -p la prioidad 
chrt -p 130            // comprobar la politica y prioridad
```

#### Ejercicio 02. 
Escribir un programa que muestre la política de planificación (como cadena) y la prioridad del proceso actual, además de mostrar los valores máximo y mínimo de la prioridad para la política de planificación.
:-----

Siempre dara la política por defecto.
- **Implementación normal** [ej2.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej2.c). Modificación con 2 terminales: en una se ejecuta el código principal, imprime su pid y duerme por 10 segundos, en otra terminal se cambia su política con ```chrt -f -p 10 pid```
- **Implementación modificada** [ej2_aux.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej2_aux.c). Se crea un proceso hijo con _fork()_ y este modifica la política, el proceso padre espera a que el hijo termine para avanzar e imprimir la nueva política.


### Procesos, grupos de procesos y sesiones


#### Ejercicio 04.
 ps(1) permite ver los procesos del sistema y su estado. Estudiar la página de manual y:
:-----

- Mostrar todos los procesos del usuario actual en formato extendido.
```ps ux```
- Mostrar los procesos del sistema, incluyendo el identificador del proceso, el identificador del grupo de procesos, el identificador de sesión, el estado y el comando con todos sus argumentos.
```ps -eo pid,pgid,sid,state,cmd```


#### Ejercicio 05.
Escribir un programa que muestre los identificadores del proceso (PID, PPID, PGID y SID), el número máximo de ficheros que puede abrir y su directorio de trabajo actual.
:-----

Código: [ej5.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej5.c)

#### Ejercicio 06.
Un demonio es un proceso que se ejecuta en segundo plano para proporcionar un servicio. Normalmente, un demonio está en su propia sesión y grupo. Para garantizar que es posible crear la sesión y el grupo, el demonio crea un nuevo proceso para crear la nueva sesión y ejecutar la lógica del servicio. Escribir una plantilla de demonio (creación del nuevo proceso y de la sesión) en el que únicamente se muestren los atributos del proceso (como en el ejercicio anterior). Además, establecer el directorio de trabajo del demonio a /tmp. ¿Qué sucede si el proceso padre termina antes que el hijo (observar el PPID del proceso hijo)? ¿Y si el proceso que termina antes es el hijo (observar el estado del proceso hijo con ps(1))? Nota: Usar sleep(3) o pause(3) para forzar el orden de finalización deseado
:-----

Código: [ej6.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej6.c)

Cuando un proceso padre termina antes que su hijo sin esperar con wait(), el proceso hijo se convierte en un proceso huérfano y es adoptado por init (PID 1). El proceso huérfano continúa ejecutándose normalmente y su estado de salida es eventualmente gestionado por init, evitando que se convierta en un proceso zombi.

### Ejecución de programas

#### Ejercicio 07.
Escribir dos versiones, una con system(3) y otra con execvp(3), de un programa que ejecute otro programa que se pasará como argumento por línea de comandos. En cada caso, se debe imprimir la cadena "El comando terminó de ejecutarse" después de la ejecución. ¿En qué casos se imprime la cadena? ¿Por qué? Nota: Considerar cómo deben pasarse los argumentos en cada caso para que sea sencilla la implementación. 
:-----
- Código system: [ej7_sys.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej7_sys.c)
- Código execvp: [ej7_exc.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej7_exc.c)

#### Ejercicio 08.
Usando la versión con execvp(3) del ejercicio anterior y la plantilla de demonio del ejercicio 6, escribir un programa que ejecute cualquier programa como si fuera un demonio. Además, redirigir los flujos estándar asociados al terminal usando dup2(2): Comprobar que el proceso sigue en ejecución tras cerrar la shell.
:-----
- La salida estándar al fichero /tmp/daemon.out.
- La salida de error estándar al fichero /tmp/daemon.err.
- La entrada estándar a /dev/null.
Código: [ej8.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej8.c)

### Señales
#### Ejercicio 09.
kill(1) permite enviar señales a un proceso o grupo de procesos por su identificador (pkill(1) permite hacerlo por nombre de proceso). Estudiar la página de manual y las señales que se pueden enviar a un proceso.
:-----

```man kill```

#### Ejercicio 10.
En un terminal, arrancar un proceso de larga duración (ej. sleep 600). En otra terminal, enviar diferentes señales al proceso, comprobar el comportamiento. Observar el código de salida del proceso. ¿Qué relación hay con la señal enviada?
:-----

```kill -9/SIGINT/SIGSTOP/... <pid>```
#### Ejercicio 11.
Escribir un programa que bloquee las señales SIGINT y SIGTSTP. Después de bloquearlas el programa debe suspender su ejecución con sleep(3) un número de segundos que se obtendrán de la variable de entorno SLEEP_SECS. Al despertar, el proceso debe informar de si recibió la señal SIGINT y/o SIGTSTP. En este último caso, debe desbloquearla con lo que el proceso se detendrá y podrá ser reanudado en la shell (imprimir una cadena antes de finalizar el programa para comprobar este comportamiento).
:-----

Código: [ej11.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej11.c)

#### Ejercicio 12.
Escribir un programa que instale un manejador para las señales SIGINT y SIGTSTP. El manejador debe contar las veces que ha recibido cada señal. El programa principal permanecerá en un bucle que se detendrá cuando se hayan recibido 10 señales. El número de señales de cada tipo se mostrará al finalizar el programa.
:-----

- Código: [ej12.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej12.c)
- Código con mejora: [ej12_aux.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej12_aux.c). Se añade sigsuspend en el bucle usando sigset_t



#### Ejercicio 13.
Escribir un programa que realice el borrado programado del propio ejecutable. El programa tendrá como argumento el número de segundos que esperará antes de borrar el fichero. Para notificar el final de la espera el programa instalará una alarma con alarm(2). El borrado del fichero se podrá detener si se recibe la señal SIGUSR1 antes de que termine el periodo de espera. Nota: Usar sigsuspend(2) para suspender el proceso y la llamada al sistema apropiada para borrar el fichero
:-----

Código: [ej13.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej13.c)

### Tuberías sin nombre

#### Ejercicio 14.

Escribir un programa que emule el comportamiento de la shell en la ejecución de una sentencia en la forma: comando1 argumento1 \| comando2 argumento2. El programa creará una tubería sin nombre y creará un hijo
:-----

- El proceso padre redireccionará la salida estándar al extremo de escritura de la tubería y ejecutará comando1 argumento1.
- El proceso hijo redireccionará la entrada estándar al extremo de lectura de la tubería y ejecutará comando2 argumento2.

Código: [ej14.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej14.c)

#### Ejercicio 15.
Para la comunicación bi-direccional, es necesario crear dos tuberías, una para cada sentido: p_h y h_p. Escribir un programa que implemente el mecanismo de sincronización de parada y espera:
:-----
- El padre leerá de la entrada estándar (terminal) y enviará el mensaje al proceso hijo, escribiéndolo en la tubería p_h. Entonces permanecerá bloqueado esperando la confirmación por parte del hijo en la otra tubería, h_p.
- El hijo leerá de la tubería p_h, escribirá el mensaje por la salida estándar y esperará 1 segundo. Entonces, enviará el carácter ‘l’ al proceso padre, escribiéndolo en la tubería h_p, para indicar que está listo. Después de 10 mensajes enviará el carácter ‘q’ para indicar al padre que finalice.

Código: [ej15.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej15.c)

### Tuberías con nombre

#### Ejercicio 16.
Usar mkfifo(1) para crear una tubería con nombre. Usar las herramientas del sistema de ficheros (stat(1), ls(1)…) para determinar sus propiedades. Comprobar su funcionamiento usando utilidades para escribir y leer de ficheros (ej. echo(1), cat(1), tee(1)...).
```
mkfifo tub1 // crea la tuberia
stat tub1 // propiedades como tipo de fichero: fifo
echo 1234 > tub1 // escribir en la tuberia
cat tub1 // leer en la tuberia
```


#### Ejercicio 17.
Escribir un programa que abra la tubería con el nombre anterior en modo sólo escritura, y escriba en ella el primer argumento del programa. En otro terminal, leer de la tubería usando un comando adecuado
:-----

Código: [ej17.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej17.c)

#### Ejercicio 18.
Crear otra tubería con nombre. Escribir un programa que espere hasta que haya datos listos para leer en alguna de ellas. El programa debe mostrar la tubería desde la que leyó y los datos leídos. Consideraciones:
:-----
- Para optimizar las operaciones de lectura usar un buffer (ej. de 256 bytes).
- Usar read(2) para leer de la tubería y gestionar adecuadamente la longitud de los datos leídos.
- Normalmente, la apertura de la tubería para lectura se bloqueará hasta que se abra para escritura (ej. con echo 1 > tuberia). Para evitarlo, usar la opción O_NONBLOCK en open(2).
- Cuando el escritor termina y cierra la tubería, read(2) devolverá 0, indicando el fin de fichero, por lo que hay que cerrar la tubería y volver a abrirla. Si no, select(2) considerará el descriptor siempre listo para lectura y no se bloqueará.

Código: [ej18.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T3/ej18.c)