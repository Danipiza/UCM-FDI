# UCM# UCM
### Creación y atributos de ficheros
#### Ejercicio  01.
ls(1) muestra el contenido de directorios y los atributos básicos de los ficheros. Consultar la página de manual y estudiar el uso de las opciones -a -l -d -h -i -R -1 -F y --color. Estudiar el significado de la salida en cada caso.
:-----

```
-a, --all              // No ignora entradas que empiezan por '.' ej: ".config"
-l                     // Formato de lista amplio 
-d, --directory        // Lista el directorio
-h, --human-readable   // Cambia el formato de tamaños al usar -l o -s ej: 1K 234M 2G etc.
-i, --inode            // Imprime el numero de indice de cada archivo
-R, --recursive        // Lista los directorios de forma recursiva (imprimiendo los archivos de cada directorio)
-1                     // Lista cada archivo en una linea
-F, --c                // Añade indicadores a las entradas (*/=>@|) 
--color[=WHEN]         // Lista con colores 'always' por defecto
```

#### Ejercicio  02.
| El modo de un fichero es <tipo><rwx_usuario><rwx_grupo><rwx_resto>. Comprobar los permisos de algunos directorios (con ls -ld) |
| :-----  |
- tipo: - fichero ordinario; d directorio; l enlace; c dispositivo carácter; b dispositivo bloque; p FIFO; s socket 
- rwx: r lectura (4); w escritura (2); x ejecución (1) 

#### Ejercicio 03.
| Los permisos se pueden otorgar de forma selectiva usando la notación octal o la simbólica. Ejemplo, probar las siguientes órdenes (equivalentes). ¿Cómo se podrían fijar los permisos rw-r--r-x, de las dos formas? Consultar la página de manual chmod(1) para ver otras formas de fijar los permisos (p.ej. los operadores + y -). |
| :-----  |
- chmod 540 fichero
- chmod u=rx,g=r,o= fichero 

```
chmod 0645 a.txt
chmod u=+rw-x,g=+r-wx,o=+rx-w a.txt
"ls -l <fichero>" o "stat <fichero>" // Para ver los permisos
```

#### Ejercicio  04.
Crear un directorio y quitar los permisos de ejecución para usuario, grupo y otros. Intentar cambiar al directorio.
:-----

```
chmod a-x <dir>
cd <dir> // Recibes este mensaje bash: cd: <dir>: Permission denied
```


#### Ejercicio  05.
Escribir un programa que, usando open(2), cree un fichero con los permisos rw-r--r-x. Comprobar el resultado y las características del fichero con ls(1).
:-----

Extra: Con el comando stat imprime sus permisos

Código: [ej5.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej5.c)

#### Ejercicio  06.
Cuando se crea un fichero, los permisos por defecto se derivan de la máscara de usuario (umask). Usando el comando interno de la shell umask, fijar la máscara de forma que los nuevos ficheros no tengan permiso de escritura para el grupo y no tengan ningún permiso para otros. Comprobar el funcionamiento con touch(1), mkdir(1) y ls(1).
:-----

```
umask         // Para ver la mascara actual
umask 0027    // Para quitar ejecucion para grupo y todo para otros
touch ej6.txt // Crea un fichero .txt con permisos -rw-r-----, touch crea ficheros con    0666 ~umask
mkdir ej6Dir  // Crea un directorio con permisos   drwxr-x---, mkdir crea directorios con 0777 ~umask
```


#### Ejercicio  07.
Modificar el ejercicio 5 para que, antes de crear el fichero, se fije la máscara igual que en el ejercicio 6. Comprobar el resultado con ls(1). Comprobar que la máscara del proceso padre (la shell) no cambia.
:-----

Código: [ej7.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej7.c)

#### Ejercicio  08.
ls(1) puede mostrar el inodo con la opción -i. El resto de información del inodo puede obtenerse usando stat(1). Consultar las opciones del comando y comprobar su funcionamiento.
:-----

#### Ejercicio  09.
| Escribir un programa que emule el comportamiento de stat(1) y muestre: |
| :-----  |
- El número major y minor asociado al dispositivo.
- El número de inodo del fichero.
- El tipo de fichero (directorio, enlace simbólico o fichero ordinario).
- La hora en la que se accedió el fichero por última vez. ¿Qué diferencia hay entre st_mtime y st_ctime? 


Código: [ej9.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej9.c)

