#include <stdio.h>
#include <stdlib.h>

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


int main(int argc, char const *argv[])
{
   //Arreglos para guardar los valores de cada caja y los leidos del archivo
   long numeros[10000] = {0};
   long cajaA[10000] = {0};
   long cajaB[10000] = {0};
   long cajaC[10000] = {0};
   long sumas[3] = {0};
   //long sumaA, sumaB,sumaC;
	leerArchivo(numeros);
   
   /*for (long i = 0; i < 10000; i++)
   {
      printf("%ld\n", numeros[i]);
   }*/

   //1. Acomodar los numeros de mayor al menor 
   ordenarArreglo(numeros, 10000);
   /*for (long i = 0; i < 10000; i++)
   {
      printf("%ld\n", numeros[i]);
   }*/
   //2. Repartir los numeros dando al grupo con la menor suma el siguiente numero mas grande del arreglo ordenado.
   repartirNumeros(numeros,cajaA,cajaB,cajaC,sumas);
   //3. Comparar las diferencias de los grupos


   printf("El valor de la cajaA fue de: %ld\n", sumas[0]);
   printf("El valor de la cajaB fue de: %ld\n", sumas[1]);
   printf("El valor de la cajaC fue de: %ld\n", sumas[2]);


   //4. Fin ? 

	return 0;
}