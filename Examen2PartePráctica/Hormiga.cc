# include "Hormiga.h"


Hormiga::Hormiga(){}

Hormiga::~Hormiga(){}

int Hormiga::imprimir(){
	printf( "Hola mundo soy una hormiga y voy a crear un vector\n");
	
	int valorPrueba = 1;
	for (int i = 0; i < 5; ++i)
	{
		setNodo(valorPrueba);
		valorPrueba++;
	}

	for (int i = 0; i < camino_comida.size(); ++i)
	{
		printf("Hola el valor de la poscion %d es: %d\n",i , camino_comida[i]);
	}

	printf("El valor del ultimo nodo es: %d\n", getUltimoNodo() );
	return 0;
}

int Hormiga::getUltimoNodo(){
	
	return camino_comida[camino_comida.size()-1] ;
}

int Hormiga::setNodo(int nodo){
	camino_comida.push_back(nodo);
	return 0;
}

int Hormiga::getRetroceso(){
	return this->retroceso;
}

int Hormiga::setRetroceso(int retro){
	this->retroceso = retro;
	return 0;
}