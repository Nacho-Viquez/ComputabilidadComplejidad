#include <cstdio>
#include "vector"
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
   private: 
      vector<int> camino_comida;
      int retroceso; // Bandera que indica si la hormiga va hacia la comida o de regreso

};