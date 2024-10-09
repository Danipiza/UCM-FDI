# UCM# UCM

## Gestión de errores

#### Ejercicio  01.
Añadir el código necesario para gestionar correctamente los errores generados por setuid(2) con perror(3). Consultar en el manual el propósito de la llamada y su prototipo.
:-----
```
int main() {
  setuid(0);
  return 1;
}
```

Código: [ej1.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej1.c)

#### Ejercicio  02.
Imprimir el código numérico de error generado por la llamada del código anterior y el mensaje asociado obtenido con strerror(3).
:-----

Código: [ej2.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej2.c)

#### Ejercicio  03.
Escribir un programa que imprima todos los mensajes de error disponibles en el sistema. Considerar inicialmente que el límite de errores posibles es 255.
:-----

Código: [ej3.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej3.c)

## Información del sistema

#### Ejercicio  04.
Consultar la página de manual de uname(1) y obtener información del sistema.
:-----

#### Ejercicio  05.
Escribir un programa que muestre, con uname(2), cada aspecto del sistema y su valor. Comprobar la correcta ejecución de la llamada.
:-----

Código: [ej5.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej5.c)

#### Ejercicio  06.
Escribir un programa que obtenga, con sysconf(3), información de configuración del sistema e imprima, por ejemplo, la longitud máxima de los argumentos, el número máximo de hijos y el número máximo de ficheros abiertos.
:-----

Código: [ej6.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej6.c)

#### Ejercicio  07.
Escribir un programa que obtenga, con pathconf(3), información de configuración del sistema de ficheros e imprima, por ejemplo, el número máximo de enlaces, el tamaño máximo de una ruta y el de un nombre de fichero.
:-----

Código: [ej7.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej7.c)

## Información del usuario

#### Ejercicio  08.
Consultar la página de manual de id(1) y comprobar su funcionamiento.
:-----

#### Ejercicio  09.
Escribir un programa que muestre, igual que id, el UID real y efectivo del usuario. ¿Cuándo podríamos asegurar que el fichero del programa tiene activado el bit setuid?
:-----

Código: [ej9.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej9.c)

#### Ejercicio  10.
Modificar el programa anterior para que muestre además el nombre de usuario, el directorio home y la descripción del usuario.
:-----

Código: [ej10.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej10.c)

## Información horaria del sistema

#### Ejercicio  11.
Consultar la página de manual de date(1) y familiarizarse con los distintos formatos disponibles para mostrar la hora
:-----

#### Ejercicio  12.
Escribir un programa que muestre la hora, en segundos desde el Epoch, usando time(2).
:-----

Código: [ej12.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej12.c)

#### Ejercicio  13.
Escribir un programa que mida, en microsegundos, lo que tarda un bucle que incrementa una variable un millón de veces usando gettimeofday(2)
:-----

Código: [e13j.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej13.c)

#### Ejercicio  14.
Escribir un programa que muestre el año usando localtime(3).
:-----

Código: [ej14.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej14.c)

#### Ejercicio  15.
Modificar el programa anterior para que imprima la hora de forma legible, como "Tue Nov 7 10:34:51 CET 2023", usando strftime(3).
:-----

Código: [ej15.c](https://github.com/Danipiza/UCM/blob/main/4to/ASOR/SO/T1/ej15.c)