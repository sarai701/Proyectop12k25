#include "pedidos.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// Códigos únicos para bitácora (3000-3999)
const string COD_CREAR = "3000";
const string COD_CONSULTAR = "3001";
const string COD_MODIFICAR = "3002";
const string COD_CANCELAR = "3003";
const string COD_HISTORIAL = "3004";

struct Pedido {
    string id;
    string cliente;
    string producto;
    int cantidad;
    string fecha;
    string estado;
    string direccion;
    string telefono;
    string notas;
};

vector<Pedido> pedidos;

void cargarPedidos() {
    ifstream archivo("pedidos.txt");
    if (archivo.is_open()) {
        Pedido p;
        while (getline(archivo, p.id, '|')) {
            getline(archivo, p.cliente, '|');
            getline(archivo, p.producto, '|');
            archivo >> p.cantidad;
            archivo.ignore();
            getline(archivo, p.fecha, '|');
            getline(archivo, p.estado, '|');
            getline(archivo, p.direccion, '|');
            getline(archivo, p.telefono, '|');
            getline(archivo, p.notas);
            pedidos.push_back(p);
        }
        archivo.close();
    }
}

void guardarPedidos() {
    ofstream archivo("pedidos.txt");
    for (const auto& p : pedidos) {
        archivo << p.id << "|" << p.cliente << "|" << p.producto << "|"
                << p.cantidad << "|" << p.fecha << "|" << p.estado << "|"
                << p.direccion << "|" << p.telefono << "|" << p.notas << endl;
    }
    archivo.close();
}

string generarIdPedido() {
    srand(time(0));
    return "PED-" + to_string(rand() % 9000 + 1000);
}

string obtenerFechaActual() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
}

void Pedidos::gestionPedidos() {
    cargarPedidos();
    int opcion;
    do {
        system("cls");
        cout << "\n\t\t========================================";
        cout << "\n\t\t|       SISTEMA DE GESTIÓN DE PEDIDOS  |";
        cout << "\n\t\t========================================";
        cout << "\n\t\t| 1. Crear nuevo pedido                |";
        cout << "\n\t\t| 2. Consultar pedidos activos         |";
        cout << "\n\t\t| 3. Modificar pedido                  |";
        cout << "\n\t\t| 4. Cancelar pedido                   |";
        cout << "\n\t\t| 5. Historial completo                |";
        cout << "\n\t\t| 6. Volver al menú principal          |";
        cout << "\n\t\t========================================";
        cout << "\n\t\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: crearPedido(); break;
            case 2: consultarPedidos(); break;
            case 3: modificarPedido(); break;
            case 4: cancelarPedido(); break;
            case 5: verHistorial(); break;
            case 6: guardarPedidos(); break;
            default:
                cout << "\n\t\tOpción inválida!";
                cin.get();
        }
    } while(opcion != 6);
}

void Pedidos::crearPedido() {
    system("cls");
    Pedido nuevo;
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       NUEVO PEDIDO                  |";
    cout << "\n\t\t========================================";

    nuevo.id = generarIdPedido();
    nuevo.fecha = obtenerFechaActual();
    nuevo.estado = "Registrado";

    cout << "\n\t\tDatos del cliente:";
    cout << "\n\t\tNombre completo: ";
    getline(cin, nuevo.cliente);
    cout << "\t\tDirección de entrega: ";
    getline(cin, nuevo.direccion);
    cout << "\t\tTeléfono de contacto: ";
    getline(cin, nuevo.telefono);

    cout << "\n\t\tDetalles del producto:";
    cout << "\n\t\tDescripción del producto: ";
    getline(cin, nuevo.producto);
    cout << "\t\tCantidad: ";
    cin >> nuevo.cantidad;
    cin.ignore();
    cout << "\t\tNotas adicionales: ";
    getline(cin, nuevo.notas);

    pedidos.push_back(nuevo);

    cout << "\n\t\t========================================";
    cout << "\n\t\t| ¡PEDIDO REGISTRADO CON ÉXITO!       |";
    cout << "\n\t\t========================================";
    cout << "\n\t\tNúmero de pedido: " << nuevo.id;
    cout << "\n\t\tFecha: " << nuevo.fecha;
    cout << "\n\t\tEstado: " << nuevo.estado;
    cout << "\n\t\t========================================";

    auditoria.insertar(usuarioRegistrado.getNombre(), COD_CREAR, "PEDIDO-CREADO-" + nuevo.id);
    system("pause");
}

