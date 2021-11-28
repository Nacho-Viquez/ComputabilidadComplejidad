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


int main(int argc, char const *argv[])
{

	//Cambio de tamanio del grafo
	grafo.resize(30);

	//Leer el archivo 
	ifstream archivo ("edges.txt");
	string hilera;
	if (archivo.is_open()){
		while(archivo){
			getline(archivo, hilera);
			if(hilera.size() == 0)
			{
				break;
			}else{
				cout << hilera <<'\n';
				string primerNodo = hilera.substr(0,2);
				string segundoNodo = hilera.substr(2);
				
				//Rellenar el grafo
				//llena el primer nodo con el vecino 
				int nodo1 = std::stoi(primerNodo);
				
				int nodo2 = std::stoi(segundoNodo);

				vector<int>::iterator it = find(grafo[nodo1].begin(),grafo[nodo1].end(), nodo2);
				if(it == grafo[nodo1].end()){
					grafo[nodo1].push_back(nodo2);
				}
				
				//llena el segundo nodo con el vecino
				it = find(grafo[nodo2].begin(),grafo[nodo2].end(), nodo1);
				if(it == grafo[nodo2].end()){
					grafo[nodo2].push_back(nodo1);
				}
				
			}
		}
	}

	//Impresion del contenido del grafo
	for (int i = 0; i < grafo.size(); ++i)
	{
		printf("El nodo %d tiene de vecino a:\n",i );
		for (int j = 0; j < grafo[i].size(); ++j)
		{
			printf("%d,\n", grafo[i][j]);
		}
		printf("----------------------------------\n");
	}




	// Creacion de hormigas
	for (int i = 0; i < 5; ++i)
	{
		Hormiga nueva;
		hormigas.push_back(nueva);	
	}
	/*
	for (int i = 0; i < hormigas.size(); ++i)
	{
		printf("Soy la hormiga:%d\n", i);
		hormigas[i].imprimir();
		printf("-----------------------\n");
	}
	*/
	
	return 0;
}