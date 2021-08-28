#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
 * ESTE METODO NO SE USA FUE UNA VERSION EXPERIMENTAL
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
 * Método que se encarga de repartir los números del arreglo ordenados de menor a mayor de manera aleatoria entre las 3 cajas y compara 
 * en cada evaluación la diferencia y en caso de haber encontrado una diferencia que es mas pequeña que la anterior mas pequeña
 * la almacena. 
 * Se detiene cuando se encuentra una diferencia menor a 0 o cuando se realizan 10 millones de ejecuciones.
*/
int repartirNumerosAleatorio(long * numeros,long * cajaA,long * cajaB,long * cajaC, long * sumas)
{
   double menorDiferenciaEncontrada = 9999999;
   int indexMasGrande = 0;
   long sumaA = 0;
   long sumaB = 0;
   long sumaC = 0;
   long indiceA = 0;
   long indiceB = 0;
   long indiceC = 0;

   //Numero maximo de evaluaciones
   int i ;
   for (i = 0; i < 10000000; ++i)
   {
      //Reiniciar los valores de los indices.
      sumaA = 0;
      sumaB = 0;
      sumaC = 0;
      indiceA = 0; 
      indiceB = 0;
      indiceC = 0;
      long cajaA_Temp[10000] = {0};
      long cajaB_Temp[10000] = {0};
      long cajaC_Temp[10000] = {0};


      //Repartir los numeros de manera aleatoria 
      for (int j = 9999; j >= 0; j--)
      {
         //Repartir numero aleatoriamente entre los dos mas pequeños
         if (indexMasGrande == 0){
            //Entre los 3
            int num = rand();
            num = num %3;
            if(num == 0){
               //Se lo sumamos a la cajaA
               cajaA_Temp[indiceA] = numeros[j];
               indiceA++;
               sumaA += numeros[j]; //Sumamos el numero
            }else if (num == 1){
               //Se lo sumamos a la cajaB
               cajaB_Temp[indiceB] = numeros[j];
               indiceB++;
               sumaB += numeros[j]; //Sumamos el numero
            }else if (num == 2){
               //Se lo sumamos a la cajaC
               cajaC_Temp[indiceC] = numeros[j];
               indiceC++;
               sumaC += numeros[j]; //Sumamos el numero
            }

         }else if(indexMasGrande == 1){
            //La suma mas grande es la de la caja A, meter el valor en B o C 
            int num = rand();
            num = num %2;
            if(num == 0){
               //Sumarlo a B
               cajaB_Temp[indiceB] = numeros[j];
               indiceB++;
               sumaB += numeros[j]; //Sumamos el numero
            }else if (num == 1){
               //Sumarlo a C
               cajaC_Temp[indiceC] = numeros[j];
               indiceC++;
               sumaC += numeros[j]; //Sumamos el numero
            }

         }else if(indexMasGrande == 2){
            //La suma mas grande es la de la caja B, meter el valor en A o C 
            int num = rand();
            num = num %2;
            if(num == 0){
               //Sumarlo a A
               cajaA_Temp[indiceA] = numeros[j];
               indiceA++;
               sumaA += numeros[j]; //Sumamos el numero
            }else if (num == 1){
               //Sumarlo a C
               cajaC_Temp[indiceC] = numeros[j];
               indiceC++;
               sumaC += numeros[j]; //Sumamos el numero
            }            

         }else if(indexMasGrande == 3){
            //La suma mas grande es la de la caja C, meter el valor en B o A 
            int num = rand();
            num = num %2;
            if(num == 0){
               //Sumarlo a B
               cajaB_Temp[indiceB] = numeros[j];
               indiceB++;
               sumaB += numeros[j]; //Sumamos el numero
            }else if (num == 1){
               //Sumarlo a A
               cajaA_Temp[indiceA] = numeros[j];
               indiceA++;
               sumaA += numeros[j]; //Sumamos el numero
            }
         }

         //Poner la nueva suma mas alta
         if((sumaA >= sumaB) && (sumaA >= sumaC)){
            //A es la nueva suma mas alta
            //printf("El mas grande fue A\n");
            indexMasGrande = 1;
         }else if((sumaB >= sumaA) && (sumaB >= sumaC)){
            //B es la nueva suma mas alta
            //printf("El mas grande fue B\n");
            indexMasGrande = 2;

         }else if((sumaC >= sumaB) && (sumaC >= sumaA)){
            //C es la nueva suma mas alta
            //printf("El mas grande fue C\n");
            indexMasGrande = 3;

         }else{
            //Caso en que algunos sean iguales
            printf("IGuales?...\n");
         }
      }

      //Calcular la diferencia entre las sumas 
      long diferencia = pow((sumaA- sumaB),2) + pow((sumaA-sumaC),2) +pow((sumaB-sumaC),2);
      long double diferencia_div = diferencia / pow(10,12);
      
      if (menorDiferenciaEncontrada > diferencia){
         menorDiferenciaEncontrada = diferencia;
         //printf("La diferencia es: %ld\n", diferencia );
      }
      
      if(menorDiferenciaEncontrada < 10){
         sumas[0]= sumaA;
         sumas[1]= sumaB;
         sumas[2]= sumaC;
         cajaA = cajaA_Temp;
         cajaB = cajaB_Temp;
         cajaC = cajaC_Temp;
         break;
      }
   }
   return i-1;
}



