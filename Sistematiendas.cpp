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
