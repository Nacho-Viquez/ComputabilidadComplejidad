#include <cstdio>
#include "vector"
#include <algorithm>

using namespace std;

class Hormiga {
   public:
      Hormiga();
      ~Hormiga();
      int imprimir();
      int getUltimoNodo();
      int getRetroceso();
      int setNodo(int nodo);
      int setRetroceso(int retro);
      int getCantidadNodosVisitados();
      vector<int> getCamino();
      int eliminarUltimo();
   private: 
      vector<int> camino_comida;
      int retroceso = 0; // Bandera que indica si la hormiga va hacia la comida o de regreso

};