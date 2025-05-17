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

using namespace std;

// Variables externas (declaradas en otro lado)
extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// ----------- Funciones privadas estáticas ------------

vector<Envio> Envios::cargarEnviosDesdeArchivo() {
    ifstream archivo("envios.bin", ios::binary);
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
    ofstream archivo("envios.dat", ios::binary | ios::trunc);
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

// ----------- Funciones auxiliares fuera de la clase ------------

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
    vector<Pedidos> pedidos;
    // Accede a la lista estática de pedidos
    pedidos = Pedidos::listaPedidos;
    return pedidos;
}

void guardarPedidos(const vector<Pedidos>& pedidos) {
    // Actualiza la lista estática y guarda
    Pedidos::listaPedidos = pedidos;
    Pedidos::guardarEnArchivoBin(Pedidos::listaPedidos);
}
// ----------- Métodos de la clase Envios ------------

void Envios::crearEnvioInteractivo() {
    system("cls");
    cout << "\n\t=== CREAR NUEVO ENVÍO ===\n";

    vector<Transportistas> transportistas = cargarTransportistasDisponibles();
    vector<Pedidos> pedidos = cargarPedidos();

    if (transportistas.empty()) {
        cout << "\n\tNo hay transportistas disponibles.\n";
        return;
    }

    if (pedidos.empty()) {
        cout << "\n\tNo hay pedidos registrados.\n";
        return;
    }

    // Mostrar tabla de pedidos
    cout << "\nPedidos disponibles:\n";
    cout << "------------------------------------------------\n";
    cout << "ID Pedido\tCliente\t\tEstado\n";
    cout << "------------------------------------------------\n";
    for (const auto& p : pedidos) {
        cout << p.getId() << "\t\t" << p.getIdCliente() << "\t\t" << p.getEstado() << "\n";
    }
    cout << "------------------------------------------------\n";

    string idPedido;
    cout << "Ingrese ID del pedido para envío: ";
    cin >> idPedido;

    auto itPedido = find_if(pedidos.begin(), pedidos.end(), [&](const Pedidos& p) {
        return p.getId() == idPedido;
    });

    if (itPedido == pedidos.end()) {
        cout << "\n\tPedido no encontrado.\n";
        return;
    }

    if (itPedido->getEstado() != "procesado") {
        cout << "\n\tEl pedido no está en estado 'procesado'.\n";
        return;
    }

    // Mostrar transportistas disponibles para elegir
    cout << "\nTransportistas disponibles:\n";
    cout << "----------------------------------------------\n";
    cout << "Índice\tID Transportista\tNombre\n";
    cout << "----------------------------------------------\n";
    for (size_t i = 0; i < transportistas.size(); i++) {
        cout << i + 1 << "\t" << transportistas[i].id << "\t\t" << transportistas[i].nombre << "\n";
    }
    cout << "----------------------------------------------\n";

    int opcionTransportista;
    cout << "Seleccione número del transportista a asignar: ";
    cin >> opcionTransportista;
    if (opcionTransportista < 1 || opcionTransportista >(int)transportistas.size()) {
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

    itPedido->setEstado("enviado");
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

void modificarEstadoEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();
    string id;
    cout << "Ingrese ID del pedido a modificar: ";
    cin >> id;

    auto it = find_if(envios.begin(), envios.end(), [&](const Envio& e) {
        return e.idPedido == id;
    });

    if (it == envios.end()) {
        cout << "\n\tEnvío no encontrado.\n";
        return;
    }

    if (it->estado != "en camino") {
        cout << "\n\tSolo se puede modificar si está 'en camino'.\n";
        return;
    }

    cout << "\nNuevo estado (entregado/demorado/devuelto): ";
    string nuevoEstado;
    cin >> nuevoEstado;

    if (nuevoEstado != "entregado" && nuevoEstado != "demorado" && nuevoEstado != "devuelto") {
        cout << "\n\tEstado inválido.\n";
        return;
    }

    it->estado = nuevoEstado;
    Envios::guardarEnviosEnArchivo(envios);
    cout << "\n\tEstado actualizado correctamente.\n";
}

void cancelarEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();
    string id;
    cout << "Ingrese ID del envío a cancelar: ";
    cin >> id;

    auto it = find_if(envios.begin(), envios.end(), [&](const Envio& e) {
        return e.idPedido == id;
    });

    if (it == envios.end()) {
        cout << "\n\tEnvío no encontrado.\n";
        return;
    }

    if (it->estado == "entregado") {
        cout << "\n\tNo se puede cancelar un envío entregado.\n";
        return;
    }

    it->estado = "cancelado";
    Envios::guardarEnviosEnArchivo(envios);
    cout << "\n\tEnvío cancelado correctamente.\n";
}

void eliminarEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();
    string id;
    cout << "Ingrese ID del envío a eliminar: ";
    cin >> id;

    auto it = find_if(envios.begin(), envios.end(), [&](const Envio& e) {
        return e.idPedido == id;
    });

    if (it == envios.end()) {
        cout << "\n\tEnvío no encontrado.\n";
        return;
    }

    char confirm;
    cout << "¿Confirmar eliminación? (s/n): ";
    cin >> confirm;

    if (confirm == 's' || confirm == 'S') {
        envios.erase(it);
        Envios::guardarEnviosEnArchivo(envios);
        cout << "\n\tEnvío eliminado exitosamente.\n";
    } else {
        cout << "\n\tOperación cancelada.\n";
    }
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
