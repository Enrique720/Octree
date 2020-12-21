# Octree

## Integrantes
- Enrique Sobrados
- Cesar Madera
- Ariana Villegas

## Descripcion del proyecto:
- Utilizacion de la estructura Octree para el guardado de una imagen tridimencional en disco, para luego poder obtener cortes a traves de un plano que rota a travez de sus ejes y comparar la complejidad de la recuperacion del corte y el espacio de la memoria ocupado por ambos metodos.

## Resumen de los archivos. 
- plano.h: contiene la estructura del plano y las funciones para obtener la formula del plano, los puntos que intersectan a un cubo en las aristas y obtener una coordenada seteando los otros dos.
- octree.h: contiene la estructura del octree y la funcion get_cut, la cual realiza el recorrido por la estructura, pintando el corte que se va a devolver.
- point.h: contiene la estructura de un punto y tiene sobrecargado las diferentes funciones y operadores para que pueda ser usado en la ejecucion del proyecto.
- functions.h: contiene las diferentes funciones para la binarizacion de las imagenes, la creacion de la imagen 3D, la obtencion del corte en base al cubo original y la creacion de la estructura. 
- tester.h: contiene el test con 20 cortes aleatorios. Genera los cortes en las carpetas testImgR y testImg, donde la primera contiene los cortes utilizando el cubo, mientras que en la segunda, con el octree

## Ejecucion del programa:
- g++ main.cpp -pthread -lX11 -w
- ./a.out
