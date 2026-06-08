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

NodoPaciente* buscarPaciente(ListaPacientes& lista, int id) {
    NodoPaciente* actual = lista.cabeza;
    while (actual != nullptr) {
        if (actual->datos.id == id)
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool existePaciente(ListaPacientes& lista, int id) {
    return buscarPaciente(lista, id) != nullptr;
}

void insertarPaciente(ListaPacientes& lista, int id, string nombre, int prioridad) {
    if (id <= 0) {
        cout << ">> Error: ID invalido.\n";
        return;
    }
    if (prioridad < 1 || prioridad > 3) {
        cout << ">> Error: Prioridad invalida.\n";
        return;
    }
    if (existePaciente(lista, id)) {
        cout << ">> Error: Ya existe un paciente con el ID " << id << ".\n";
        return;
    }

    NodoPaciente* nuevo = new NodoPaciente();
    nuevo->datos = {id, nombre, prioridad, "espera"};
    nuevo->siguiente = nullptr;

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoPaciente* actual = lista.cabeza;
        while (actual->siguiente != nullptr)
            actual = actual->siguiente;
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

bool estaEnCola(ColaAtencion& cola, int id) {
    NodoCola* actual = cola.frente;
    while (actual != nullptr) {
        if (actual->datos.id == id)
            return true;
        actual = actual->siguiente;
    }
    return false;
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


// ==================
// === INTEGRANTE 3: Pila de Recursos ===

struct NodoPila {
    string recurso;
    int idPaciente;
    NodoPila* siguiente;
};

struct PilaRecursos {
    NodoPila* tope;
    int tamanio;
};

void inicializarPila(PilaRecursos& pila) {
    pila.tope = nullptr;
    pila.tamanio = 0;
}

void asignarRecurso(PilaRecursos& pila, string recurso, int idPaciente) {
    NodoPila* nuevo = new NodoPila();
    nuevo->recurso = recurso;
    nuevo->idPaciente = idPaciente;
    nuevo->siguiente = pila.tope;
    pila.tope = nuevo;
    pila.tamanio++;
    cout << ">> Recurso '" << recurso << "' asignado al paciente ID " << idPaciente << "\n";
}

void liberarRecurso(PilaRecursos& pila) {
    if (pila.tope == nullptr) {
        cout << ">> No hay recursos asignados actualmente.\n";
        return;
    }
    NodoPila* liberado = pila.tope;
    cout << ">> Recurso liberado: '" << liberado->recurso
         << "' (Paciente ID: " << liberado->idPaciente << ")\n";
    pila.tope = pila.tope->siguiente;
    delete liberado;
    pila.tamanio--;
}

void mostrarPila(PilaRecursos& pila) {
    if (pila.tope == nullptr) {
        cout << ">> No hay recursos asignados.\n";
        return;
    }
    cout << "\n--- RECURSOS ASIGNADOS (tope -> base) ---\n";
    NodoPila* actual = pila.tope;
    while (actual != nullptr) {
        cout << "Recurso: " << actual->recurso
             << " | Paciente ID: " << actual->idPaciente << "\n";
        actual = actual->siguiente;
    }
    cout << "-----------------------------------------\n";
}


// ================
// === INTEGRANTE 4: Persistencia ===

void guardarPacientes(ListaPacientes& lista) {
    ofstream archivo("pacientes.txt");
    if (!archivo.is_open()) {
        cout << ">> Error al guardar datos.\n";
        return;
    }
    NodoPaciente* actual = lista.cabeza;
    while (actual != nullptr) {
        archivo << actual->datos.id << ","
                << actual->datos.nombre << ","
                << actual->datos.prioridad << ","
                << actual->datos.estado << "\n";
        actual = actual->siguiente;
    }
    archivo.close();
    cout << ">> Datos guardados en 'pacientes.txt'.\n";
}

void cargarPacientes(ListaPacientes& lista) {
    ifstream archivo("pacientes.txt");
    if (!archivo.is_open()) {
        cout << ">> No se encontro archivo de datos previos.\n";
        return;
    }

    // Vaciar la lista antes de cargar para evitar duplicados
    NodoPaciente* actual = lista.cabeza;
    while (actual != nullptr) {
        NodoPaciente* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    lista.cabeza = nullptr;
    lista.contador = 0;

    string linea;
    while (getline(archivo, linea)) {
        int id, prioridad;
        string nombre, estado;
        int pos1 = linea.find(',');
        int pos2 = linea.find(',', pos1 + 1);
        int pos3 = linea.find(',', pos2 + 1);
        id        = stoi(linea.substr(0, pos1));
        nombre    = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        prioridad = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
        estado    = linea.substr(pos3 + 1);
        insertarPaciente(lista, id, nombre, prioridad);
    }
    archivo.close();
    cout << ">> Datos cargados correctamente.\n";
}


// ================
// === INTEGRANTE 5: Menú Principal ===

void mostrarMenu() {
    cout << "\n========================================\n";
    cout << "   SISTEMA DE GESTION HOSPITALARIA\n";
    cout << "========================================\n";
    cout << "  --- GESTOR DE PACIENTES ---\n";
    cout << "  1. Registrar nuevo paciente\n";
    cout << "  2. Eliminar paciente\n";
    cout << "  3. Buscar paciente por ID\n";
    cout << "  4. Modificar prioridad de paciente\n";
    cout << "  5. Mostrar todos los pacientes\n";
    cout << "  --- COLA DE ATENCION ---\n";
    cout << "  6. Encolar paciente para atencion\n";
    cout << "  7. Atender siguiente paciente (desencolar)\n";
    cout << "  8. Ver cola de atencion actual\n";
    cout << "  --- RECURSOS / CAMAS ---\n";
    cout << "  9. Asignar recurso a paciente\n";
    cout << " 10. Liberar ultimo recurso\n";
    cout << " 11. Ver estado de recursos\n";
    cout << "  --- DATOS ---\n";
    cout << " 12. Guardar datos\n";
    cout << " 13. Cargar datos\n";
    cout << "  0. Salir\n";
    cout << "========================================\n";
    cout << "Opcion: ";
}

int main() {
    ListaPacientes lista;
    ColaAtencion cola;
    PilaRecursos pila;

    inicializarLista(lista);
    inicializarCola(cola);
    inicializarPila(pila);

    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                int id, prioridad;
                string nombre;
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                do {
                    cout << "Prioridad (1=urgente, 2=moderado, 3=leve): ";
                    cin >> prioridad;
                    if (prioridad < 1 || prioridad > 3)
                        cout << ">> Error: Solo se permiten prioridades 1, 2 o 3.\n";
                } while (prioridad < 1 || prioridad > 3);
                insertarPaciente(lista, id, nombre, prioridad);
                break;
            }
            case 2: {
                int id;
                cout << "ID a eliminar: "; cin >> id;
                eliminarPaciente(lista, id);
                break;
            }
            case 3: {
                int id;
                cout << "ID a buscar: "; cin >> id;
                NodoPaciente* resultado = buscarPaciente(lista, id);
                if (resultado != nullptr)
                    cout << ">> Encontrado: " << resultado->datos.nombre
                         << " | Prioridad: " << resultado->datos.prioridad << "\n";
                else
                    cout << ">> Paciente no encontrado.\n";
                break;
            }
            case 4: {
                int id, nuevaPrioridad;
                cout << "ID del paciente: "; cin >> id;
                do {
                    cout << "Nueva prioridad (1-3): ";
                    cin >> nuevaPrioridad;
                    if (nuevaPrioridad < 1 || nuevaPrioridad > 3)
                        cout << ">> Error: Solo se permiten prioridades 1, 2 o 3.\n";
                } while (nuevaPrioridad < 1 || nuevaPrioridad > 3);
                modificarPrioridad(lista, id, nuevaPrioridad);
                break;
            }
            case 5:
                mostrarPacientes(lista);
                break;
            case 6: {
                int id;
                cout << "ID del paciente a encolar: "; cin >> id;
                NodoPaciente* p = buscarPaciente(lista, id);
                if (p != nullptr) {
                    if (estaEnCola(cola, id))
                        cout << ">> Error: El paciente ya se encuentra en la cola.\n";
                    else
                        encolarPaciente(cola, p->datos);
                } else {
                    cout << ">> Paciente no encontrado en la lista.\n";
                }
                break;
            }
            case 7:
                desencolarPaciente(cola);
                break;
            case 8:
                mostrarCola(cola);
                break;
            case 9: {
                string recurso;
                int id;
                cout << "Nombre del recurso (ej: Cama-101): "; getline(cin, recurso);
                cout << "ID del paciente: "; cin >> id;
                asignarRecurso(pila, recurso, id);
                break;
            }
            case 10:
                liberarRecurso(pila);
                break;
            case 11:
                mostrarPila(pila);
                break;
            case 12:
                guardarPacientes(lista);
                break;
            case 13:
                cargarPacientes(lista);
                break;
            case 0:
                break;
            default:
                cout << ">> Opcion invalida.\n";
        }

    } while (opcion != 0);

    cout << ">> Sistema cerrado. Hasta pronto.\n";
    return 0;
}