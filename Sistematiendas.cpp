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

void actualizarTienda() {
    int id;
    cout << "\nIngrese ID de la tienda a actualizar: ";
    cin >> id;

    int indice = buscarTiendaPorID(id);

    if (indice == -1) {
        cout << "Tienda no encontrada.\n";
        return;
    }

    cout << "\n--- Datos actuales de la tienda ---\n";
    cout << "Nombre: " << tiendas[indice].nombre << endl;
    cout << "Categoría: " << tiendas[indice].categoria << endl;
    cout << "Ventas mensuales: S/. " << tiendas[indice].ventasMensuales << endl;

    cout << "\n--- Actualizar los Datos de la tienda "
         << tiendas[indice].nombre << " ---\n";

    cout << "Nueva categoria: ";
    cin.ignore();
    getline(cin, tiendas[indice].categoria);

    do {
        cout << "Nuevas Ventas mensuales: ";
        cin >> tiendas[indice].ventasMensuales;

        if (tiendas[indice].ventasMensuales < 0) {
            cout << "El monto de venta debe ser positivo.\n";
        }

    } while (tiendas[indice].ventasMensuales < 0);

    cout << "Actualizado correctamente.\n";
}

void buscarTienda() {
    int id;

    cout << "\nIngrese ID de la tienda: ";
    cin >> id;

    int indice = buscarTiendaPorID(id);

    if (indice == -1) {
        cout << "Tienda no encontrada.\n";
        return;
    }

    Tienda &t = tiendas[indice];

    cout << "Nombre: " << t.nombre << endl;
    cout << "Categoria: " << t.categoria << endl;
    cout << "Ventas: " << t.ventasMensuales << endl;
}

void mostrarTiendas() {
    for (int i = 0; i < totalTiendas; ++i) {

        Tienda &t = tiendas[i];

        cout << "ID: " << t.id << endl;
        cout << "Nombre: " << t.nombre << endl;
        cout << "Categoria: " << t.categoria << endl;
        cout << "Ventas: " << t.ventasMensuales << endl;
    }
}

float calcularAlquiler(Tienda &t) {
    float alquiler = 1000;

    if (t.mantenimiento) {
        alquiler += 200;
    }

    if (t.publicidad) {
        alquiler += 300;
    }

    if (t.ventasMensuales > 10000) {
        alquiler += t.ventasMensuales * 0.05;
    }

    t.alquiler = alquiler;

    return alquiler;
}

void calcularAlquilerDeTienda() {
    int id;

    cout << "\nIngrese ID de la tienda: ";
    cin >> id;

    int indice = buscarTiendaPorID(id);

    if (indice == -1) {
        cout << "Tienda no encontrada.\n";
        return;
    }

    float alquiler = calcularAlquiler(tiendas[indice]);

    cout << "\n Detalle del alquiler \n";
    cout << "ID: " << tiendas[indice].id << endl;
    cout << "Nombre: " << tiendas[indice].nombre << endl;
    cout << "Categoria: " << tiendas[indice].categoria << endl;
    cout << "Ventas mensuales: S/. " << tiendas[indice].ventasMensuales << endl;
    cout << "Mantenimiento: " << (tiendas[indice].mantenimiento ? "Si" : "No") << endl;
    cout << "Publicidad: " << (tiendas[indice].publicidad ? "Si" : "No") << endl;
    cout << "Alquiler calculado: S/. " << alquiler << endl;
}
void reporteAlquileres() {
    if (totalTiendas == 0) {
        cout << "\nNo hay tiendas registradas para generar el reporte.\n";
        return;
    }
    cout << "\n=========================================\n";
    cout << "       REPORTE GENERAL DE ALQUILERES     \n";
    cout << "=========================================\n";
    for (int i = 0; i < totalTiendas; ++i) {
        calcularAlquiler(tiendas[i]);
        cout << "ID: " << tiendas[i].id 
             << " | Nombre: " << tiendas[i].nombre 
             << " | Alquiler Total: S/. " << tiendas[i].alquiler << endl;
    }
}

void reporteCobrosAdicionales() {
    if (totalTiendas == 0) {
        cout << "\nNo hay tiendas registradas para generar el reporte.\n";
        return;
    }
    cout << "\n=========================================\n";
    cout << "      REPORTE DE COBROS ADICIONALES      \n";
    cout << "=========================================\n";
    for (int i = 0; i < totalTiendas; ++i) {
        float mant = tiendas[i].mantenimiento ? 200 : 0;
        float pub = tiendas[i].publicidad ? 300 : 0;
        float comision = (tiendas[i].ventasMensuales > 10000) ? (tiendas[i].ventasMensuales * 0.05) : 0;
        float totalAdicional = mant + pub + comision;

        cout << "ID: " << tiendas[i].id << " | Tienda: " << tiendas[i].nombre << endl;
        cout << "  - Mantenimiento: S/. " << mant << endl;
        cout << "  - Publicidad: S/. " << pub << endl;
        cout << "  - Comision (5%): S/. " << comision << endl;
        cout << "  - Total Adicionales: S/. " << totalAdicional << endl;
        cout << "-----------------------------------------\n";
    }
}

void calcularTotalAlquiler() {
    if (totalTiendas == 0) {
        cout << "\nNo hay tiendas registradas.\n";
        return;
    }
    float sumaAlquileres = 0;
    for (int i = 0; i < totalTiendas; ++i) {
        sumaAlquileres += calcularAlquiler(tiendas[i]);
    }
    cout << "\n=========================================\n";
    cout << " MONTO TOTAL A RECAUDAR POR ALQUILERES: S/. " << sumaAlquileres << endl;
    cout << "=========================================\n";
}

int main() {
    int opcion;
    do {
        cout << "\n=========================================\n";
        cout << "   MENÚ PRINCIPAL DEL SISTEMA LA TIENDA    \n";
        cout << "=========================================\n";
        cout << "1. Registrar Tienda\n";
        cout << "2. Actualizar Tienda\n";
        cout << "3. Buscar Tienda\n";
        cout << "4. Mostrar Todas las Tiendas\n";
        cout << "5. Calcular Alquiler de una Tienda \n";
        cout << "6. Reporte General de Alquileres \n";
        cout << "7. Reporte de Cobros Adicionales \n";
        cout << "8. Calcular Total Recaudado \n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarTienda(); break;
            case 2: actualizarTienda(); break;
            case 3: buscarTienda(); break;
            case 4: mostrarTiendas(); break;
            case 5: calcularAlquilerDeTienda(); break;
            case 6: reporteAlquileres(); break;
            case 7: reporteCobrosAdicionales(); break;
            case 8: calcularTotalAlquiler(); break;
            case 9: cout << "\nSaliendo del sistema...\n"; break;
            default: cout << "\nOpcion no valida. Intente de nuevo.\n"; break;
        }
    } while (opcion != 9);

    return 0;
}