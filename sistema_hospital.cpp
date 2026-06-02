// ============================================================
//  SISTEMA DE GESTION HOSPITALARIA
//  Asignatura: Estructura de Datos
//  Universidad Continental - Plan 2024
// ============================================================

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

