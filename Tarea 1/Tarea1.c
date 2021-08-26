#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
 * Método que se encarga de leer el archivo de números y los almacena en un array de tipo long.
*/
int leerArchivo(long * numeros)
{
   long index = 0;
   long valor;
   FILE * archvo_numeros = fopen("numbers.txt", "r"); 

   while(fscanf(archvo_numeros,"%ld",&valor) >=0)
   {
      numeros[index] = valor;
      index++;
   }

   fclose(archvo_numeros);
   return 0;
}

/*
 * Método que se encarga de ordenar los números del arreglo de numeros de menor a mayor.
*/
int ordenarArreglo(long * numeros, long tamanioArreglo)
{
   long temp, i, j, k;
   for (j = 0; j < tamanioArreglo; ++j)
   {
      for (k = j + 1; k < tamanioArreglo; ++k)
      {
         if (numeros[j] > numeros[k])
         {
            temp = numeros[j];
            numeros[j] = numeros[k];
            numeros[k] = temp;
         }
      }
   }
   return 0;
}

/*
 * Método que se encarga de repartir los números en las distintas cajas. Para esto se reparte el array de números
 * que ya ha sido ordenado de menor a mayor anteriormente y se reparten primero los números más grandes, o sea de 
 * atras para delante. Los tres primeros números en cada caja se hacen de manera manual, esto es los tres números 
 * mas grandes se asignan a A, B y C respectivamente. Despues cada nuevo número que se extraiga del array se colocará 
 * en la caja cuya suma total sea la mas baja. 
 * Se continua de esta manera hasta que se acaben los números.
*/
int repartirNumeros(long * numeros,long * cajaA,long * cajaB,long * cajaC, long * sumas)
{
   long sumaA = 0;
   long sumaB = 0;
   long sumaC = 0;
   long indiceA = 0;
   long indiceB = 0;
   long indiceC = 0;
   
   //Caso inicial
   sumaA += numeros[9999];
   cajaA[indiceA] = numeros[9999];
   indiceA++;


   sumaB += numeros[9998];
   cajaB[indiceB] = numeros[9998];
   indiceB++;


   sumaC += numeros[9997];
   cajaC[indiceC] = numeros[9997];
   indiceC++;


   for(int index = 9996; index > 0;index--){
      
      if((sumaA <= sumaB) && (sumaA <= sumaC)) {
         //Entonces la suma de A es la mas pequeña 
         cajaA[indiceA] = numeros[index];
         indiceA++;
         sumaA += numeros[index]; //Sumamos el numero
      }else if ((sumaB <= sumaA) && (sumaB <= sumaC )){
         //Entonces la suma de B es la mas pequeña
         cajaB[indiceB] = numeros[index];
         indiceB++;
         sumaB += numeros[index];// Sumamos el numero a B para actualizar.
      }else if((sumaC <= sumaA) && (sumaC <= sumaB )){
         //Entonces la suma de C es la mas pequeña 
         cajaC[indiceC] = numeros[index]; //Guardamos el valor en la caja
         indiceC++;
         sumaC += numeros[index];
      }else{
         //Caso de prueba
         printf("hola");
      }
   }
   sumas[0] = sumaA;
   sumas[1] = sumaB;
   sumas[2] = sumaC;

   return 0;
} 

/*
 * Método que se encarga de escribir el archivo de salida con todo lo que se pide en la especificación de la tarea.
*/
int escribirArchivo(long * sumas, long diferencia, double diferencia_div, long * cajaA,long * cajaB,long * cajaC)
{
   FILE * archivo_respuesta = fopen("salida.txt","w");
   int indexCajas = 0;
   //Manejo de errores 
   if(archivo_respuesta == NULL)
   {
      printf("Error al crear el archivo_respuesta!");   
      exit(1);             
   }
   fprintf(archivo_respuesta,"----Estudiante: Jose Ignacio Viquez Rojas B78451, Tarea 1----\n");
   fprintf(archivo_respuesta,"Evaluaciones: 1\n");
   fprintf(archivo_respuesta,"------Sumas optenidas------\n");
   fprintf(archivo_respuesta,"Suma de la cajaA:%ld\n", sumas[0]);
   fprintf(archivo_respuesta,"Suma de la cajaB:%ld\n", sumas[1]);
   fprintf(archivo_respuesta,"Suma de la cajaC:%ld\n", sumas[2]);
   fprintf(archivo_respuesta,"Diferencia(f): %ld\n",diferencia);
   fprintf(archivo_respuesta,"Diferencia al dividirla entre 10^12(f): %f\n",diferencia_div);
   fprintf(archivo_respuesta,"Asignaciones de los numeros:\n");

   fprintf(archivo_respuesta,"------CajaA------\n");   
   while(cajaA[indexCajas]!= 0){
      //printf("indexCajas: %i\n",indexCajas);
      fprintf(archivo_respuesta,"%ld\n",cajaA[indexCajas]);
      indexCajas++;
   }

   indexCajas = 0;
   fprintf(archivo_respuesta,"------CajaB-----\n");   
   while(cajaB[indexCajas]!= 0){
      //printf("indexCajas: %i\n",indexCajas);
      fprintf(archivo_respuesta,"%ld\n",cajaB[indexCajas]);
      indexCajas++;
   }

   indexCajas = 0;
   fprintf(archivo_respuesta,"------CajaC-----\n");   
   while(cajaC[indexCajas]!= 0){
      //printf("indexCajas: %i\n",indexCajas);
      fprintf(archivo_respuesta,"%ld\n",cajaC[indexCajas]);
      indexCajas++;
   }


   fclose(archivo_respuesta);
   return 0;
}

/*
 * Funcion main con la logica general del programa, realiza llamados a distintos metodos.
*/
int main(int argc, char const *argv[])
{
   //Arreglos para guardar los valores de cada caja y los numeros leidos del archivo
   long numeros[10000] = {0};
   long cajaA[10000] = {0};
   long cajaB[10000] = {0};
   long cajaC[10000] = {0};
   long sumas[3] = {0};

   //Leemos el archivo y guardamos los valores.
	leerArchivo(numeros);
   //1. Acomodar los numeros de mayor al menor 
   ordenarArreglo(numeros, 10000);
   //2. Repartir los numeros dando al grupo con la menor suma el siguiente numero mas grande del arreglo ordenado.
   repartirNumeros(numeros,cajaA,cajaB,cajaC,sumas);
   //3. Comparar las diferencias de los grupos
   printf("El valor de la cajaA fue de: %ld\n", sumas[0]);
   printf("El valor de la cajaB fue de: %ld\n", sumas[1]);
   printf("El valor de la cajaC fue de: %ld\n", sumas[2]);
   long diferencia = pow((sumas[0]- sumas[1]),2) + pow((sumas[0]-sumas[2]),2) +pow((sumas[1]-sumas[2]),2);
   double diferencia_div = diferencia / pow(10,12);
   printf("La diferencia es: %ld\n", diferencia );
   printf("La diferencia al dividirla por 10^12 es: %f\n", diferencia_div );
   //4. Escritura del archivo de salida
   escribirArchivo(sumas, diferencia, diferencia_div, cajaA, cajaB, cajaC);

	return 0;
}