#### Ejercicio  10.
| Los enlaces se crean con ln(1): |
| :-----  |
- Con la opción -s, se crea un enlace simbólico. Crear un enlace simbólico a un fichero ordinario y otro a un directorio. Comprobar el resultado con ls -l y ls -i. Determinar el inodo de cada fichero.
- Repetir el apartado anterior con enlaces rígidos. Determinar con stat(1) los inodos de los ficheros y las propiedades, en especial, el número de enlaces.
- ¿Qué sucede cuando se borra uno de los enlaces rígidos? ¿Qué sucede si se borra uno de los enlaces simbólicos? ¿Y si se borra el fichero original?

```
ln -s ej7.txt ej10sym // Enlace simbolico a fichero
ln -s ej6Dir/ ej10Dirsym // Enlace simbolico a directorio
ln ej7.txt ej10eduro // Enlace rigido/duro a fichero
ln ej6Dir/ ej10Direduro // ERROR: ln: ej6Dir/: hard link not allowed for directory

           | Tiene 2 copias 
-rw-r----- 2 root root     0 Jun 11 21:07 ej10eduro
-rw-r----- 2 root root   997 Jun 11 21:07 ej7.txt
El enlace rigido puede existir sin el original, pero el simbolico no (se convierte en un enlace roto).
```


#### Ejercicio  11.
link(2) y symlink(2) crean enlaces rígidos y simbólicos, respectivamente. Escribir un programa que reciba una ruta a un fichero como argumento. Si la ruta es un fichero regular, creará un enlace simbólico y rígido con el mismo nombre terminado en .sym y .hard, respectivamente. Comprobar el resultado con ls(1).
:-----

Código: [ej11.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej11.c)

#### Ejercicio  12.
Escribir un programa que redirija la salida estándar a un fichero cuya ruta se pasa como primer argumento. Probar haciendo que el programa escriba varias cadenas en la salida estándar.
:-----

Código: [ej12.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej12.c)

#### Ejercicio  13.
Modificar el programa anterior para que también redirija la salida estándar de error al fichero. Comprobar el funcionamiento incluyendo varias sentencias que impriman en ambos flujos. 
:-----

Código: [ej13.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej13.c)

¿Hay diferencia si las redirecciones se hacen en diferente orden? ¿Por qué ls > dirlist 2>&1 es diferente a ls 2>&1 > dirlist?
```
Si hay diferencia.
ls > dirlist 2>&1
  // Redirije la salida estandar al fichero dirlist,
  // y luego 2>&1 redirige la salida de error (2) a la salida estandar (1), es decir, el fichero dirlist.
ls 2>&1 > dirlist
  // Primero la salida de error se redirige a la salida estandar, y luego la salida estandar se redirige al fichero.
En la primera opcion ambos apuntan al fichero. En la segunda, solo la salida estandar apunta al fichero.

Explicación de 2>&1:
- "2":  se refiere a stderr.
- "1":  se refiere a stdout.
- ">&": es un operador que redirige un descriptor de archivo a otro.
```

#### Ejercicio  14.
El estado y los cerrojos de fichero en uso en el sistema se pueden consultar en el fichero /proc/locks. Estudiar el contenido de este fichero
:-----



#### Ejercicio  15.

| Escribir un programa que intente bloquear un fichero usando lockf(3): |
| :-----  |
- Si lo consigue, mostrará la hora actual y suspenderá su ejecución durante 10 segundos con sleep(3). A continuación, desbloqueará el fichero, suspenderá su ejecución durante otros 10 segundos y terminará.
- Si no lo consigue, el programa mostrará el error con perror(3) y terminará. 


Código: [ej15.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej15.c)

#### Ejercicio  16 (Opcional).
flock(1) proporciona funcionalidad de cerrojos antiguos BSD en guiones shell. Consultar la página de manual y el funcionamiento del comando.
:-----



#### Ejercicio  17.
| Escribir un programa que muestre el contenido de un directorio cuya ruta se proporciona como argumento. Para ello, el programa: |
| :-----  |
- Cambiará al directorio y comprobará que tiene acceso.
- Recorrerá las entradas del directorio y escribirá su nombre de fichero. Además:
  - Si es un fichero regular y tiene permiso de ejecución para usuario, grupo u otros, escribirá el carácter ‘*’ después del nombre.
  - Si es un directorio, escribirá el carácter ‘/’ después del nombre.
  - Si es un enlace simbólico, escribirá “->” y el nombre del fichero enlazado obtenido con readlink(2).
- Al final, escribirá el tamaño total que ocupan los ficheros regulares en kilobytes




Código: [ej17.c](https://github.com/Danipiza/UCM/blob/main/4to/1er_cuatrimestre/ASOR/SO/T2/ej17.c)
