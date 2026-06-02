// ============================================================
//  SISTEMA DE GESTION HOSPITALARIA
//  Asignatura: Estructura de Datos
//  Universidad Continental - Plan 2024
// ============================================================



// ========================================
// === INTEGRANTE 1: Cola de Prioridad  ===

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Paciente {
    int id;
    string nombre;
    int prioridad; 
    string estado; 
};

struct NodoPaciente {
    Paciente datos;
    NodoPaciente* siguiente;
};

struct ListaPacientes {
    NodoPaciente* cabeza;
    int contador;
};

void inicializarLista(ListaPacientes& lista) {
    lista.cabeza = nullptr;
    lista.contador = 0;
}

void insertarPaciente(ListaPacientes& lista, int id, string nombre, int prioridad) {
    NodoPaciente* nuevo = new NodoPaciente();
    nuevo->datos = {id, nombre, prioridad, "espera"};
    nuevo->siguiente = nullptr;

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoPaciente* actual = lista.cabeza;
        for (; actual->siguiente != nullptr; actual = actual->siguiente);
        actual->siguiente = nuevo;
    }
    lista.contador++;
    cout << ">> Paciente registrado: " << nombre << " (ID: " << id << ")\n";
}

void eliminarPaciente(ListaPacientes& lista, int id) {
    NodoPaciente* actual = lista.cabeza;
    NodoPaciente* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->datos.id == id) {
            if (anterior == nullptr)
                lista.cabeza = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;
            delete actual;
            lista.contador--;
            cout << ">> Paciente con ID " << id << " eliminado.\n";
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    cout << ">> Paciente con ID " << id << " no encontrado.\n";
}

NodoPaciente* buscarPaciente(ListaPacientes& lista, int id) {
    NodoPaciente* actual = lista.cabeza;
    while (actual != nullptr) {
        if (actual->datos.id == id)
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

void modificarPrioridad(ListaPacientes& lista, int id, int nuevaPrioridad) {
    NodoPaciente* nodo = buscarPaciente(lista, id);
    if (nodo != nullptr) {
        nodo->datos.prioridad = nuevaPrioridad;
        cout << ">> Prioridad actualizada para ID " << id << ": " << nuevaPrioridad << "\n";
    } else {
        cout << ">> No se encontro el paciente con ID " << id << ".\n";
    }
}

void mostrarPacientes(ListaPacientes& lista) {
    if (lista.cabeza == nullptr) {
        cout << ">> No hay pacientes registrados.\n";
        return;
    }
    cout << "\n--- LISTA DE PACIENTES ---\n";
    NodoPaciente* actual = lista.cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->datos.id
             << " | Nombre: " << actual->datos.nombre
             << " | Prioridad: " << actual->datos.prioridad
             << " | Estado: " << actual->datos.estado << "\n";
        actual = actual->siguiente;
    }
    cout << "--------------------------\n";
}


// ========================================
// === INTEGRANTE 2: Cola de Prioridad  ===



struct NodoCola {
    Paciente datos;
    NodoCola* siguiente;
};


struct ColaAtencion {
    NodoCola* frente;
    NodoCola* final;
    int tamanio;
};


void inicializarCola(ColaAtencion& cola) {
    cola.frente = nullptr;
    cola.final = nullptr;
    cola.tamanio = 0;
}


void encolarPaciente(ColaAtencion& cola, Paciente p) {
    NodoCola* nuevo = new NodoCola();
    nuevo->datos = p;
    nuevo->siguiente = nullptr;


    if (cola.frente == nullptr) {
        cola.frente = nuevo;
        cola.final = nuevo;
    } else {
        if (nuevo->datos.prioridad < cola.frente->datos.prioridad) {
            nuevo->siguiente = cola.frente;
            cola.frente = nuevo;
        } else {
            NodoCola* actual = cola.frente;
            while (actual->siguiente != nullptr &&
                   actual->siguiente->datos.prioridad <= nuevo->datos.prioridad) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
            if (nuevo->siguiente == nullptr)
                cola.final = nuevo;
        }
    }
    cola.tamanio++;
    cout << ">> Paciente encolado: " << p.nombre << " (Prioridad: " << p.prioridad << ")\n";
}


void desencolarPaciente(ColaAtencion& cola) {
    if (cola.frente == nullptr) {
        cout << ">> No hay pacientes en cola de atencion.\n";
        return;
    }
    NodoCola* atendido = cola.frente;
    cout << ">> Atendiendo a: " << atendido->datos.nombre
         << " (ID: " << atendido->datos.id << ", Prioridad: " << atendido->datos.prioridad << ")\n";
    cola.frente = cola.frente->siguiente;
    if (cola.frente == nullptr)
        cola.final = nullptr;
    delete atendido;
    cola.tamanio--;
}

void mostrarCola(ColaAtencion& cola) {
    if (cola.frente == nullptr) {
        cout << ">> La cola de atencion esta vacia.\n";
        return;
    }
    cout << "\n--- COLA DE ATENCION (frente -> final) ---\n";
    NodoCola* actual = cola.frente;
    int pos = 1;
    while (actual != nullptr) {
        cout << pos++ << ". " << actual->datos.nombre
             << " | Prioridad: " << actual->datos.prioridad << "\n";
        actual = actual->siguiente;
    }
    cout << "------------------------------------------\n";
}
