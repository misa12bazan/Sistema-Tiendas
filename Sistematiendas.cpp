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

void registrarTienda() {

    int op;

    if (totalTiendas >= MAX_TIENDAS) {
        cout << "\nLímite de tiendas alcanzado.\n";
        return;
    }

    Tienda t;
    cout << "\nIngrese ID de la tienda: ";
    cin >> t.id;

    if (buscarTiendaPorID(t.id) != -1) {
        cout << "ID ya registrado.\n";
        return;
    }

    cin.ignore();
    cout << "Ingrese Nombre de la tienda: ";
    getline(cin, t.nombre);

    cout << "Categoria de Productos: ";
    getline(cin, t.categoria);

    do {
        cout << "Ventas mensuales: ";
        cin >> t.ventasMensuales;

        if (t.ventasMensuales <= 0) {
            cout << "El monto de venta debe ser positivo.\n";
        }
    } while (t.ventasMensuales <= 0);

    cout << "Servicios adicionales:\n";

    do {
        cout << "¿Mantenimiento? (1 = sí, 0 = no): ";
        cin >> t.mantenimiento;

        if (t.mantenimiento != 0 && t.mantenimiento != 1) {
            cout << "Opción inválida. Ingrese 1 o 0.\n";
        }
    } while (t.mantenimiento != 0 && t.mantenimiento != 1);

    do {
        cout << "¿Publicidad? (1 = sí, 0 = no): ";
        cin >> t.publicidad;

        if (t.publicidad != 0 && t.publicidad != 1) {
            cout << "Opción inválida. Ingrese 1 o 0.\n";
        }
    } while (t.publicidad != 0 && t.publicidad != 1);

    tiendas[totalTiendas++] = t;

    cout << "\nTienda registrada con exito.\n";
}
