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
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO ENVIO                        \n";
    cout << "------------------------------------------------------------\n";

    vector<Transportistas> transportistas = cargarTransportistasDisponibles();
    vector<Pedidos> pedidos = cargarPedidos();

    if (transportistas.empty()) {
        cout << "\n\tNo hay transportistas disponibles.\n";
        system("pause");
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
        system("pause");
        return;
    }

    cout << "\nPedidos disponibles para envio:\n";
    cout << "------------------------------------------------\n";
    cout << "ID Pedido\tCliente\t\tEstado\n";
    cout << "------------------------------------------------\n";
    for (const auto& p : procesados) {
        cout << p.getId() << "\t\t" << p.getIdCliente() << "\t\t" << p.getEstado() << "\n";
    }
    cout << "------------------------------------------------\n";

    string idPedido;
    cout << "Ingrese ID del pedido para envio (0 para salir): ";
    cin >> idPedido;
    if (idPedido == "0") {
        system("pause");
        return;
    }

    auto itPedido = find_if(procesados.begin(), procesados.end(), [&](const Pedidos& p) {
        return p.getId() == idPedido;
    });

    if (itPedido == procesados.end()) {
        cout << "\n\tPedido no encontrado o no esta en estado 'procesado'.\n";
        system("pause");
        return;
    }

    cout << "\nTransportistas disponibles:\n";
    cout << "----------------------------------------------\n";
    cout << "Indice\tID Transportista\tNombre\n";
    cout << "----------------------------------------------\n";
    for (size_t i = 0; i < transportistas.size(); i++) {
        cout << i + 1 << "\t" << transportistas[i].id << "\t\t" << transportistas[i].nombre << "\n";
    }
    cout << "----------------------------------------------\n";

    int opcionTransportista;
    cout << "Seleccione numero del transportista a asignar (0 para salir): ";
    cin >> opcionTransportista;
    if (opcionTransportista == 0) {
        system("pause");
        return;
    }
    if (opcionTransportista < 1 || opcionTransportista > (int)transportistas.size()) {
        cout << "\n\tOpcion de transportista invalida.\n";
        system("pause");
        return;
    }

    Transportistas seleccionado = transportistas[opcionTransportista - 1];

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

    auditoria.registrar(usuarioRegistrado.getNombre(), "ENVIOS", "Creado envio para pedido " + idPedido + " con transportista " + seleccionado.id);
    cout << "\n\tEnvio creado exitosamente.\n";

    system("pause");
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
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                     LISTA DE ENVIOS                         \n";
    cout << "------------------------------------------------------------\n";

    vector<Envio> envios = cargarEnviosDesdeArchivo();
    if (envios.empty()) {
        cout << "\n\tNo hay envios registrados.\n";
        system("pause");
        return;
    }

    cout << "------------------------------------------------------------\n";
    cout << "ID Pedido       | ID Transportista | Estado                  \n";
    cout << "------------------------------------------------------------\n";

    for (const auto& envio : envios) {
        cout << setw(15) << left << envio.idPedido << "| "
             << setw(17) << left << envio.idTransportista << "| "
             << setw(23) << left << envio.estado << "\n";
    }
    cout << "------------------------------------------------------------\n";

    system("pause");
}

void mostrarTablaEnvios(const vector<Envio>& envios) {
    cout << "\n-------------------------------------------------------------\n";
    cout << "| ID Pedido | ID Cliente | ID Transportista | Estado        |\n";
    cout << "-------------------------------------------------------------\n";

    for (const auto& envio : envios) {
        cout << "| "
             << setw(9) << envio.idPedido << " | "
             << setw(10) << envio.idCliente << " | "
             << setw(16) << envio.idTransportista << " | "
             << setw(13) << envio.estado << " |\n";
    }

    cout << "-------------------------------------------------------------\n";
}

