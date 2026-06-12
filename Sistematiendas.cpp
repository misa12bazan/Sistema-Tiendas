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

// ================= REGISTRO =================

void registrarTienda(ListaTiendas &lista, ColaMantenimiento &cola, PilaHistorial &historial) {
    Tienda t;
    int cantidad, i;

    cout << "\n===== REGISTRAR TIENDAS =====\n";
    cout << "Cantidad actual de tiendas registradas: " << lista.obtenerCantidad() << endl;
    cout << "Limite maximo de tiendas: " << MAX_TIENDAS << endl;

    if (lista.obtenerCantidad() >= MAX_TIENDAS) {
        cout << "\nYa se alcanzo el limite maximo de tiendas.\n";
        return;
    }

    do {
        cantidad = leerEnteroPositivo("Cuantas tiendas desea registrar: ");

        if (lista.obtenerCantidad() + cantidad > MAX_TIENDAS) {
            cout << "Error: solo puede registrar "
                 << MAX_TIENDAS - lista.obtenerCantidad()
                 << " tienda(s) mas.\n";
        }

    } while (lista.obtenerCantidad() + cantidad > MAX_TIENDAS);

    for (i = 1; i <= cantidad; i++) {
        cout << "\n===== TIENDA " << i << " DE " << cantidad << " =====\n";

        t.id = leerEnteroPositivo("Ingrese ID de la tienda: ");

        if (lista.buscarPorID(t.id) != NULL) {
            cout << "Error: ID ya registrado. Intente nuevamente.\n";
            i--;
        } else {
            cin.ignore();
            cout << "Ingrese nombre de la tienda: ";
            getline(cin, t.nombre);

            cout << "Categoria de productos: ";
            getline(cin, t.categoria);

            t.ventasMensuales = leerEnteroPositivo("Ventas mensuales: ");

            cout << "\nServicios adicionales:\n";

            t.mantenimiento = leerOpcion01("Mantenimiento 1 = Si, 0 = No: ");
            t.publicidad = leerOpcion01("Publicidad 1 = Si, 0 = No: ");

            t.alquiler = 0;

            lista.insertarFinal(t);

            if (t.mantenimiento) {
                cola.encolar(t.id);
            }

            historial.apilar("Se registro la tienda", t.id);

            cout << "\nTienda registrada correctamente.\n";
        }
    }
}

void atenderMantenimiento(ColaMantenimiento &cola, PilaHistorial &historial) {
    int id = cola.desencolar();

    if (id == -1) {
        cout << "\nNo hay solicitudes de mantenimiento pendientes.\n";
        return;
    }

    cout << "\nSe atendio la solicitud de mantenimiento de la tienda ID: " << id << endl;
    historial.apilar("Se atendio mantenimiento de la tienda", id);
}

// ================= MAIN =================

int main() {
    ListaTiendas lista;
    ColaMantenimiento cola;
    PilaHistorial historial;

    int opcion;
    int idActualizado;

    do {
        cout << "\n=========================================\n";
        cout << " SISTEMA DE GESTION DE TIENDAS Y ALQUILERES\n";
        cout << "=========================================\n";
        cout << "1. Registrar Tienda\n";
        cout << "2. Actualizar Tienda\n";
        cout << "3. Buscar Tienda\n";
        cout << "4. Mostrar Todas las Tiendas\n";
        cout << "5. Calcular Alquiler de una Tienda\n";
        cout << "6. Reporte General de Alquileres\n";
        cout << "7. Reporte de Cobros Adicionales\n";
        cout << "8. Calcular Total Recaudado\n";
        cout << "9. Ver Cola de Mantenimiento\n";
        cout << "10. Atender Mantenimiento\n";
        cout << "11. Ver Historial de Acciones\n";
        cout << "12. Desapilar Ultima Accion\n";
        cout << "13. Salir\n";

        opcion = leerEnteroPositivo("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                registrarTienda(lista, cola, historial);
                break;

            case 2:
                idActualizado = lista.actualizar();

                if (idActualizado != -1) {
                    historial.apilar("Se actualizo la tienda", idActualizado);
                }

                break;

            case 3:
                lista.buscar();
                break;

            case 4:
                lista.mostrar();
                break;

            case 5:
                lista.calcularAlquilerDeTienda(historial);
                break;

            case 6:
                lista.reporteAlquileres(historial);
                break;

            case 7:
                lista.reporteCobrosAdicionales(historial);
                break;

            case 8:
                lista.calcularTotalAlquiler(historial);
                break;

            case 9:
                cola.mostrar();
                break;

            case 10:
                atenderMantenimiento(cola, historial);
                break;

            case 11:
                historial.mostrar();
                break;

            case 12:
                historial.desapilar();
                break;

            case 13:
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "\nOpcion no valida.\n";
                break;
        }

    } while (opcion != 13);

    return 0;
}
