//Linea para ejecutar: gcc investigacion.c -o investigacion -lm
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int matris[3][6] = {};
int  fila = 3;
int  columna = 6;
int seed = 10395922; // Numero aleatorio para los numeros generados 
int rango_velocidad = 12; // Rango para la velocidad

int menor_X_global = 99999;
int menor_Y_global = 99999;
double menor_global = 9999.99;



int imprimir(){
	for (int i = 0; i < fila; i++)
	{
		for (int j = 0; j < columna; j++)
		{
			printf("matris[%d][%d] = %d \n",i,j, matris[i][j]);
		}
		printf("-\n");
	}
	printf("menor_X_global: %d\n",menor_X_global);
	printf("menor_Y_global: %d\n",menor_Y_global);
	printf("Hola mundo\n");
	return 0;
}

int numero_aleatorio(int rango){
	int num = rand() % rango;
	float negativo = (double)rand() / (double)RAND_MAX;
	if (negativo < 0.5){
		num = num * -1;
	}

	return num;
}

double calcular_funcion(int x,int y){
	double resultado = sin(x/180 - 4)/ ((x*x)/100000 + 1 ) + (x*x)/500000 + cos(y/100 -1)/((y*y)/1000000 + 1) + (y*y)/500000;
	return resultado;
}

int main(int argc, char const *argv[])
{
	srand(seed); 
	// Iniciacion valores para las particulas 
	for (int i = 0; i <fila; ++i)
	{
		//Inicializacion de parametros de coordenadas
		matris[i][0] = numero_aleatorio(1000); //Coordenada X
		matris[i][1] = numero_aleatorio(1000); //Coordenada Y

		//La mejor posicion inicial es la aleatoria ya que no se conoce otra 
		matris[i][2] = matris[i][0]; //Coordenada de la mejor posicion de X
		matris[i][3] = matris[i][1]; //Coordenada de la mejor posicion de Y

		//Inicializacion de parametros de velocidad de las particulas 
		matris[i][4] = numero_aleatorio(rango_velocidad);
		matris[i][5] = numero_aleatorio(rango_velocidad);
	}

	//Iniciar el valor de G con los valores anteriormente declarados
	for (int i = 0; i < fila; ++i){
		double evaluacion = calcular_funcion(matris[i][0],matris[i][1]);
		printf("La evaluacion para %d dio: %f\n",i, evaluacion );
		if (evaluacion < menor_global){
			menor_global = evaluacion;
			menor_X_global = matris[i][0];
			menor_Y_global = matris[i][1];
		}
	}

	imprimir();
	return 0;
}