/*
 * Método que se encarga de escribir el archivo de salida con todo lo que se pide en la especificación de la tarea.
*/
int escribirArchivo(long * sumas, long diferencia,long double diferencia_div, long * cajaA,long * cajaB,long * cajaC, int ultimaevaluacion)
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
   fprintf(archivo_respuesta,"Evaluaciones: %d\n",ultimaevaluacion);
   fprintf(archivo_respuesta,"------Sumas optenidas------\n");
   fprintf(archivo_respuesta,"Suma de la cajaA:%ld\n", sumas[0]);
   fprintf(archivo_respuesta,"Suma de la cajaB:%ld\n", sumas[1]);
   fprintf(archivo_respuesta,"Suma de la cajaC:%ld\n", sumas[2]);
   fprintf(archivo_respuesta,"Diferencia(f): %ld\n",diferencia);
   fprintf(archivo_respuesta,"Diferencia al dividirla entre 10^12(f): %Lf\n",diferencia_div);
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
   clock_t inicio, fin;
   long double duracionPrograma;

   //Leemos el archivo y guardamos los valores.
	leerArchivo(numeros);

   //Iniciamos reloj 
   inicio = clock();

   //1. Acomodar los numeros de mayor al menor 
   ordenarArreglo(numeros, 10000);

   //2. Repartir los numeros dando al grupo con la menor suma el siguiente numero mas grande del arreglo ordenado.
   int ultimaevaluacion = repartirNumerosAleatorio(numeros,cajaA,cajaB,cajaC,sumas);

   //3. Comparar las diferencias de los grupos
   printf("La evaluacion : %d fue la que dio la menor diferencia, de los 10 millones.\n", ultimaevaluacion);
   printf("El valor de la cajaA fue de: %ld\n", sumas[0]);
   printf("El valor de la cajaB fue de: %ld\n", sumas[1]);
   printf("El valor de la cajaC fue de: %ld\n", sumas[2]);
   long diferencia = pow((sumas[0]- sumas[1]),2) + pow((sumas[0]-sumas[2]),2) +pow((sumas[1]-sumas[2]),2);
   long double diferencia_div = diferencia / pow(10,12);
   printf("La diferencia es: %ld\n", diferencia );
   printf("La diferencia al dividirla por 10^12 es: %Lf\n", diferencia_div );

   //Fin del algoritmo
   fin = clock();
   duracionPrograma = ((double) (fin - inicio))/CLOCKS_PER_SEC; //Formula tomada de: https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
   printf("La duracion del programa fue: %Lf\n", duracionPrograma);
   //4. Escritura del archivo de salida
   escribirArchivo(sumas, diferencia, diferencia_div, cajaA, cajaB, cajaC, ultimaevaluacion);
	return 0;
}