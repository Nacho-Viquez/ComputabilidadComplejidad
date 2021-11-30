# include "Hormiga.h"


Hormiga::Hormiga(){}

Hormiga::~Hormiga(){}

int Hormiga::imprimir(){
	printf("El camino que tome para llegar a la comida fue\n");
	for (int i = 0; i < camino_comida.size(); ++i)
	{
		printf("Nodo: %d \n", camino_comida[i]);
	}
	printf("------Fin de la ruta------\n");
	//printf("El valor del ultimo nodo es: %d\n", getUltimoNodo() );
	return 0;
}

int Hormiga::getUltimoNodo(){
	
	return camino_comida[camino_comida.size()-1] ;
}

int Hormiga::setNodo(int nodo){
	vector<int>::iterator it = find(camino_comida.begin(),camino_comida.end(), nodo);

	if(it != camino_comida.end())
	{
		//El nodo esta ya en el camino, hay un ciclo
		int index = camino_comida.size()-1;
		while(camino_comida[index] != nodo)
		{
			//Eliminamos todos los nodos del camino que formen el ciclo
			camino_comida.pop_back();
			index--;
		}

	}
	else
	{
		//Se incerta el nodo normalemnte
		camino_comida.push_back(nodo);
	}
	return 0;
}

int Hormiga::getRetroceso(){
	return this->retroceso;
}

int Hormiga::setRetroceso(int retro){
	this->retroceso = retro;
	return 0;
}

int Hormiga::getCantidadNodosVisitados(){
	int cantidad_nodos = camino_comida.size();
	return cantidad_nodos;
}

vector<int> Hormiga::getCamino(){

	return camino_comida;
}

int Hormiga::eliminarUltimo(){
	camino_comida.pop_back();
	return 0;
}