# Exámenes y Prácticas de Sistemas Operativos

## Tema 3
Señales y tuberias. TODO...

---

## Tema 4 (TCP/UDP)
2 tipos de ejercicios: 
- Servidor UDP/TCP normal
- Servidores concurrentes (pre-fork, accept-and-fork)

### (Ordinaria) Febrero 2021 (UDP) 
Escribe un programa servidor UDP que escuche en una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. Recibirá del cliente una ruta de fichero y le devolverá una cadena con el tipo del fichero (regular, directorio, enlace, fifo u otro). Además, al recibir cada mensaje imprimirá en el terminal la dirección y el puerto del cliente.
:-----

Código: [2021_Oudp.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/Examenes/2021_Oudp.c)


### (Ordinaria) Enero 2023 (TDP) 
Escribe un programa servidor TCP que escuche en una dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor recibirá el PID de un proceso, imprimirá en el terminal el PID recibido y su valor de nice y enviará al cliente el valor del nice. En caso de que el proceso no exista en el servidor, devolverá un mensaje de error informando.
:-----

![so_2023_O](https://github.com/Danipiza/UCM/assets/98972125/67d38529-b735-4ec4-a5c5-f25ced3fff5e)
El Código1 es con la sintaxis del manual, y el Código2 es con la sintaxis de los apuntes. Solo la sintaxis de socket() y bind().
- Código1: [2023_Otcp.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/Examenes/2023_O2tcp.c)
- Código2: [2023_Otcp2.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/Examenes/2023_O2tcp2.c)
  

