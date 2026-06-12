#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_TIENDAS = 100;

struct Tienda {
    int id;
    string nombre;
    string categoria;
    int ventasMensuales;
    bool mantenimiento;
    bool publicidad;
    int alquiler;
};

int leerEnteroPositivo(string mensaje) {
    int valor;

    do {
        cout << mensaje;
        cin >> valor;

        if (cin.fail() || valor <= 0) {
            cout << "Error: ingrese un numero entero positivo mayor a 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            valor = -1;
        }

    } while (valor <= 0);

    return valor;
}

int leerOpcion01(string mensaje) {
    int valor;

    do {
        cout << mensaje;
        cin >> valor;

        if (cin.fail() || (valor != 0 && valor != 1)) {
            cout << "Error: ingrese solo 1 para Si o 0 para No.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            valor = -1;
        }

    } while (valor != 0 && valor != 1);

    return valor;
}

// ================= PILA =================

struct NodoPila {
    string accion;
    int idTienda;
    NodoPila* sig;
};

typedef NodoPila* pnodoPila;

class PilaHistorial {
private:
    pnodoPila cima;

public:
    PilaHistorial();
    ~PilaHistorial();
    void apilar(string accion, int idTienda);
    void desapilar();
    void mostrar();
};

PilaHistorial::PilaHistorial() {
    cima = NULL;
}

PilaHistorial::~PilaHistorial() {
    pnodoPila aux;

    while (cima != NULL) {
        aux = cima;
        cima = (*cima).sig;
        delete aux;
    }
}

void PilaHistorial::apilar(string accion, int idTienda) {
    pnodoPila nuevo;

    nuevo = new NodoPila;
    (*nuevo).accion = accion;
    (*nuevo).idTienda = idTienda;
    (*nuevo).sig = cima;
    cima = nuevo;
}

void PilaHistorial::desapilar() {
    pnodoPila aux;

    if (cima == NULL) {
        cout << "\nPila vacia.\n";
    } else {
        aux = cima;
        cima = (*cima).sig;

        cout << "\nAccion eliminada: " << (*aux).accion;
        cout << " | ID tienda: " << (*aux).idTienda << endl;

        delete aux;
    }
}

void PilaHistorial::mostrar() {
    pnodoPila p;

    if (cima == NULL) {
        cout << "\nPila vacia.\n";
    } else {
        p = cima;

        cout << "\n===== HISTORIAL DE ACCIONES =====\n";

        while (p != NULL) {
            cout << "Accion: " << (*p).accion;
            cout << " | ID tienda: " << (*p).idTienda << endl;
            p = (*p).sig;
        }
    }
}

// ================= COLA =================

struct NodoCola {
    int idTienda;
    NodoCola* sig;
};

typedef NodoCola* pnodoCola;

class ColaMantenimiento {
private:
    pnodoCola frente;
    pnodoCola final;

public:
    ColaMantenimiento();
    ~ColaMantenimiento();
    void encolar(int idTienda);
    int desencolar();
    void mostrar();
    bool estaVacia();
};

ColaMantenimiento::ColaMantenimiento() {
    frente = NULL;
    final = NULL;
}

ColaMantenimiento::~ColaMantenimiento() {
    pnodoCola aux;

    while (frente != NULL) {
        aux = frente;
        frente = frente->sig;
        delete aux;
    }

    final = NULL;
}

bool ColaMantenimiento::estaVacia() {
    return frente == NULL;
}

void ColaMantenimiento::encolar(int idTienda) {
    pnodoCola nuevo = new NodoCola;
    nuevo->idTienda = idTienda;
    nuevo->sig = NULL;

    if (frente == NULL) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->sig = nuevo;
        final = nuevo;
    }
}

int ColaMantenimiento::desencolar() {
    if (frente == NULL) {
        return -1;
    }

    pnodoCola aux = frente;
    int id = aux->idTienda;

    frente = frente->sig;

    if (frente == NULL) {
        final = NULL;
    }

    delete aux;
    return id;
}

void ColaMantenimiento::mostrar() {
    if (frente == NULL) {
        cout << "\nNo hay solicitudes de mantenimiento.\n";
        return;
    }

    pnodoCola actual = frente;

    cout << "\n===== COLA DE MANTENIMIENTO =====\n";

    while (actual != NULL) {
        cout << "Tienda ID: " << actual->idTienda << endl;
        actual = actual->sig;
    }
}

