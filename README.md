# PRÁCTICA FINAL - PRO1
## Creación de  una calculadora

[![N|Solid](https://www.upc.edu/comunicacio/ca/identitat/descarrega-arxius-grafics/fitxers-marca-principal/upc-positiu-p3005.png)](https://www.epsevg.upc.edu/ca/escola)

![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)

Proyecto realizado en parejas para la primera actividad de la asignatura ESIN de la EPSEVG-UPC. Como el proyecto no tuvo que ser documentado, no hay demasiada documentación aparte de los comentarios en los códigos . 

- Autores: Mario Kochan y [Jesús Gómez](https://github.com/TorchZz)
- Fecha: 07/01/2020
- Profesores: Neus Català i Jordi Esteve

## Características

- Programación en [C++](https://es.wikipedia.org/wiki/C%2B%2B)
- Uso de clases
- Uso de estructuras de datos
- Uso de tests

### Proyecto
El proyecto se basa en crear una calculadora con capacidad de hacer operaciones múltiples y hacer operaciones binarias.

Para ello, se han creado 3 clases, siendo estas: token, expressió y calculadora.

La clase token sirve para identificar un elemento y tratarlo. 
La clase expresión sirve para crear la estructura de datos para guardar el cálculo que nos pasen por calculadora.
La clase calculadora es la terminal y permite introducir cálculos y realizarlos.

### Estructura de datos utilizada
Hacemos uso de arboles binarios, listas y vectores.

### Make y ejecución del programa

En la propia raiz del documento, podemos hacer uso de un make:
```sh
make
```
Nos compilará los archivos y podremos ejecutar el programa.
```sh
./calculadora.o
```
También viene incluido archivos .in para poder hacer diff en caso que queramos checkear si el programa saca buenos resultados.
Podemos hacer uso del make para hacer los tests
```sh
make test_token
make test_expressio
make test_calculadora
```
### NOTA:
- Nota final: Aprobado (No me acuerdo de la nota, creo que un 6.8)