void Pedidos::consultarPedidos() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       PEDIDOS ACTIVOS               |";
    cout << "\n\t\t========================================";

    bool encontrados = false;
    for (const auto& p : pedidos) {
        if (p.estado != "Cancelado" && p.estado != "Entregado") {
            encontrados = true;
            cout << "\n\t\t----------------------------------------";
            cout << "\n\t\tID: " << p.id;
            cout << "\n\t\tCliente: " << p.cliente;
            cout << "\n\t\tProducto: " << p.producto << " x" << p.cantidad;
            cout << "\n\t\tFecha: " << p.fecha;
            cout << "\n\t\tEstado: " << p.estado;
            cout << "\n\t\t----------------------------------------";
        }
    }

    if (!encontrados) {
        cout << "\n\t\tNo hay pedidos activos en este momento.";
    }

    auditoria.insertar(usuarioRegistrado.getNombre(), COD_CONSULTAR, "CONSULTA-PEDIDOS");
    system("pause");
}

void Pedidos::modificarPedido() {
    system("cls");
    string id;
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       MODIFICAR PEDIDO              |";
    cout << "\n\t\t========================================";
    cout << "\n\t\tIngrese el ID del pedido: ";
    getline(cin, id);

    auto it = find_if(pedidos.begin(), pedidos.end(), [&id](const Pedido& p) { return p.id == id; });

    if (it != pedidos.end()) {
        cout << "\n\t\tDatos actuales del pedido " << id << ":";
        cout << "\n\t\t1. Cliente: " << it->cliente;
        cout << "\n\t\t2. Producto: " << it->producto;
        cout << "\n\t\t3. Cantidad: " << it->cantidad;
        cout << "\n\t\t4. Dirección: " << it->direccion;
        cout << "\n\t\t5. Teléfono: " << it->telefono;
        cout << "\n\t\t6. Notas: " << it->notas;
        cout << "\n\t\t----------------------------------------";
        cout << "\n\t\tIngrese el número del campo a modificar (1-6): ";

        int campo;
        cin >> campo;
        cin.ignore();

        switch(campo) {
            case 1:
                cout << "\t\tNuevo nombre del cliente: ";
                getline(cin, it->cliente);
                break;
            case 2:
                cout << "\t\tNuevo producto: ";
                getline(cin, it->producto);
                break;
            case 3:
                cout << "\t\tNueva cantidad: ";
                cin >> it->cantidad;
                cin.ignore();
                break;
            case 4:
                cout << "\t\tNueva dirección: ";
                getline(cin, it->direccion);
                break;
            case 5:
                cout << "\t\tNuevo teléfono: ";
                getline(cin, it->telefono);
                break;
            case 6:
                cout << "\t\tNuevas notas: ";
                getline(cin, it->notas);
                break;
            default:
                cout << "\t\tOpción inválida!";
        }

        cout << "\n\t\t¡Pedido actualizado con éxito!";
        auditoria.insertar(usuarioRegistrado.getNombre(), COD_MODIFICAR, "PEDIDO-MODIFICADO-" + id);
    } else {
        cout << "\n\t\tPedido no encontrado!";
    }

    system("pause");
}

void Pedidos::cancelarPedido() {
    system("cls");
    string id;
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       CANCELAR PEDIDO               |";
    cout << "\n\t\t========================================";
    cout << "\n\t\tIngrese el ID del pedido: ";
    getline(cin, id);

    auto it = find_if(pedidos.begin(), pedidos.end(), [&id](const Pedido& p) { return p.id == id; });

    if (it != pedidos.end()) {
        cout << "\n\t\tMotivo de cancelación: ";
        string motivo;
        getline(cin, motivo);

        it->estado = "Cancelado";
        it->notas += "\nCancelación: " + motivo + " - " + obtenerFechaActual();

        cout << "\n\t\t¡Pedido cancelado con éxito!";
        auditoria.insertar(usuarioRegistrado.getNombre(), COD_CANCELAR, "PEDIDO-CANCELADO-" + id + "-MOTIVO:" + motivo);
    } else {
        cout << "\n\t\tPedido no encontrado!";
    }

    system("pause");
}

void Pedidos::verHistorial() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       HISTORIAL DE PEDIDOS          |";
    cout << "\n\t\t========================================";

    if (pedidos.empty()) {
        cout << "\n\t\tNo hay pedidos registrados.";
    } else {
        for (const auto& p : pedidos) {
            cout << "\n\t\t----------------------------------------";
            cout << "\n\t\tID: " << p.id;
            cout << "\n\t\tCliente: " << p.cliente;
            cout << "\n\t\tProducto: " << p.producto << " x" << p.cantidad;
            cout << "\n\t\tFecha: " << p.fecha;
            cout << "\n\t\tEstado: " << p.estado;
            if (p.estado == "Cancelado") {
                cout << "\n\t\tNotas: " << p.notas.substr(p.notas.find_last_of("\n"));
            }
            cout << "\n\t\t----------------------------------------";
        }
    }

    auditoria.insertar(usuarioRegistrado.getNombre(), COD_HISTORIAL, "HISTORIAL-CONSULTADO");
    system("pause");
}
