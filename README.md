# Codificación de Huffman.

El Algoritmo de Huffman es un método de compresión de datos sin pérdida (lossless) que se utiliza para crear códigos de longitud variable.

Su objetivo es reducir el tamaño de un archivo (texto, imagen, audio, etc.) asignando una representación binaria (código) más corta a los símbolos o caracteres que aparecen con mayor frecuencia, y códigos más largos a los que aparecen con menos frecuencia.

El comando para ejecutar la practica es el siguiente:

```
gcc -c main.c -o main.o
gcc -c helpers.c -o helpers.o
gcc -c lista.c -o lista.o
gcc main.o helpers.o tiempo.c lista.o -o main

./main
```
