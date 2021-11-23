//Linea para ejecutar: gcc investigacion.c -o investigacion -lm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


double matriz[5][6] = {};
int fila = 5;
int columna = 6;
int seed = 10395922; // Numero aleatorio para los numeros generados 
int cantidad_iteraciones = 500;
int cantidad_coordenadas = 500;

int iteraciones_mejor_solucion = 0;
double coeficiente_inercia = 0.73;
double coeficiente_aceleracion = 2;
double menor_X_global = 99999;
double menor_Y_global = 99999;
double menor_global = 9999.99;




//Graficación
double coordenadas_X[5][500] = {}; // Matriz de coordenadas
double coordenadas_Y[5][500] = {}; // Matriz de coordenadas

//Prueba 
double puntuaciones[5][500] = {};


double calcular_funcion(double x,double y){
	double resultado = sin((x/180) - 4)/ (((x*x)/100000) + 1 ) + (x*x)/500000 + cos((y/100) -1)/(((y*y)/1000000) + 1) + (y*y)/500000;
	return resultado;
}



int imprimir(){
	for (int i = 0; i < fila; i++)
	{
		for (int j = 0; j < columna; j++)
		{
			printf("matriz[%d][%d] = %lf \n",i,j, matriz[i][j]);
		}
		printf("-\n");
	}
	printf("menor_X_global: %f\n",menor_X_global);
	printf("menor_Y_global: %f\n",menor_Y_global);
	double respuesta = calcular_funcion(menor_X_global,menor_Y_global);
	printf("Menor evaluación: %f\n",respuesta );
	return 0;
}

double numero_aleatorio(int rango){
	double num = rand() % rango;
	double negativo = (double)rand() / (double)RAND_MAX;
	//printf("Probabilidad de numero negativo es: %f\n",negativo );
	if (negativo <= 0.5){
		num = num * -1;
	}
	return num;
}


void escribir_archivo(FILE* fp,double valor_x, double valor_y)
{
	fprintf(fp, "%f %f\n", valor_x,valor_y);
}



