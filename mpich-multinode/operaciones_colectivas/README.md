# Ejercicios Plataformas a gran Escala

Andrés Camilo Arias Martinez, codigo 1733956 - 
Henry Salazar carvajal, codigo 1731445 

En esta carpeta se encuentran los archivos de los ejercicios de la tarea OPERACIONES COLECTIVAS.

## mpibcast_s_r.c
Realiza la funcionalidad de MPI_Bcast pero utilizando las funciones MPI_Send y MPI_Recv.

## mpiscatter_s_r.c
Realiza la funcionalidad de MPI_Gather pero utilizando las funciones MPI_Send y MPI_Recv.

## mpigather_s_r.c
Realiza la funcionalidad de MPI_Gather pero utilizando las funciones MPI_Send y MPI_Recv.

## my_bcast.c
Funcion alternativa descargada de el enlace proporcionado por el profesor, 
que realiza la funcionalidad de MPI_Bcast pero utilizando las funciones MPI_Send y MPI_Recv.

## compare_bcast.c
codigo que compara los tiempos de ejecucion de la funcion MPI_Bcast y my_bcast().

## mpipromedio.c
Se crea un vector de N numeros aleatorios y lo divide entre los procesos usando MPI_Scatter, 
cada proceso saca un promedio parcial de su parte del vecotr y lo envia al proceso root usando MPI_Gather,
el proceso root suma todos los promedios parciales y obtiene un promedio global.

## mpireduce.c
Se crea un vector de N numeros aleatorios y lo divide entre los procesos usando MPI_Scatter, 
cada proceso saca un promedio parcial de su parte del vecotr y lo envia al proceso root usando MPI_Reduce, 
usando MPI_SUM, el proceso root recive la suma de todos los promedios parciales, 
luego se divide este resultado entre el total de procesos y se obtiene el promedio global.