// ================= LISTA ENLAZADA =================

struct NodoTienda {
    Tienda dato;
    NodoTienda* sig;
};

typedef NodoTienda* pnodoTienda;

class ListaTiendas {
private:
    pnodoTienda pL;
    int cantTiendas;

public:
    ListaTiendas();
    ~ListaTiendas();
    int obtenerCantidad();
    pnodoTienda buscarPorID(int id);
    void insertarFinal(Tienda t);
    int actualizar();
    void buscar();
    void mostrar();
    int calcularAlquiler(Tienda &t);
    void calcularAlquilerDeTienda(PilaHistorial &historial);
    void reporteAlquileres(PilaHistorial &historial);
    void reporteCobrosAdicionales(PilaHistorial &historial);
    void calcularTotalAlquiler(PilaHistorial &historial);
    bool estaVacia();
};

ListaTiendas::ListaTiendas() {
    pL = NULL;
    cantTiendas = 0;
}

int ListaTiendas::obtenerCantidad() {
    return cantTiendas;
}

ListaTiendas::~ListaTiendas() {
    pnodoTienda p, q;

    p = pL;

    while (p != NULL) {
        q = p->sig;
        delete p;
        p = q;
    }

    pL = NULL;
}

bool ListaTiendas::estaVacia() {
    return pL == NULL;
}

pnodoTienda ListaTiendas::buscarPorID(int id) {
    pnodoTienda actual = pL;

    while (actual != NULL) {
        if (actual->dato.id == id) {
            return actual;
        }

        actual = actual->sig;
    }

    return NULL;
}

void ListaTiendas::insertarFinal(Tienda t) {
    pnodoTienda nuevo = new NodoTienda;
    nuevo->dato = t;
    nuevo->sig = NULL;

    if (pL == NULL) {
        pL = nuevo;
    } else {
        pnodoTienda aux = pL;

        while (aux->sig != NULL) {
            aux = aux->sig;
        }

        aux->sig = nuevo;
    }
}

int ListaTiendas::actualizar() {
    int id = leerEnteroPositivo("\nIngrese ID de la tienda a actualizar: ");

    pnodoTienda tienda = buscarPorID(id);

    if (tienda == NULL) {
        cout << "Tienda no encontrada.\n";
        return -1;
    }

    cout << "\n--- Datos actuales ---\n";
    cout << "Nombre: " << tienda->dato.nombre << endl;
    cout << "Categoria: " << tienda->dato.categoria << endl;
    cout << "Ventas mensuales: S/. " << tienda->dato.ventasMensuales << endl;

    cin.ignore();
    cout << "\nNueva categoria: ";
    getline(cin, tienda->dato.categoria);

    tienda->dato.ventasMensuales = leerEnteroPositivo("Nuevas ventas mensuales: ");
    tienda->dato.mantenimiento = leerOpcion01("Â¿Mantenimiento? 1 = Si, 0 = No: ");
    tienda->dato.publicidad = leerOpcion01("Â¿Publicidad? 1 = Si, 0 = No: ");

    cout << "\nTienda actualizada correctamente.\n";

    return id;
}

void ListaTiendas::buscar() {
    int id = leerEnteroPositivo("\nIngrese ID de la tienda: ");

    pnodoTienda tienda = buscarPorID(id);

    if (tienda == NULL) {
        cout << "Tienda no encontrada.\n";
        return;
    }

    cout << "\n===== DATOS DE LA TIENDA =====\n";
    cout << "ID: " << tienda->dato.id << endl;
    cout << "Nombre: " << tienda->dato.nombre << endl;
    cout << "Categoria: " << tienda->dato.categoria << endl;
    cout << "Ventas mensuales: S/. " << tienda->dato.ventasMensuales << endl;
    cout << "Mantenimiento: " << (tienda->dato.mantenimiento ? "Si" : "No") << endl;
    cout << "Publicidad: " << (tienda->dato.publicidad ? "Si" : "No") << endl;
}

