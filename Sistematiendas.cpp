#include <iostream>
#include <string>
using namespace std;

const int MAX_TIENDAS = 100;

struct Tienda {
    int id;
    string nombre;
    string categoria;
    float ventasMensuales;
    bool mantenimiento;
    bool publicidad;
    float alquiler;
};

Tienda tiendas[MAX_TIENDAS];
int totalTiendas = 0;

int buscarTiendaPorID(int id) {
    for (int i = 0; i < totalTiendas; ++i) {
        if (tiendas[i].id == id) return i;
    }
    return -1;
}
