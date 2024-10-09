# Exámenes y Prácticas de Sistemas Operativos


## IMPORTANTES.
T3.
- Señales no han preguntado mucho, saber BLOQUEO y CAPTURA
- (Ordinaria 1) Enero 2023 (Sim. Comandos)
- (Ordinaria) Febrero 2021 (1 fd + terminal)

T4:
- (Ordinaria 1) Enero 2019 (UDP + "read" terminal) hora
- (Ordinaria) Febrero 2018 (TCP) (no especifica pre/accept-fork)

## Tema 3
Señales y tuberias. TODO...
3 tipos de ejercicios:
- Señales
- Combinar comandos con pipes. **Tuberia sin nombre** redirigir estandar entre procesos para ejecutar comandos combiandos >cmd1 | cmd2
- Multiplexacion con tuberias. **tuberia con nombre**, con select gestionar varias tuberias.

Señales:
- (Ordinario 3) Enero 2019 (Bloqueo - sigprocmask)

Tuberia sin nombre:
- (Ordinaria 1) Enero 2023 (Sim. Comandos)
- (Ordinaria) Enero 2022 (Sim. Comandos)
- (Ordinaria) Enero 2020 (Sim. Comandos con 2 procesos. padre espera y cierra todo) 
- (Ordinaria 2) Enero 2019 (Sim. Comandos con 2 procesos. padre espera y cierra todo)

Multififo:
- (Ordinaria 2) Enero 2023 (2 fd)
- (Ordinaria) Febrero 2021 (1 fd + terminal)
- (Ordinaria 1) Enero 2020 (2 fd)

### TODO

#### (Ordinaria 1) Enero 2019 
Escribe un programa que lance un demonio del sistema. Recibirá el programa a lanzar como primer argumento y el resto de argumentos se interpretarán como argumentos del programa: ```$ ./daemonize comando arg1 arg2 ...```
El proceso principal debe crear un proceso y terminar. El nuevo proceso debe crear una nueva sesión, fijar el directorio de trabajo a /tmp, mostrar los identificadores de proceso, de proceso padre, de grupo de procesos y de sesión, y ejecutar el programa con sus argumentos.

### Señales

#### (Ordinario 3) Enero 2019 
Escriba un programa que cuente las veces que ha recibido las señales SIGINT y SIGTSTP. El programa principal permanecerá en un bucle que se detendrá cuando se hayan recibido 10 señales en total. El número de señales de cada tipo se mostrará al finalizar el programa.

### Combinar comandos con pipes (sin nombre)

#### (Ordinaria) Enero 2020 (pipe) y
#### (Ordinaria 2) Enero 2019 (pipe) 
Escribe un programa que ejecute dos comandos de la siguiente forma: 
- Los comandos serán el primer y segundo argumento del programa. El resto de argumentos del programa se considerarán argumentos del segundo comando: ```$ ./conecta comando1 comando2 arg2_1 arg2_2 ...```
- Cada comando se ejecutará en un proceso distinto, que imprimirá su PID por el terminal.
- El programa conectará la salida estándar del primer proceso con la entrada estándar del segundo, y esperará la finalización de ambos para terminar su ejecución.

- Código: [2020_Opipe.c.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2020_Opipe.c.c)

#### (Ordinaria) Enero 2022 (pipe)
Escribe un programa que cree dos procesos y ejecute un comando en cada uno, de forma que la salida del primer comando sea la entrada del segundo. El proceso padre imprimirá el PID y el código de salida de cada proceso. El programa se ejecutará de la siguiente manera:

#### (Ordinaria 1) Enero 2023 (pipe)
Escribe un programa que ejecute dos comandos de la siguiente forma:
- Los comandos serán el primer y segundo argumento del programa.
- El primer comando se ejecutará en un nuevo proceso y el segundo comando se ejecutará en el proceso principal. Ambos procesos imprimirán su PID por el terminal.
- Se conectará la salida estándar del nuevo proceso con la entrada estándar del proceso principal mediante una tubería sin nombre.

- Código: [2023_O1pipe.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2023_O1pipe.c)


### Multiplexacion de tuberias

####  (Ordinaria 2) Enero 2023 (multi-fifo)
Escribe un programa que lea simultáneamente dos tuberías con nombre usando multiplexación de E/S síncrona. Las tuberías existirán previamente en el directorio actual de trabajo y se llamarán fifo1 y fifo2. El programa mostrará el nombre de la tubería de la que ha leído y los datos leídos. Además, el programa cerrará y volverá a abrir la tubería al detectar el fin de fichero.

- Código: [2023_O2fifo.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2023_O2fifo.c)

####  (Ordinaria 2) Enero 2023 (multi-fifo con terminal)
Escribe un programa que lea simultáneamente de una tubería con nombre, que existirá previamente en el directorio actual de trabajo y se llamará tuberia, y del terminal.
- Imprimirá en el terminal los datos leídos y terminará tras 5 segundos sin recibir datos 
- Al detectar el fin de fichero en la tubería, la cerrará y volverá a abrirla 

- Código: [2021_Ofifo.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2021_Ofifo.c)

