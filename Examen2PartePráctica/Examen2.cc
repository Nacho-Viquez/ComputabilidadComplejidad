#include "Hormiga.h"
#include "vector"

int main(int argc, char const *argv[])
{

	//Prueba almacenamiento de hormigas

	std::vector<Hormiga> hormigas;
	for (int i = 0; i < 5; ++i)
	{
		Hormiga nueva;
		hormigas.push_back(nueva);	
	}

	for (int i = 0; i < hormigas.size(); ++i)
	{
		printf("Soy la hormiga:%d\n", i);
		hormigas[i].imprimir();
		printf("-----------------------\n");
	}
	return 0;
}