void modificarEstadoEnvio() {
    system("cls");
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    if (envios.empty()) {
        cout << "\n\tNo hay envios registrados.\n";
        system("pause");
        return;
    }

    cout << "------------------------------------------------------------\n";
    cout << "                MODIFICAR ESTADO DE ENVIO                   \n";
    cout << "------------------------------------------------------------\n";

    cout << "ID Pedido       | Estado\n";
    cout << "------------------------------------------------------------\n";
    for (const auto& envio : envios) {
        cout << setw(15) << left << envio.idPedido << "| "
             << setw(23) << left << envio.estado << "\n";
    }
    cout << "------------------------------------------------------------\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

    string idPedido;
    cout << "Ingrese ID del pedido a modificar (0 para salir): ";
    getline(cin, idPedido);

    if (idPedido == "0") return;

    bool encontrado = false;
    for (auto& envio : envios) {
        if (envio.idPedido == idPedido) {
            cout << "Estado actual  : " << envio.estado << "\n";
            cout << "Ingrese nuevo estado (en camino, entregado): ";
            getline(cin, envio.estado);
            encontrado = true;

            // Si el nuevo estado es "entregado", también actualizar en pedidos
            if (envio.estado == "entregado") {
                vector<Pedidos> pedidos = cargarPedidos();
                for (auto& pedido : pedidos) {
                    if (pedido.getId() == idPedido) {
                        pedido.setEstado("entregado");
                        break;
                    }
                }
                guardarPedidos(pedidos);
            }

            break;
        }
    }

    if (encontrado) {
        Envios::guardarEnviosEnArchivo(envios);
        cout << "\n\tEstado modificado exitosamente.\n";
    } else {
        cout << "\n\tNo se encontro el envio con ID de pedido: " << idPedido << "\n";
    }

    system("pause");
}

void cancelarEnvio() {
    system("cls");
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    if (envios.empty()) {
        cout << "\n\tNo hay envios registrados.\n";
        system("pause");
        return;
    }

    cout << "------------------------------------------------------------\n";
    cout << "                      CANCELAR ENVIO                         \n";
    cout << "------------------------------------------------------------\n";

    cout << "ID Pedido       | Estado\n";
    cout << "------------------------------------------------------------\n";
    for (const auto& envio : envios) {
        cout << setw(15) << left << envio.idPedido << "| "
             << setw(23) << left << envio.estado << "\n";
    }
    cout << "------------------------------------------------------------\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

    string idPedido;
    cout << "Ingrese ID del pedido a cancelar (0 para salir): ";
    getline(cin, idPedido);

    if (idPedido == "0") return;

    bool encontrado = false;
    for (auto& envio : envios) {
        if (envio.idPedido == idPedido) {
            if (envio.estado == "entregado") {
                cout << "\n\tNo se puede cancelar un envio ya entregado.\n";
                system("pause");
                return;
            }
            if (envio.estado != "en camino") {
                cout << "\n\tNo se puede cancelar el envio en estado actual: " << envio.estado << "\n";
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
        cout << "\n\tEnvio cancelado exitosamente.\n";
    } else {
        cout << "\n\tNo se encontro el envio con ID de pedido: " << idPedido << "\n";
    }

    system("pause");
}

void eliminarEnvio() {
    system("cls");
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    if (envios.empty()) {
        cout << "\n\tNo hay envios registrados.\n";
        system("pause");
        return;
    }

    cout << "------------------------------------------------------------\n";
    cout << "                      ELIMINAR ENVIO                         \n";
    cout << "------------------------------------------------------------\n";

    cout << "ID Pedido       | Estado\n";
    cout << "------------------------------------------------------------\n";
    for (const auto& envio : envios) {
        cout << setw(15) << left << envio.idPedido << "| "
             << setw(23) << left << envio.estado << "\n";
    }
    cout << "------------------------------------------------------------\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

    string idPedido;
    cout << "Ingrese ID del pedido a eliminar (0 para salir): ";
    getline(cin, idPedido);

    if (idPedido == "0") return;

    auto it = std::remove_if(envios.begin(), envios.end(), [idPedido](const Envio& envio) {
        return envio.idPedido == idPedido;
    });

    if (it != envios.end()) {
        envios.erase(it, envios.end());
        Envios::guardarEnviosEnArchivo(envios);
        cout << "\n\tEnvio eliminado exitosamente.\n";
    } else {
        cout << "\n\tNo se encontro el envio con ID de pedido: " << idPedido << "\n";
    }

    system("pause");
}

void Envios::gestionEnvios() {
    int opcion = 0;
    do {
        system("cls");
        cout << "------------------------------------------------------------\n";
        cout << "                   SISTEMA DE GESTION DE ENVIOS             \n";
        cout << "------------------------------------------------------------\n";
        cout << "        [1] Crear nuevo envio\n";
        cout << "        [2] Consultar envios\n";
        cout << "        [3] Modificar estado de envio\n";
        cout << "        [4] Cancelar envio\n";
        cout << "        [5] Eliminar envio\n";
        cout << "        [6] Volver al menu principal\n";
        cout << "------------------------------------------------------------\n";
        cout << "           Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            crearEnvioInteractivo();
            break;
        case 2:
            mostrarEnvios();
            break;
        case 3:
            modificarEstadoEnvio();
            break;
        case 4:
            break;
        case 5:
            eliminarEnvio();
            break;
        case 6:
            cout << "\n\tSaliendo al menu principal...\n";
            break;
        default:
            cout << "\n\tOpcion invalida.\n";
            break;
        }
    } while (opcion != 6);
}