#### (Ordinaria 1) Enero 2020 (multi-fifo)
Escribe un programa que lea simultáneamente de dos tuberías con nombre (tuberia1 y tuberia2). El programa mostrará el nombre de la tubería desde la que se leyó y los datos leídos. El programa detectará cuándo se cierra el extremo de escritura de una tubería (read() devuelve 0) para cerrarla y volver a abrirla.

- Código: [2020_O1fifo.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2020_O1fifo.c)

---

## Tema 4 (TCP/UDP)
2 tipos de ejercicios: 
- Servidor UDP/TCP **normal**
- Servidores **concurrentes** (pre-fork, accept-and-fork)

Concurrente:
- (Ordinaria 3) Enero 2019 (TCP) (no especifica pre/accept-fork)
- (Ordinaria) Febrero 2018 (TCP) (no especifica pre/accept-fork)

Normal:
- (Ordinaria 1) Enero 2023 (TCP) nice
- (Ordinaria 2) Enero 2023 (UDP) passwd
- (Ordinaria) Enero 2022 (TCP) direccion del cliente
- (Ordinaria) Febrero 2021 (UDP) stat
- (Ordinaria) Enero 2020 (TCP) mensaje del cliente
- (Ordinaria 1) Enero 2020 (UDP) hora 
- (Ordinario 2) Enero 2019 (TCP) direccion y puerto del cliente
- (Ordinaria 1) Enero 2019 (UDP + "read" terminal) hora

### Concurrentes

#### (Ordinaria 3) Enero 2019 
Escriba un programa servidor TCP que escuche en una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor devolverá lo que el cliente le envíe y será capaz de atender a varios clientes a la vez. En cada conexión, el servidor imprimirá la dirección y el puerto del cliente, así como el PID del proceso que la atiende. Finalmente, el servidor gestionará adecuadamente la finalización de los procesos hijo que cree.

### Normal (UDP/TCP)

#### (Ordinaria) Febrero 2021 (UDP) 
Escribe un programa servidor UDP que escuche en una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. Recibirá del cliente una ruta de fichero y le devolverá una cadena con el tipo del fichero (regular, directorio, enlace, fifo u otro). Además, al recibir cada mensaje imprimirá en el terminal la dirección y el puerto del cliente.
:-----

- Código: [2021_Oudp.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2021_Oudp.c)


#### (Ordinaria 1) Enero 2023 (TCP) 
Escribe un programa servidor TCP que escuche en una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor recibirá el PID de un proceso, imprimirá en el terminal el PID recibido y su valor de nice y enviará al cliente el valor del nice. En caso de que el proceso no exista en el servidor, devolverá un mensaje de error informando.
:-----

![so_2023_O](https://github.com/Danipiza/UCM/assets/98972125/67d38529-b735-4ec4-a5c5-f25ced3fff5e)
El Código1 es con la sintaxis del manual, y el Código2 es con la sintaxis de los apuntes. Solo la sintaxis de socket() y bind().
- Código1: [2023_Otcp.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2023_O2tcp.c)
- Código2: [2023_Otcp2.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2023_O2tcp2.c)
  
#### (Ordinaria) Enero 2022 (TCP) 
Escribe un programa servidor TCP que devuelva la dirección del cliente al recibir cualquier mensaje. El programa se ejecutará de la siguiente manera: $ ./tcp <dir IPv4 o IPv6 en cualquier formato> <puerto>
- Ejemplo: $ ./tcp :: 7777

Código: [2022_Otcp.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2022_Otcp.c)

#### (Ordinaria) Enero 2020 (TCP)
Escribe un programa servidor TCP que escuche en una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor devolverá lo que el cliente le envíe. En cada conexión, el servidor mostrará la dirección y el puerto del cliente.

- Código: [2020_Otcp.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2020_Otcp.c)
- Extra (versión UDP): [2020_Oudp.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/Extra/2020_Oudp.c)

#### (Ordinaria 1) Enero 2020 (UDP)
Escribe un programa servidor UDP que escuche peticiones realizadas a una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor devolverá la hora (en formato HH:MM:SS) al recibir cualquier mensaje. En cada mensaje, el servidor mostrará la dirección y el puerto del cliente.

- Código: [2020_O1udp.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/Examenes/2020_O1udp.c)


#### (Ordinario 2) Enero 2019 (TCP)
Escribe un programa servidor TCP que escuche peticiones realizadas a una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor devolverá la dirección del cliente al recibir cualquier mensaje. En cada conexión, el servidor mostrará en el terminal la dirección y el puerto del cliente.

#### (Ordinaria 1) Enero 2019 (UDP)
Escribe un programa servidor UDP que escuche peticiones realizadas a una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos y desde el terminal, multiplexando ambos canales. El servidor devolverá la hora al recibir cualquier mensaje. En cada mensaje, el servidor mostrará en el terminal la dirección y el puerto del cliente.

#### (Ordinaria) Febrero 2018 (TCP)
Escriba un programa servidor TCP que escuche en una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor devolverá lo que el cliente le envíe y será capaz de atender a varios clientes a la vez. En cada conexión, el servidor imprimirá la dirección y el puerto del cliente, así como el PID del proceso que la atiende. Finalmente, el servidor gestionará adecuadamente la finalización de los procesos hijo que cree. 