void ListaTiendas::mostrar() {
    if (pL == NULL) {
        cout << "\nNo hay tiendas registradas.\n";
        return;
    }

    pnodoTienda actual = pL;

    cout << "\n===== LISTA DE TIENDAS =====\n";

    while (actual != NULL) {
        cout << "\nID: " << actual->dato.id << endl;
        cout << "Nombre: " << actual->dato.nombre << endl;
        cout << "Categoria: " << actual->dato.categoria << endl;
        cout << "Ventas mensuales: S/. " << actual->dato.ventasMensuales << endl;
        cout << "Mantenimiento: " << (actual->dato.mantenimiento ? "Si" : "No") << endl;
        cout << "Publicidad: " << (actual->dato.publicidad ? "Si" : "No") << endl;

        actual = actual->sig;
    }
}

int ListaTiendas::calcularAlquiler(Tienda &t) {
    int alquiler = 1000;

    if (t.mantenimiento) {
        alquiler += 200;
    }

    if (t.publicidad) {
        alquiler += 300;
    }

    if (t.ventasMensuales > 10000) {
        alquiler += t.ventasMensuales * 5 / 100;
    }

    t.alquiler = alquiler;
    return alquiler;
}

void ListaTiendas::calcularAlquilerDeTienda(PilaHistorial &historial) {
    int id = leerEnteroPositivo("\nIngrese ID de la tienda: ");

    pnodoTienda tienda = buscarPorID(id);

    if (tienda == NULL) {
        cout << "Tienda no encontrada.\n";
        return;
    }

    int alquiler = calcularAlquiler(tienda->dato);

    cout << "\n===== DETALLE DEL ALQUILER =====\n";
    cout << "ID: " << tienda->dato.id << endl;
    cout << "Nombre: " << tienda->dato.nombre << endl;
    cout << "Categoria: " << tienda->dato.categoria << endl;
    cout << "Ventas mensuales: S/. " << tienda->dato.ventasMensuales << endl;
    cout << "Mantenimiento: " << (tienda->dato.mantenimiento ? "Si" : "No") << endl;
    cout << "Publicidad: " << (tienda->dato.publicidad ? "Si" : "No") << endl;
    cout << "Alquiler calculado: S/. " << alquiler << endl;

    historial.apilar("Se calculo alquiler de la tienda", id);
}

void ListaTiendas::reporteAlquileres(PilaHistorial &historial) {
    if (pL == NULL) {
        cout << "\nNo hay tiendas registradas.\n";
        return;
    }

    pnodoTienda actual = pL;

    cout << "\n===== REPORTE GENERAL DE ALQUILERES =====\n";

    while (actual != NULL) {
        calcularAlquiler(actual->dato);

        cout << "ID: " << actual->dato.id
             << " | Nombre: " << actual->dato.nombre
             << " | Alquiler Total: S/. " << actual->dato.alquiler << endl;

        actual = actual->sig;
    }

    historial.apilar("Se genero reporte general de alquileres", 0);
}

void ListaTiendas::reporteCobrosAdicionales(PilaHistorial &historial) {
    if (pL == NULL) {
        cout << "\nNo hay tiendas registradas.\n";
        return;
    }

    pnodoTienda actual = pL;

    cout << "\n===== REPORTE DE COBROS ADICIONALES =====\n";

    while (actual != NULL) {
        int mant = actual->dato.mantenimiento ? 200 : 0;
        int pub = actual->dato.publicidad ? 300 : 0;
        int comision = actual->dato.ventasMensuales > 10000 ? actual->dato.ventasMensuales * 5 / 100 : 0;
        int totalAdicional = mant + pub + comision;

        cout << "\nID: " << actual->dato.id << " | Tienda: " << actual->dato.nombre << endl;
        cout << "Mantenimiento: S/. " << mant << endl;
        cout << "Publicidad: S/. " << pub << endl;
        cout << "Comision 5%: S/. " << comision << endl;
        cout << "Total adicionales: S/. " << totalAdicional << endl;

        actual = actual->sig;
    }

    historial.apilar("Se genero reporte de cobros adicionales", 0);
}

void ListaTiendas::calcularTotalAlquiler(PilaHistorial &historial) {
    if (pL == NULL) {
        cout << "\nNo hay tiendas registradas.\n";
        return;
    }

    pnodoTienda actual = pL;
    int total = 0;

    while (actual != NULL) {
        total += calcularAlquiler(actual->dato);
        actual = actual->sig;
    }

    cout << "\nMonto total a recaudar por alquileres: S/. " << total << endl;

    historial.apilar("Se calculo el total recaudado por alquileres", 0);
}
