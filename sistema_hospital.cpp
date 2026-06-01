// ============================================================
//  SISTEMA DE GESTION HOSPITALARIA
//  Asignatura: Estructura de Datos
//  Universidad Continental - Plan 2024
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ============================================================
// === INTEGRANTE 1: Estructuras base y Lista Enlazada      ===
// === (Gestor de Pacientes)                                ===
// ============================================================

// Estructura que representa un paciente
struct Paciente {
    int id;
    string nombre;
    int prioridad;   // 1=urgente, 2=moderado, 3=leve
    string estado;   // "espera", "atencion", "alta"
};

// Nodo para la lista enlazada
struct NodoPaciente {
    Paciente datos;
    NodoPaciente* siguiente;
};

// Lista enlazada de pacientes registrados
struct ListaPacientes {
    NodoPaciente* cabeza;
    int contador;
};

// Inicializar lista
void inicializarLista(ListaPacientes& lista) {
    lista.cabeza = nullptr;
    lista.contador = 0;
}

// Insertar nuevo paciente al final de la lista
void insertarPaciente(ListaPacientes& lista, int id, string nombre, int prioridad) {
    NodoPaciente* nuevo = new NodoPaciente();
    nuevo->datos = {id, nombre, prioridad, "espera"};
    nuevo->siguiente = nullptr;

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoPaciente* actual = lista.cabeza;
        // FOR: recorre la lista hasta llegar al ultimo nodo
        // se usa FOR porque sabemos que hay un fin definido (el nullptr)
        for (; actual->siguiente != nullptr; actual = actual->siguiente);
        actual->siguiente = nuevo;
    }
    lista.contador++;
    cout << ">> Paciente registrado: " << nombre << " (ID: " << id << ")\n";
}

// Eliminar paciente por ID
void eliminarPaciente(ListaPacientes& lista, int id) {
    NodoPaciente* actual = lista.cabeza;
    NodoPaciente* anterior = nullptr;

    // WHILE: recorre la lista porque no sabemos en que posicion esta el ID
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

// Buscar paciente por ID
NodoPaciente* buscarPaciente(ListaPacientes& lista, int id) {
    NodoPaciente* actual = lista.cabeza;
    // WHILE: buscamos sin saber donde esta el elemento
    while (actual != nullptr) {
        if (actual->datos.id == id)
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

// Modificar prioridad de un paciente
void modificarPrioridad(ListaPacientes& lista, int id, int nuevaPrioridad) {
    NodoPaciente* nodo = buscarPaciente(lista, id);
    // IF_ELSE: verificamos si el paciente existe antes de modificar
    if (nodo != nullptr) {
        nodo->datos.prioridad = nuevaPrioridad;
        cout << ">> Prioridad actualizada para ID " << id << ": " << nuevaPrioridad << "\n";
    } else {
        cout << ">> No se encontro el paciente con ID " << id << ".\n";
    }
}

// Mostrar todos los pacientes
void mostrarPacientes(ListaPacientes& lista) {
    if (lista.cabeza == nullptr) {
        cout << ">> No hay pacientes registrados.\n";
        return;
    }
    cout << "\n--- LISTA DE PACIENTES ---\n";
    NodoPaciente* actual = lista.cabeza;
    // WHILE: recorremos todos los nodos para mostrarlos
    while (actual != nullptr) {
        cout << "ID: " << actual->datos.id
             << " | Nombre: " << actual->datos.nombre
             << " | Prioridad: " << actual->datos.prioridad
             << " | Estado: " << actual->datos.estado << "\n";
        actual = actual->siguiente;
    }
    cout << "--------------------------\n";
}

