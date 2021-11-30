// Linea de comando para la compilacion: g++ Examen2.cc Hormiga.cc -o Examen
#include "Hormiga.h"
#include "vector"
#include <iostream>
#include <fstream>
#include <algorithm>

#include <string.h>



using namespace std;
//Variables del problema 
vector<Hormiga> hormigas;
vector<vector<int>> grafo;
vector<vector<double>> cantidad_feromona;
vector<int> mejor_solucion;
int cantidad_nodos_mejor_solucion = 30;
int hormiga_mejor_camino ;

int cantidad_hormigas = 5;
int cantidad_iterciones = 10000;
int seed(559642);
double factor_evaporacion = 0.02;
double feromona = 0.04;



int main(int argc, char const *argv[])
{
	srand(seed); 
	//Cambio de tamanio del grafo del problema y de la representación de las feromonas
	grafo.resize(30);
	cantidad_feromona.resize(30);

	//Leer el archivo e inicializar el grafo 
	ifstream archivo ("edges.txt");
	string hilera;
	if (archivo.is_open())
	{
		while(archivo)
		{
			getline(archivo, hilera);
			if(hilera.size() == 0)
			{
				break;
			}
			else
			{
				
				string primerNodo = hilera.substr(0,2);
				string segundoNodo = hilera.substr(2);
				
				//Rellenar el grafo
				//llena el primer nodo con el vecino 
				int nodo1 = std::stoi(primerNodo);
				int nodo2 = std::stoi(segundoNodo);
				vector<int>::iterator it = find(grafo[nodo1].begin(),grafo[nodo1].end(), nodo2);
				if(it == grafo[nodo1].end())
				{
					grafo[nodo1].push_back(nodo2);
					//Ponemos una cantidad incial de feromonas en el camino i,j
					cantidad_feromona[nodo1].push_back(0.1);
				}
				
				//llena el segundo nodo con el vecino
				it = find(grafo[nodo2].begin(),grafo[nodo2].end(), nodo1);
				if(it == grafo[nodo2].end())
				{
					grafo[nodo2].push_back(nodo1);
					//Ponemos una cantidad incial de feromonas en el camino i,j
					cantidad_feromona[nodo2].push_back(0.1);
				}
				
			}
		}
	}

	//PRUEBA: Impresion del contenido del grafo
	/*
	for (int i = 0; i < grafo.size(); ++i)
	{
		printf("El nodo %d tiene de vecino a:\n",i );
		for (int j = 0; j < grafo[i].size(); ++j)
		{
			printf("%d, cantidad de feromonas: %f\n", grafo[i][j], cantidad_feromona[i][j]);
		}
		printf("----------------------------------\n");
	}
	*/




	// Creacion de hormigas
	for (int i = 0; i < cantidad_hormigas; ++i)
	{
		Hormiga nueva;
		nueva.setNodo(0);
		hormigas.push_back(nueva);	
	}
	


	//PRUEBA: Impresion del contenido del arreglo de hormigas asi con el valor inicial de cada hormiga
	/*
	for (int i = 0; i < hormigas.size(); ++i)
	{
		printf("Hola mundo soy la hormiga %d, y este es mi camino a la comida:\n", i);
		hormigas[i].imprimir();
		printf("-----------------------\n");
	}
	*/


	//ciclo principal 
	int iteraciones = 0;
	while(iteraciones < cantidad_iterciones){
		printf("Iteracion: %d \n",iteraciones );
		//Ciclo interno de movimiento de las hormigas 
		for (int i = 0; i < hormigas.size(); ++i)
		{	
			int nodo_actual = hormigas[i].getUltimoNodo();
			//Revisar si la hormiga se regresa o va de camino a la comida
			if(hormigas[i].getRetroceso() == 0)
			{	
				//printf("Soy la hormiga %d y voy buscando la comida\n",i );
				//Decidir el movimiento de las hormigas 
				
				double seleccion_camino = (double)rand() / (double)RAND_MAX;
				vector<int> posibles_caminos;

				for (int j = 0; j < grafo[nodo_actual].size(); ++j)
				{
					//Recorremos los vecinos del nodo actual para decidir a cual ir
					if(seleccion_camino <= cantidad_feromona[nodo_actual][j])
					{
						//El camino al vecino j tiene suficiente feromonas para ser considerado
						posibles_caminos.push_back(j);
					}
				}

				int indice_escogido ;
				if(posibles_caminos.size() != 0)
				{
					//Se escoge un vecino de los que tenga mayor valor de manera aleatoria.
					indice_escogido = rand() % ( posibles_caminos.size() );
					//printf("Los caminos eran distintos  entonces desde el nodo: %d, escogi irmea al %d\n", nodo_actual, grafo[nodo_actual][indice_escogido]);

				}
				else
				{ 
					indice_escogido = rand() % ( grafo[nodo_actual].size() );
					//printf("Los caminos eran iguales entonces desde el nodo: %d, escogi irmea al %d\n", nodo_actual, grafo[nodo_actual][indice_escogido]);
				}

				int siguiente_nodo = grafo[nodo_actual][indice_escogido];
				hormigas[i].setNodo(siguiente_nodo);

				//Depositar feromonas en el camino usado en ambas entradas del grafo
				cantidad_feromona[nodo_actual][indice_escogido] = cantidad_feromona[nodo_actual][indice_escogido] + 0.03;
				
				for (int k = 0; k < grafo[siguiente_nodo].size(); ++k)
				{
					if(grafo[siguiente_nodo][k] == nodo_actual)
					{
						cantidad_feromona[siguiente_nodo][k] = cantidad_feromona[siguiente_nodo][k] + 0.03;
					}
				}


				//Revisar si se llego a la comida 
				if (hormigas[i].getUltimoNodo() == 1)
				{
					printf("Soy la hormiga %d y llegue a la comida:\n", i);
					//La hormiga llego al final 
					hormigas[i].imprimir();
					
					if(cantidad_nodos_mejor_solucion > hormigas[i].getCantidadNodosVisitados())
					{
						// Encontramos una mejor solucion.
						cantidad_nodos_mejor_solucion = hormigas[i].getCantidadNodosVisitados();
						mejor_solucion = hormigas[i].getCamino();
						hormiga_mejor_camino = i;
					}
					
					hormigas[i].setRetroceso(1);
				}
			}
			else
			{
				//La hormiga va de regreso
				//printf("Hola soy la hormiga %d y voy para atras:\n",i);
				if(nodo_actual != 0)
				{	
					//Eliminamos del camino el ultimo(actual)
					hormigas[i].eliminarUltimo();
					int nodo_anterior = hormigas[i].getUltimoNodo();// ya deberia de haber cambiado
					//Depositar feromonas.
					for (int k = 0; k < grafo[nodo_actual].size(); ++k)
					{
						if(grafo[nodo_actual][k] == nodo_anterior)
						{
							cantidad_feromona[nodo_actual][k] = cantidad_feromona[nodo_actual][k] + 0.03;
						}
					}
					for (int k = 0; k < grafo[nodo_anterior].size(); ++k)
					{
						if(grafo[nodo_anterior][k] == nodo_actual)
						{
							cantidad_feromona[nodo_anterior][k] = cantidad_feromona[nodo_anterior][k] + 0.03;
						}
					}

				}
				else
				{
					//La hormiga llego al inicio y ha de regresar a buscar comida.
					hormigas[i].setRetroceso(0);
				}

			}
		}

		//Disminuir Feromonas
		for (int i = 0; i < grafo.size(); ++i)
		{
			for (int j = 0; j < grafo[i].size(); ++j)
			{
				//Si se realizan la evaporación solo con restas podria dar un valor negativo afectando el programa, el minimo sera 0
				if((cantidad_feromona[i][j] - factor_evaporacion) < 0){
					cantidad_feromona[i][j] = 0;
				}else{
					cantidad_feromona[i][j] = cantidad_feromona[i][j] - factor_evaporacion;
				}
			}
		}
		printf("--------------------------------\n");
		iteraciones++;
	}

	printf("La el mejor camino fue encontrado por la hormiga: %d y es el siguiente:\n", hormiga_mejor_camino );
	for (int i = 0; i < mejor_solucion.size(); ++i)
	{
		printf("Nodo: %d\n",mejor_solucion[i] );
	}


	//PRUEBA: Impresion del contenido del arreglo de hormigas 
	/*
	for (int i = 0; i < hormigas.size(); ++i)
	{
		printf("Hola mundo soy la hormiga %d, y este es mi camino a la comida:\n", i);
		hormigas[i].imprimir();
		printf("-----------------------\n");
	}
	*/


	//PRUEBA: Impresion del contenido del grafo
	/*
	for (int i = 0; i < grafo.size(); ++i)
	{
		printf("El nodo %d tiene de vecino a:\n",i );
		for (int j = 0; j < grafo[i].size(); ++j)
		{
			printf("%d, cantidad de feromonas: %f\n", grafo[i][j], cantidad_feromona[i][j]);
		}
		printf("----------------------------------\n");
	}
	*/


	
	return 0;
}