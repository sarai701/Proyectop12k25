#include "envios.h"
#include "pedidos.h"
#include "transportistas.h"
#include "almacen.h"
#include "clientes.h"
#include "bitacora.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

// Variables externas
extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// ----------- Funciones privadas estáticas ------------

vector<Envio> Envios::cargarEnviosDesdeArchivo() {
    ifstream archivo("envios.dat", ios::binary);  // CAMBIO: unificado el nombre del archivo
    vector<Envio> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Envio envio;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        envio.idPedido.resize(size);
        archivo.read(&envio.idPedido[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        envio.idTransportista.resize(size);
        archivo.read(&envio.idTransportista[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        envio.estado.resize(size);
        archivo.read(&envio.estado[0], size);

        lista.push_back(envio);
    }
    archivo.close();
    return lista;
}

void Envios::guardarEnviosEnArchivo(const vector<Envio>& envios) {
    ofstream archivo("envios.dat", ios::binary | ios::trunc);  // CAMBIO: nombre unificado
    for (const auto& envio : envios) {
        size_t size;

        size = envio.idPedido.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(envio.idPedido.c_str(), size);

        size = envio.idTransportista.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(envio.idTransportista.c_str(), size);

        size = envio.estado.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(envio.estado.c_str(), size);
    }
    archivo.close();
}

// ----------- Funciones auxiliares ------------

vector<Transportistas> cargarTransportistasDisponibles() {
    vector<Transportistas> todos;
    Transportistas::cargarDesdeArchivo(todos);
    vector<Transportistas> disponibles;
    for (const auto& t : todos) {
        if (t.disponibilidad == "disponible")
            disponibles.push_back(t);
    }
    return disponibles;
}

vector<Pedidos> cargarPedidos() {
    Pedidos::cargarDesdeArchivoBin(Pedidos::listaPedidos);  // Asegura carga
    return Pedidos::listaPedidos;
}

void guardarPedidos(const vector<Pedidos>& pedidos) {
    Pedidos::listaPedidos = pedidos;
    Pedidos::guardarEnArchivoBin(Pedidos::listaPedidos);
}

// ----------- Métodos de Envios ------------

void Envios::crearEnvioInteractivo() {
    system("cls");
    cout << "\n\t=== CREAR NUEVO ENVÍO ===\n";

    vector<Transportistas> transportistas = cargarTransportistasDisponibles();
    vector<Pedidos> pedidos = cargarPedidos();

    if (transportistas.empty()) {
        cout << "\n\tNo hay transportistas disponibles.\n";
        return;
    }

    vector<Pedidos> procesados;
    for (const auto& p : pedidos) {
        if (p.getEstado() == "procesado") {
            procesados.push_back(p);
        }
    }

    if (procesados.empty()) {
        cout << "\n\tNo hay pedidos en estado 'procesado'.\n";
        return;
    }

    // Mostrar pedidos
    cout << "\nPedidos disponibles para envío:\n";
    cout << "------------------------------------------------\n";
    cout << "ID Pedido\tCliente\t\tEstado\n";
    cout << "------------------------------------------------\n";
    for (const auto& p : procesados) {
        cout << p.getId() << "\t\t" << p.getIdCliente() << "\t\t" << p.getEstado() << "\n";
    }
    cout << "------------------------------------------------\n";

    string idPedido;
    cout << "Ingrese ID del pedido para envío (0 para salir): ";
    cin >> idPedido;
    if (idPedido == "0") return;

    auto itPedido = find_if(procesados.begin(), procesados.end(), [&](const Pedidos& p) {
        return p.getId() == idPedido;
    });

    if (itPedido == procesados.end()) {
        cout << "\n\tPedido no encontrado o no está en estado 'procesado'.\n";
        return;
    }

    // Mostrar transportistas disponibles
    cout << "\nTransportistas disponibles:\n";
    cout << "----------------------------------------------\n";
    cout << "Índice\tID Transportista\tNombre\n";
    cout << "----------------------------------------------\n";
    for (size_t i = 0; i < transportistas.size(); i++) {
        cout << i + 1 << "\t" << transportistas[i].id << "\t\t" << transportistas[i].nombre << "\n";
    }
    cout << "----------------------------------------------\n";

    int opcionTransportista;
    cout << "Seleccione número del transportista a asignar (0 para salir): ";
    cin >> opcionTransportista;
    if (opcionTransportista == 0) return;
    if (opcionTransportista < 1 || opcionTransportista > (int)transportistas.size()) {
        cout << "\n\tOpción de transportista inválida.\n";
        return;
    }

    Transportistas seleccionado = transportistas[opcionTransportista - 1];

    // Crear nuevo envío
    Envio nuevo;
    nuevo.idPedido = idPedido;
    nuevo.idTransportista = seleccionado.id;
    nuevo.estado = "en camino";

    vector<Envio> envios = cargarEnviosDesdeArchivo();
    envios.push_back(nuevo);
    guardarEnviosEnArchivo(envios);

    for (auto& p : pedidos) {
        if (p.getId() == idPedido) {
            p.setEstado("enviado");
        }
    }
    guardarPedidos(pedidos);

    auditoria.registrar(usuarioRegistrado.getNombre(), "ENVIOS", "Creado envío para pedido " + idPedido + " con transportista " + seleccionado.id);
    cout << "\n\tEnvío creado exitosamente.\n";
}

void Envios::crearEnvio(const std::string& idPedido, const std::vector<Transportistas>& transportistasDisponibles) {
    if (transportistasDisponibles.empty()) {
        std::cout << "No hay transportistas disponibles." << std::endl;
        return;
    }

    Envio nuevo;
    nuevo.idPedido = idPedido;
    nuevo.idTransportista = transportistasDisponibles.front().id;
    nuevo.estado = "en camino";

    std::vector<Envio> envios = cargarEnviosDesdeArchivo();
    envios.push_back(nuevo);
    guardarEnviosEnArchivo(envios);

    std::cout << "Envio creado con éxito para pedido: " << idPedido << std::endl;
}

void Envios::mostrarEnvios() {
    vector<Envio> envios = cargarEnviosDesdeArchivo();
    if (envios.empty()) {
        cout << "\n\tNo hay envíos registrados.\n";
        return;
    }

    cout << "\n\t===== LISTA DE ENVÍOS =====\n";
    for (const auto& envio : envios) {
        cout << "\nPedido ID: " << envio.idPedido
             << "\nTransportista ID: " << envio.idTransportista
             << "\nEstado: " << envio.estado << "\n--------------------------\n";
    }
}

void mostrarTablaEnvios(const vector<Envio>& envios) {
    cout << "\n=============================================================\n";
    cout << "| ID Pedido | ID Cliente | ID Transportista |  Estado       |\n";
    cout << "=============================================================\n";

    for (const auto& envio : envios) {
        cout << "| "
             << setw(9) << envio.idPedido << " | "
             << setw(10) << envio.idCliente << " | "
             << setw(16) << envio.idTransportista << " | "
             << setw(13) << envio.estado << " |\n";
    }

    cout << "=============================================================\n";
}

void modificarEstadoEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    if (envios.empty()) {
        cout << "No hay envíos registrados.\n";
        system("pause");
        return;
    }

    mostrarTablaEnvios(envios);

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer antes de getline

    std::string idPedido;
    cout << "Ingrese ID del pedido a modificar (0 para salir): ";
    getline(cin, idPedido);

    if (idPedido == "0") return;

    bool encontrado = false;
    for (auto& envio : envios) {
        if (envio.idPedido == idPedido) {
            cout << "Estado actual: " << envio.estado << "\n";
            cout << "Ingrese nuevo estado (en camino, entregado): ";
            getline(cin, envio.estado);
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        Envios::guardarEnviosEnArchivo(envios);
        cout << "Estado modificado exitosamente.\n";
    } else {
        cout << "No se encontró el envío con ID de pedido: " << idPedido << "\n";
    }

    system("pause");
}

void cancelarEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    if (envios.empty()) {
        cout << "No hay envíos registrados.\n";
        system("pause");
        return;
    }

    mostrarTablaEnvios(envios);

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer antes de getline

    std::string idPedido;
    cout << "Ingrese ID del pedido a cancelar (0 para salir): ";
    getline(cin, idPedido);

    if (idPedido == "0") return;

    bool encontrado = false;
    for (auto& envio : envios) {
        if (envio.idPedido == idPedido) {
            if (envio.estado == "entregado") {
                cout << "No se puede cancelar un envío ya entregado.\n";
                system("pause");
                return;
            }
            if (envio.estado != "en camino") {
                cout << "No se puede cancelar el envío en estado actual: " << envio.estado << "\n";
                system("pause");
                return;
            }
            envio.estado = "Cancelado";
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        Envios::guardarEnviosEnArchivo(envios);
        cout << "Envío cancelado exitosamente.\n";
    } else {
        cout << "No se encontró el envío con ID de pedido: " << idPedido << "\n";
    }

    system("pause");
}


void eliminarEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    if (envios.empty()) {
        cout << "No hay envíos registrados.\n";
        system("pause");
        return;
    }

    mostrarTablaEnvios(envios);

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer antes de getline

    std::string idPedido;
    cout << "Ingrese ID del pedido a eliminar (0 para salir): ";
    getline(cin, idPedido);

    if (idPedido == "0") return;

    auto it = std::remove_if(envios.begin(), envios.end(), [idPedido](const Envio& envio) {
        return envio.idPedido == idPedido;
    });

    if (it != envios.end()) {
        envios.erase(it, envios.end());
        Envios::guardarEnviosEnArchivo(envios);
        cout << "Envío eliminado exitosamente.\n";
    } else {
        cout << "No se encontró el envío con ID de pedido: " << idPedido << "\n";
    }

    system("pause");
}


void Envios::gestionEnvios() {
    int opcion = 0;
    do {
        system("cls");
        cout << "\t\t========================================\n";
        cout << "\t\t|     SISTEMA DE GESTIÓN DE ENVÍOS      |\n";
        cout << "\t\t========================================\n";
        cout << "\t\t 1. Crear nuevo envío\n";
        cout << "\t\t 2. Consultar envíos\n";
        cout << "\t\t 3. Modificar estado de envío\n";
        cout << "\t\t 4. Cancelar envío\n";
        cout << "\t\t 5. Eliminar envío\n";
        cout << "\t\t 6. Volver al menú principal\n";
        cout << "\t\t========================================\n";
        cout << "\t\t Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            crearEnvioInteractivo();
            system("pause");
            break;
        case 2:
            mostrarEnvios();
            system("pause");
            break;
        case 3:
            modificarEstadoEnvio();
            system("pause");
            break;
        case 4:
            cancelarEnvio();
            system("pause");
            break;
        case 5:
            eliminarEnvio();
            system("pause");
            break;
        case 6:
            cout << "\n\tSaliendo al menú principal...\n";
            break;
        default:
            cout << "\n\tOpción inválida.\n";
            system("pause");
            break;
        }
    } while (opcion != 6);
}