int main(int argc, char const *argv[]){
	srand(seed); 
	// Iniciacion valores para las particulas 
	for (int i = 0; i <fila; ++i){
		//Inicializacion de parametros de coordenadas
		matriz[i][0] = numero_aleatorio(1000); //Coordenada X
		matriz[i][1] = numero_aleatorio(1000); //Coordenada Y

		//La mejor posicion inicial es la aleatoria ya que no se conoce otra 
		matriz[i][2] = matriz[i][0]; //Coordenada de la mejor posicion de X
		matriz[i][3] = matriz[i][1]; //Coordenada de la mejor posicion de Y

		//Inicializacion de parametros de velocidad de las particulas 
		matriz[i][4] = numero_aleatorio(10);
		matriz[i][5] = numero_aleatorio(10);
	}

	//Iniciar el valor de G con los valores anteriormente declarados --OJO! 
	for (int i = 0; i < fila; ++i){
		double evaluacion = calcular_funcion(matriz[i][0],matriz[i][1]);
		printf("La evaluacion para %d dio: %f\n",i, evaluacion );
		if (evaluacion < menor_global){
			menor_global = evaluacion;
			menor_X_global = matriz[i][0];
			menor_Y_global = matriz[i][1];
		}
	}

	printf("-------------------------------------------\n");
	imprimir();
	printf("-------------------------------------------\n");


	//Ciclo principal del algoritmo
	while(cantidad_iteraciones != 0 ){
		printf("Iteración: %d\n",cantidad_iteraciones );

		for (int i = 0; i < fila; i++)
		{
			
			//Guardar las coordenadas de la particula i
			coordenadas_X[i][cantidad_coordenadas - cantidad_iteraciones] = matriz[i][0]; // OJO
			coordenadas_Y[i][cantidad_coordenadas - cantidad_iteraciones] = matriz[i][1];

			//Prueba 
			puntuaciones[i][cantidad_coordenadas - cantidad_iteraciones] = calcular_funcion(matriz[i][0],matriz[i][1]);



			//Calcular la función para la posicion actual de la particula i
			double evaluacion = calcular_funcion(matriz[i][0],matriz[i][1]);

			//Comprobacion con la mejor posicion de la particula i 
			double mejor_eval = calcular_funcion(matriz[i][2],matriz[i][3]);
			if(evaluacion < mejor_eval){
				//printf("La particula %d encontro una mejor solucion.\n",i );
				// Asignamos las coordenadas 
				matriz[i][2] = matriz[i][0]; //Coordenada de la mejor posicion de X
				matriz[i][3] = matriz[i][1]; //Coordenada de la mejor posicion de Y
			}

			//Comprobacion con la mejor solucion global si no cambia la solucion global aumentar el contador de iteraciones de la solucion global
			
			if(evaluacion < menor_global){

				double diferencia_evaluaciones = menor_global - evaluacion;
				printf("Valores para calcular la diferencia, menor_global:%f, evaluacion: %f \n", menor_global, evaluacion );
				printf("Diferencia de evaluaciones:%f\n",diferencia_evaluaciones );
				if (0.0001 <= diferencia_evaluaciones){
					printf("Hola entre---------------------------\n");
					menor_global = evaluacion;
					menor_X_global = matriz[i][0];
					menor_Y_global = matriz[i][1];

					//Ponemos en 0 la iteraciones desde que encontramos esta solucion para contar las 100 
					iteraciones_mejor_solucion = 0;
				} 

			}

			//Ajustar la velocidad de la particula i
			matriz[i][4] = coeficiente_inercia * matriz[i][4] +
				coeficiente_aceleracion * ((double)rand()/(double)RAND_MAX) * (matriz[i][2] - matriz[i][0]) +
				coeficiente_aceleracion * ((double)rand()/(double)RAND_MAX) * (menor_X_global - matriz[i][0]);
			matriz[i][5] = coeficiente_inercia*matriz[i][5] +
				coeficiente_aceleracion * ((double)rand()/(double)RAND_MAX) * (matriz[i][3] - matriz[i][1]) +
				coeficiente_aceleracion * ((double)rand()/(double)RAND_MAX) * (menor_Y_global - matriz[i][1]);

			//Ajustar la posicion de la particula i
			matriz[i][0] = matriz[i][0] + matriz[i][4];
			matriz[i][1] = matriz[i][1] + matriz[i][5];

			//Control de limites de la funcion
			while ((matriz[i][0] > 1000)||(matriz[i][0] < -1000)||(matriz[i][1] > 1000) || (matriz[i][1] < -1000)){
				if(matriz[i][0] > 1000){
					matriz[i][0] = matriz[i][0] - 2000;
				}else if (matriz[i][0] < -1000){
					matriz[i][0] = matriz[i][0] + 2000;
				}
				if(matriz[i][1] > 1000){
					matriz[i][1] = matriz[i][1] - 2000;
				}else if (matriz[i][1] < -1000){
					matriz[i][1] = matriz[i][1] + 2000;
				}
			}

		}



		iteraciones_mejor_solucion = iteraciones_mejor_solucion + 1;
		cantidad_iteraciones = cantidad_iteraciones - 1;
		if (iteraciones_mejor_solucion == 100){
			// Terminamos la ejecucion
			cantidad_coordenadas = cantidad_coordenadas -cantidad_iteraciones;
			cantidad_iteraciones = 0;
		}
	}




	// Creacion de archivos 
	for (int i = 0; i < fila; ++i)
	{
		FILE* fp;
		char nombreArchivo[20];
		sprintf(nombreArchivo, "coordenadas_%d",i);
		fp = fopen(nombreArchivo, "w");
		for (int j = 0; j < cantidad_coordenadas; ++j)
		{
			escribir_archivo(fp,coordenadas_X[i][j], coordenadas_Y[i][j]);
		}
		fclose(fp);
	}
	
	//Prueba
	for (int i = 0; i < fila; ++i)
	{
		FILE* fp;
		char nombreArchivo[20];
		sprintf(nombreArchivo, "prueba_%d",i);
		fp = fopen(nombreArchivo, "w");
		for (int j = 0; j < cantidad_coordenadas; ++j)
		{
			fprintf(fp, "%f \n", puntuaciones[i][j]);
		}
		fclose(fp);
	}

	imprimir();
	return 0;
}