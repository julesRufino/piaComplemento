Proyecto Final

Lenguaje C++

Elabora un programa en lenguaje C++ que muestre el siguiente menú:
a. Registro de Vuelos
b. Listado de Destinos
c. Listado de Vuelos
d. Salir

***Opción a***. Elabora una pantalla en la cual el usuario pueda comprar un boleto para viajar a algún
destino de la República Mexicana. 
El programa deberá detectar si los archivos no tienen información. 
En este caso antes de que inicie el registro de los vuelos se lo informará al usuario para
primero dar de alta registros para los Destinos.
La opción para registro de destinos impleméntala donde consideres apropiado.

Los datos que se pedirán para el registro de los destinos son:

-Clave del destino. Validar que la clave inicie con una letra mayúscula, posteriormente un “_”
seguido de 4 dígitos.

-Descripción. Iniciará con una letra mayúscula y después podrá contener cualquier cantidad
de letras mayúsculas, minúsculas y espacio.

-Precio. Contendrá de 3 a 5 dígitos, posteriormente un “.” Y terminará con dos dígitos.

Las tres validaciones de los destinos se realizarán mediante expresiones regulares.

Utiliza un archivo secuencial de texto para el registro llamado destinos.txt.

Para el registro de los viajes se utilizará un archivo de acceso secuencial llamado viajes.txt.

Para el registro de los viajes de le pedirá al usuario la siguiente información:

-Nombre del destino (descripción). Primero validar que lo tecleado por el usuario sea lo
indicado en el alta de destinos, cuando sea correcto, revisar que el nombre exista en el
archivo destinos.txt

-Viaje redondo. El usuario solo podrá escribir “si” o “no”. Utiliza expresiones regulares.

-Fecha de viaje de ida. Deberá tener el formato DD-MM-AAAA. Valida la captura mediante una
expresión regular. Si el usuario en el campo viaje redondo indica si, se deberá pedir también
la fecha de viaje de regreso. También validada con el mismo criterio que el de ida.

Cuando el usuario indique el nombre del destino se mostrará el precio y cuando indique “si” en viaje
redondo, se mostrará el doble del precio.

***Opción b***. Mostrar un listado de todos los destinos registrados con toda su información. La
impresión será de forma tabular utilizando los manipuladores de flujo vistos en el capítulo 21 del
libro.

***Opción c***. Solicitarle al usuario una fecha que será validada con el mismo criterio del registro de
vuelos, posteriormente se mostrarán un listado con la clave, descripción y precio de los vuelos
registrados para esa fecha. En caso de que existan varios vuelos al mismo destino, únicamente se
mostrará uno (no mostrar información repetida).

El reporte será en forma tabular con las mismas indicaciones del b)
En esta opción también se mostrará un listado con todos los vuelos registrados y con toda la
información de cada uno de ellos. (no mostrar información repetida).

Estos dos reportes acomódalos en el menú de acuerdo con lo que consideres mejor.
Indicaciones generales:
-Para la estructura del programa utilizar funciones.
-Implementa al menos 5 excepciones en el programa (diferentes).
-No es necesario crear un archivo de cabecera propio.
-No se utilizarán estructuras para los archivos.
-El manejo de archivos es de acuerdo con lo visto para C.