# UCM

### Gestión de direcciones

#### Ejercicio 01.
Escribir un programa que obtenga todas las posibles direcciones con las que se podría crear un socket asociado a un host dado como primer argumento del programa. Para cada dirección, mostrar la IP numérica, la familia de protocolos y tipo de socket. El programa se implementará usando getaddrinfo(3) para obtener la lista de posibles direcciones de socket (struct sockaddr). Cada dirección se imprimirá en su valor numérico, usando getnameinfo(3) con el flag NI_NUMERICHOST, así como la familia de direcciones y el tipo de socket. Comprobar el resultado para:
:-----
- Una dirección IPv4 válida (ej. “147.96.1.9”).
- Una dirección IPv6 válida (ej. “fd00::a:0:0:0:1”).
- Un nombre de dominio válido (ej. “www.google.com”).
- Un nombre en /etc/hosts válido (ej. “localhost”).
- Una dirección o nombre incorrectos en cualquiera de los casos anteriores.

Código: [ej1.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej1.c)


#### Ejercicio 02.

| Escribir un servidor UDP de hora de forma que: |
| :-----  |
| La dirección y el puerto son el primer y segundo argumento del programa. Las direcciones pueden expresarse en cualquier formato (nombre de host, notación de punto…). Además, el servidor debe funcionar con direcciones IPv4 e IPv6. |
| El servidor recibirá un comando (codificado en un carácter), de forma que ‘t’ devuelva la hora, ‘d’ devuelve la fecha y ‘q’ termina el proceso servidor |
| En cada mensaje el servidor debe imprimir el nombre y puerto del cliente, usar getnameinfo(3). |


Probar el funcionamiento del servidor con la herramienta Netcat (comando nc o ncat) como cliente. Nota: Dado que el servidor puede funcionar con direcciones IPv4 e IPv6, hay que usar struct sockaddr_storage para acomodar cualquiera de ellas, por ejemplo, en recvfrom(2).
![so_t4_ej7](https://github.com/Danipiza/UCM/assets/98972125/2a752716-4549-4566-9a29-eb7d0cb42acb)

Código: [ej2.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej2.c)



#### Ejercicio 03.
Escribir el cliente para el servidor de hora. El cliente recibirá como argumentos la dirección del servidor, el puerto del servidor y el comando. Por ejemplo, para solicitar la hora, ./time_client 192.128.0.1 3000 t.
:-----

Código: [ej3.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej3.c)



#### Ejercicio 04.
Modificar el servidor para que, además de poder recibir comandos por red, los pueda recibir directamente por el terminal, leyendo dos caracteres (el comando y ‘\n’) de la entrada estándar. Multiplexar el uso de ambos canales usando select(2).
:-----

![so_t4_ej2](https://github.com/Danipiza/UCM/assets/98972125/7c8ab955-2891-4f09-b92f-7fe83b331f70)

Código: [ej4.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej4.c)



#### Ejercicio 05.
Convertir el servidor UDP en multi-proceso. Una vez asociado el socket a la dirección local con bind(2), crear varios procesos que llamen a recvfrom(2) de forma que cada uno atenderá un mensaje de forma concurrente. Imprimir el PID del proceso servidor para comprobarlo. Para terminar el servidor, enviar la señal SIGTERM al grupo de procesos
:-----

Código: [ej5.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej5.c)

### Protocolo TCP - Servidor de eco

#### Ejercicio 06.
Crear un servidor TCP de eco que escuche por conexiones entrantes en una dirección (IPv4 o IPv6) y puerto dados. Cuando reciba una conexión entrante, debe mostrar la dirección y número de puerto del cliente. A partir de ese momento, enviará al cliente todo lo que reciba desde el mismo (eco). Comprobar su funcionamiento empleando la herramienta Netcat como cliente. Comprobar qué sucede si varios clientes intentan conectar al mismo tiempo
:-----

![so_t4_ej6](https://github.com/Danipiza/UCM/assets/98972125/c2485ca7-478d-4cc5-b890-b47804031c76)

Código: [ej6.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej6.c)



#### Ejercicio 07.
Escribir el cliente para conectarse con el servidor del ejercicio anterior. El cliente recibirá la dirección y el puerto del servidor como argumentos y, una vez establecida la conexión con el servidor, le enviará lo que el usuario escriba por teclado. Mostrará en la consola la respuesta recibida desde el servidor. Cuando el usuario escriba el carácter ‘Q’ como único carácter de una línea, el cliente cerrará la conexión con el servidor y terminará.
:-----

Código: [ej7.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej7.c)



#### Ejercicio 08 (+ ejercicio 09).
Modificar el código del servidor para que acepte varias conexiones simultáneas. Cada petición debe gestionarse en un proceso diferente siguiendo el patrón accept-and-fork. El proceso padre debe cerrar el socket devuelto por accept(2). 
:-----

Código: [ej8.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T4/ej8.c)
Se añade la logica para gestionar los procesos hijos, para que no se conviertan en zombies.


