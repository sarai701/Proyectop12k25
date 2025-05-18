//Angoly Camila Mayo 2025
#include "facturacion.h"
#include "bitacora.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

void Facturacion::mostrarMenuFacturacion() {
    int opcion;
    do {
        system("cls");
        cout << "=== MENU FACTURACION ===\n";
        cout << "1. Crear factura\n";
        cout << "2. Mostrar facturas\n";
        cout << "3. Modificar factura\n";
        cout << "4. Eliminar factura\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: crearFactura(); break;
            case 2: mostrarFacturas(); break;
            case 3: modificarFactura(); break;
            case 4: eliminarFactura(); break;
            case 5: break;
            default:
                cout << "Opcion invalida!\n";
                system("pause");
        }
    } while (opcion != 5);
}

int Facturacion::generarIdFactura() {
    ifstream file(archivoFacturas, ios::binary);
    Factura factura;
    int ultimoId = 3555;

    while (file.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
        if (factura.idFactura > ultimoId)
            ultimoId = factura.idFactura;
    }

    file.close();

    int nuevoId = ultimoId + 1;
    if (nuevoId > 3606)
        nuevoId = 3556;

    return nuevoId;
}

void Facturacion::registrarBitacora(const Factura& factura, const string& accion, const string& usuario) {
    ofstream bitacora(archivoBitacora, ios::app);
    if (!bitacora) return;

    time_t now = time(0);
    tm* local = localtime(&now);
    char timestamp[100];
    strftime(timestamp, 100, "%d/%m/%Y %H:%M:%S", local);

    bitacora << factura.idFactura << "     "
             << usuario << "     "
             << "FACTURACION"
             << "     " << accion << " - ID: " << factura.idFactura
             << "     " << timestamp << "\n";

    bitacora.close();
}

void Facturacion::mostrarClientes() {
    ifstream file("clientes.bin", ios::binary);
    if (!file) {
        cout << "No se pudo abrir clientes.bin\n";
        return;
    }

    struct Cliente {
        int idCliente;
        char nombre[50];
        char direccion[100];
        char telefono[20];
    } cliente;

    cout << "\n--- Lista de Clientes ---\n";
    while (file.read(reinterpret_cast<char*>(&cliente), sizeof(cliente))) {
        cout << "ID: " << cliente.idCliente
             << " | Nombre: " << cliente.nombre
             << " | Direccion: " << cliente.direccion
             << " | Telefono: " << cliente.telefono << "\n";
    }

    file.close();
}

void Facturacion::mostrarPedidos() {
    ifstream file("pedidos.bin", ios::binary);
    if (!file) {
        cout << "No se pudo abrir pedidos.bin\n";
        return;
    }

    struct Pedido {
        int idPedido;
        int idCliente;
        char descripcion[100];
        float monto;
        bool entregado;
    } pedido;

    cout << "\n--- Lista de Pedidos ---\n";
    while (file.read(reinterpret_cast<char*>(&pedido), sizeof(pedido))) {
        cout << "ID: " << pedido.idPedido
             << " | Cliente ID: " << pedido.idCliente
             << " | Descripción: " << pedido.descripcion
             << " | Monto: " << pedido.monto
             << " | Entregado: " << (pedido.entregado ? "Sí" : "No") << "\n";
    }

    file.close();
}

void Facturacion::crearFactura() {
    Factura factura;
    system("cls");
    cout << "Crear nueva factura\n";

    factura.idFactura = generarIdFactura();
    cout << "ID factura generado: " << factura.idFactura << "\n";

    mostrarClientes();
    cout << "Ingrese ID del cliente: ";
    cin >> factura.idCliente;

    mostrarPedidos();
    cout << "Ingrese ID del pedido: ";
    cin >> factura.idPedido;

    // Obtener monto automáticamente desde pedido
    ifstream filePedido("pedidos.bin", ios::binary);
    if (!filePedido) {
        cout << "No se pudo abrir pedidos.bin\n";
        return;
    }

    struct Pedido {
        int idPedido;
        int idCliente;
        char descripcion[100];
        float monto;
        bool entregado;
    } pedido;

    bool encontrado = false;
    while (filePedido.read(reinterpret_cast<char*>(&pedido), sizeof(pedido))) {
        if (pedido.idPedido == factura.idPedido) {
            factura.monto = pedido.monto;
            encontrado = true;
            break;
        }
    }
    filePedido.close();

    if (!encontrado) {
        cout << "Pedido no encontrado. No se puede crear factura.\n";
        system("pause");
        return;
    }

    factura.pagada = false;
    strcpy(factura.cliente, "");

    guardarEnArchivo(factura);
    registrarBitacora(factura, "Factura agregada");

    cout << "Factura creada correctamente.\n";
    system("pause");
}

void Facturacion::guardarEnArchivo(Factura factura) {
    ofstream file(archivoFacturas, ios::binary | ios::app);
    if (file) {
        file.write(reinterpret_cast<char*>(&factura), sizeof(Factura));
        file.close();
    } else {
        cout << "No se pudo guardar la factura.\n";
    }
}

void Facturacion::mostrarFacturas() {
    system("cls");
    cout << "Listado de facturas:\n";

    ifstream file(archivoFacturas, ios::binary);
    if (!file) {
        cout << "No hay facturas guardadas.\n";
        system("pause");
        return;
    }

    Factura factura;
    while (file.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
        cout << "ID Factura: " << factura.idFactura
             << " | Cliente ID: " << factura.idCliente
             << " | Pedido ID: " << factura.idPedido
             << " | Monto: " << factura.monto
             << " | Pagada: " << (factura.pagada ? "Sí" : "No") << "\n";
    }

    file.close();
    system("pause");
}

void Facturacion::modificarFactura() {
    cout << "Función de modificar factura aún no implementada.\n";
    system("pause");
}

void Facturacion::eliminarFactura() {
    cout << "Función de eliminar factura aún no implementada.\n";
    system("pause");
}
