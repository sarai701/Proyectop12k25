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
std::vector<Envio> Envios::envios;

// Rango de IDs para envíos
const int ID_ENVIO_INICIAL = 3500;
const int ID_ENVIO_FINAL = 3599;

// Funciones auxiliares para ID único
bool idEnvioDisponible(const vector<Envio>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(), [&id](const Envio& e) {
        return e.idEnvio == id;
    });
}

string generarIdEnvioUnico(const vector<Envio>& lista) {
    for (int i = ID_ENVIO_INICIAL; i <= ID_ENVIO_FINAL; ++i) {
        string id = to_string(i);
        if (idEnvioDisponible(lista, id)) return id;
    }
    return "";
}

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
        envio.idEnvio.resize(size);
        archivo.read(&envio.idEnvio[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
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
    ofstream archivo("envios.bin", ios::binary | ios::trunc);
    for (const auto& envio : envios) {
        size_t size;

        size = envio.idEnvio.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(envio.idEnvio.c_str(), size);

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
    Pedidos::cargarDesdeArchivoBin(Pedidos::listaPedidos);
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
    vector<Envio> envios = cargarEnviosDesdeArchivo();
    nuevo.idEnvio = generarIdEnvioUnico(envios);
    nuevo.idPedido = idPedido;
    nuevo.idTransportista = seleccionado.id;
    nuevo.estado = "en camino";

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
}

void Envios::crearEnvio(const std::string& idPedido, const std::vector<Transportistas>& transportistasDisponibles) {
    if (transportistasDisponibles.empty()) {
        std::cout << "No hay transportistas disponibles." << std::endl;
        return;
    }

    std::vector<Envio> envios = cargarEnviosDesdeArchivo();

    Envio nuevo;
    nuevo.idEnvio = generarIdEnvioUnico(envios); // ✅ si estás usando ID automático
    nuevo.idPedido = idPedido;
    nuevo.idTransportista = transportistasDisponibles.front().id;
    nuevo.estado = "en camino";

    envios.push_back(nuevo);
    guardarEnviosEnArchivo(envios);

    std::cout << "Envío creado con éxito para pedido: " << idPedido << std::endl;
}

void Envios::mostrarEnvios() {
    system("cls");  // Limpia la pantalla

    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    cout << "\n----------------------------- Reporte de Envíos -----------------------------\n" << endl;

    if (envios.empty()) {
        cout << "\t\t\tNo hay información ...\n";
        cout << "\nPresione una tecla para continuar...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << left
         << setw(15) << "ID Envío"
         << setw(15) << "ID Pedido"
         << setw(20) << "Transportista"
         << setw(15) << "Estado" << endl;

    cout << "---------------------------------------------------------------------------\n";

    for (const auto& envio : envios) {
        cout << left
             << setw(15) << envio.idEnvio
             << setw(15) << envio.idPedido
             << setw(20) << envio.idTransportista
             << setw(15) << envio.estado << endl;
    }

    cout << "---------------------------------------------------------------------------\n";

    cout << "\nPresione una tecla para continuar...";
    cin.ignore();
    cin.get();
}

void mostrarTablaEnvios(const vector<vector<string>>& tabla) {
    cout << "\n----------------------------- Tabla de Envíos -----------------------------\n" << endl;

    if (tabla.empty()) {
        cout << "\t\t\tNo hay información ...\n";
        return;
    }

    // Imprimir encabezado (asumiendo que la primera fila es encabezado)
    const vector<string>& encabezado = tabla[0];

    for (const auto& titulo : encabezado) {
        cout << left << setw(15) << titulo;
    }
    cout << endl;

    cout << "---------------------------------------------------------------------------\n";

    // Imprimir filas de datos (desde la segunda fila)
    for (size_t i = 1; i < tabla.size(); i++) {
        for (const auto& dato : tabla[i]) {
            cout << left << setw(15) << dato;
        }
        cout << endl;
    }

    cout << "---------------------------------------------------------------------------\n";
}

void modificarEstadoEnvio() {
    system("cls");
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    cout << "\n---------------------------- Modificar Estado de Envío ----------------------------\n" << endl;

    if (envios.empty()) {
        cout << "\n\t\tNo hay envíos registrados.\n";
        cout << "------------------------------------------------------------------------------------\n";
        system("pause");
        return;
    }

    cout << left << setw(12) << "ID Envío"
         << setw(20) << "Estado" << endl;
    cout << "------------------------------------------------------------------------------------\n";

    for (const auto& envio : envios) {
        cout << left << setw(12) << envio.idEnvio
             << setw(20) << envio.estado << endl;
    }
    cout << "------------------------------------------------------------------------------------\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

    string idEnvio;
    cout << "\nIngrese ID de envío a modificar (0 para salir): ";
    getline(cin, idEnvio);

    if (idEnvio == "0") {
        cout << "------------------------------------------------------------------------------------\n";
        return;
    }

    bool encontrado = false;
    for (auto& envio : envios) {
        if (envio.idEnvio == idEnvio) {
            encontrado = true;

            cout << "\nEstado actual: " << envio.estado << "\n";

            string nuevoEstado;
            cout << "Ingrese nuevo estado (en camino / entregado): ";
            getline(cin, nuevoEstado);

            // Validación del estado
            if (nuevoEstado != "en camino" && nuevoEstado != "entregado") {
                cout << "\n\tEstado inválido. Solo se permite 'en camino' o 'entregado'.\n";
                cout << "------------------------------------------------------------------------------------\n";
                system("pause");
                return;
            }

            envio.estado = nuevoEstado;

            // Si se marcó como entregado, actualizar también en pedidos
            if (nuevoEstado == "entregado") {
                vector<Pedidos> pedidos = cargarPedidos();
                for (auto& pedido : pedidos) {
                    if (pedido.getId() == envio.idPedido) {
                        pedido.setEstado("entregado");
                        break;
                    }
                }
                guardarPedidos(pedidos);
            }

            Envios::guardarEnviosEnArchivo(envios);
            cout << "\n---------------------------- Estado actualizado exitosamente ----------------------------\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "\n\tNo se encontró el envío con ID: " << idEnvio << "\n";
    }

    cout << "------------------------------------------------------------------------------------\n";
    system("pause");
}


void cancelarEnvio() {
    system("cls");
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    cout << "\n------------------------------ Cancelar Envío ------------------------------\n" << endl;

    if (envios.empty()) {
        cout << "\n\t\tNo hay envíos registrados.\n";
        cout << "---------------------------------------------------------------------------\n";
        system("pause");
        return;
    }

    cout << left << setw(12) << "ID Envío"
         << setw(20) << "Estado" << endl;
    cout << "---------------------------------------------------------------------------\n";

    for (const auto& envio : envios) {
        cout << left << setw(12) << envio.idEnvio
             << setw(20) << envio.estado << endl;
    }
    cout << "---------------------------------------------------------------------------\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

    string idEnvio;
    cout << "\nIngrese ID de envío a cancelar (0 para salir): ";
    getline(cin, idEnvio);

    if (idEnvio == "0") {
        cout << "---------------------------------------------------------------------------\n";
        return;
    }

    bool encontrado = false;
    for (auto& envio : envios) {
        if (envio.idEnvio == idEnvio) {
            encontrado = true;

            if (envio.estado == "entregado") {
                cout << "\n\tNo se puede cancelar un envío ya entregado.\n";
                cout << "---------------------------------------------------------------------------\n";
                system("pause");
                return;
            }
            if (envio.estado != "en camino") {
                cout << "\n\tNo se puede cancelar el envío en estado actual: " << envio.estado << "\n";
                cout << "---------------------------------------------------------------------------\n";
                system("pause");
                return;
            }

            envio.estado = "Cancelado";
            break;
        }
    }

    if (encontrado) {
        Envios::guardarEnviosEnArchivo(envios);
        cout << "\n----------------------------- Envío cancelado exitosamente -----------------------------\n";
    } else {
        cout << "\n\tNo se encontró el envío con ID: " << idEnvio << "\n";
    }

    cout << "---------------------------------------------------------------------------\n";
    system("pause");
}

void eliminarEnvio() {
    system("cls");
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();

    cout << "\n------------------------------ Eliminar Envío ------------------------------\n" << endl;

    if (envios.empty()) {
        cout << "\n\t\tNo hay envíos registrados.\n";
        cout << "---------------------------------------------------------------------------\n";
        system("pause");
        return;
    }

    cout << left << setw(12) << "ID Envío"
         << setw(20) << "Estado" << endl;
    cout << "---------------------------------------------------------------------------\n";

    for (const auto& envio : envios) {
        cout << left << setw(12) << envio.idEnvio
             << setw(20) << envio.estado << endl;
    }
    cout << "---------------------------------------------------------------------------\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

    string idEnvio;
    cout << "\nIngrese ID de envío a eliminar (0 para salir): ";
    getline(cin, idEnvio);

    if (idEnvio == "0") {
        cout << "---------------------------------------------------------------------------\n";
        return;
    }

    auto it = std::remove_if(envios.begin(), envios.end(), [idEnvio](const Envio& envio) {
        return envio.idEnvio == idEnvio;
    });

    if (it != envios.end()) {
        envios.erase(it, envios.end());
        Envios::guardarEnviosEnArchivo(envios);
        cout << "\n----------------------------- Envío eliminado exitosamente -----------------------------\n";
    } else {
        cout << "\n\tNo se encontró el envío con ID: " << idEnvio << "\n";
    }

    cout << "---------------------------------------------------------------------------\n";
    system("pause");
}

void Envios::gestionEnvios() {
    int opcion = 0;
    do {
        system("cls");
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "                          SISTEMA DE GESTION DE ENVIOS                          \n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "   [1] Crear nuevo envio\n";
        cout << "   [2] Consultar envios\n";
        cout << "   [3] Modificar estado de envio\n";
        cout << "   [4] Cancelar envio\n";
        cout << "   [5] Eliminar envio\n";
        cout << "   [6] Volver al menu principal\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "                     Seleccione una opcion: ";
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
                cancelarEnvio();
                break;
            case 5:
                eliminarEnvio();
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
