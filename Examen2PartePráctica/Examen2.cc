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
vector<vector<int>> cantidad_feromona;
int cantidad_hormigas = 5;



int main(int argc, char const *argv[])
{

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
					cantidad_feromona[nodo1].push_back(0);
				}
				
				//llena el segundo nodo con el vecino
				it = find(grafo[nodo2].begin(),grafo[nodo2].end(), nodo1);
				if(it == grafo[nodo2].end())
				{
					grafo[nodo2].push_back(nodo1);
					//Ponemos una cantidad incial de feromonas en el camino i,j
					cantidad_feromona[nodo2].push_back(0);
				}
				
			}
		}
	}

	//PRUEBA: Impresion del contenido del grafo
	for (int i = 0; i < grafo.size(); ++i)
	{
		printf("El nodo %d tiene de vecino a:\n",i );
		for (int j = 0; j < grafo[i].size(); ++j)
		{
			printf("%d, cantidad de feromonas: %d\n", grafo[i][j], cantidad_feromona[i][j]);
		}
		printf("----------------------------------\n");
	}





	// Creacion de hormigas
	for (int i = 0; i < cantidad_hormigas; ++i)
	{
		Hormiga nueva;
		nueva.setNodo(0);
		hormigas.push_back(nueva);	
	}
	
	//PRUEBA: Impresion del contenido del arreglo de hormigas asi con el valor inicial de cada hormiga
	for (int i = 0; i < hormigas.size(); ++i)
	{
		printf("Hola mundo soy la hormiga %d, y este es mi camino a la comida:\n", i);
		hormigas[i].imprimir();
		printf("-----------------------\n");
	}
	
	
	return 0;
}