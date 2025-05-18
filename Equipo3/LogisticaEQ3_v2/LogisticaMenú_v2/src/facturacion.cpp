//Angoly Araujo Mayo 2025
#include "facturacion.h"
#include "bitacora.h"
#include "pedidos.h"
#include "clientes.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

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

    bitacora << setw(10) << factura.idFactura << " "
             << setw(15) << usuario << " "
             << setw(20) << "FACTURACION" << " "
             << setw(20) << accion << " "
             << timestamp << endl;

    bitacora.close();
}

void Facturacion::crearFactura() {
    int repetir;
    do {
        Factura factura;
        system("cls");
        cout << "Crear nueva factura\n";

        factura.idFactura = generarIdFactura();
        cout << "ID factura generado: " << factura.idFactura << "\n";

        // Cargar y mostrar clientes
        vector<Clientes> clientesTemporales;
        Clientes temp;
        temp.cargarDesdeArchivo(clientesTemporales);
        Clientes::mostrar(clientesTemporales);

        if (clientesTemporales.empty()) {
            cout << "No hay clientes disponibles. No se puede crear la factura.\n";
            system("pause");
            return;
        }

        cout << "Ingrese ID del cliente: ";
        cin >> factura.idCliente;

        // Mostrar pedidos
        Pedidos pedidos;
        pedidos.consultarPedidos();
        cout << "Ingrese ID del pedido: ";
        cin >> factura.idPedido;

        // Buscar el pedido para extraer monto
        ifstream filePedido("pedidos.bin", ios::binary);
        if (!filePedido) {
            cout << "No se pudo abrir pedidos.bin\n";
            system("pause");
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

        system("cls");
        cout << "\n=========== FACTURA ===========" << endl;
        cout << "ID Factura: " << factura.idFactura << endl;
        cout << "ID Cliente: " << factura.idCliente << endl;
        cout << "ID Pedido : " << factura.idPedido << endl;
        cout << "Monto     : $" << fixed << setprecision(2) << factura.monto << endl;
        cout << "Pagada    : " << (factura.pagada ? "Sí" : "No") << endl;
        cout << "===============================" << endl;

        cout << "\n¿Desea regresar al menú principal? (1: Sí / 0: No): ";
        cin >> repetir;
    } while (repetir == 0);
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
    cout << left << setw(12) << "ID" << setw(12) << "Cliente" << setw(12) << "Pedido"
         << setw(12) << "Monto" << setw(10) << "Pagada\n";
    cout << string(60, '-') << "\n";
    while (file.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
        cout << left << setw(12) << factura.idFactura
             << setw(12) << factura.idCliente
             << setw(12) << factura.idPedido
             << setw(12) << fixed << setprecision(2) << factura.monto
             << setw(10) << (factura.pagada ? "Sí" : "No") << "\n";
    }

    file.close();
    system("pause");
}

void Facturacion::modificarFactura() {
    int repetir;
    do {
        system("cls");
        int id;
        cout << "Ingrese ID de la factura a modificar: ";
        cin >> id;

        fstream file(archivoFacturas, ios::binary | ios::in | ios::out);
        Factura factura;
        bool encontrado = false;

        while (file.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
            if (factura.idFactura == id) {
                cout << "\nFactura actual:\n";
                cout << "ID Cliente actual: " << factura.idCliente << endl;
                cout << "ID Pedido actual : " << factura.idPedido << endl;
                cout << "Monto actual     : " << factura.monto << endl;
                cout << "Pagada (1/0)     : " << factura.pagada << endl;

                cout << "\nIngrese nuevo ID de cliente: ";
                cin >> factura.idCliente;
                cout << "Ingrese nuevo ID de pedido : ";
                cin >> factura.idPedido;
                cout << "Ingrese nuevo monto        : ";
                cin >> factura.monto;
                cout << "¿Está pagada? (1: Sí / 0: No): ";
                cin >> factura.pagada;

                file.seekp(-static_cast<int>(sizeof(Factura)), ios::cur);
                file.write(reinterpret_cast<char*>(&factura), sizeof(Factura));
                encontrado = true;
                registrarBitacora(factura, "Factura modificada");
                break;
            }
        }
        file.close();

        if (!encontrado) cout << "Factura no encontrada.\n";

        cout << "\n¿Desea regresar al menú principal? (1: Sí / 0: No): ";
        cin >> repetir;
    } while (repetir == 0);
}

void Facturacion::eliminarFactura() {
    int repetir;
    do {
        system("cls");
        int id;
        cout << "Ingrese ID de la factura a eliminar: ";
        cin >> id;

        ifstream original(archivoFacturas, ios::binary);
        ofstream temporal("temp.bin", ios::binary);
        Factura factura;
        bool encontrado = false;

        while (original.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
            if (factura.idFactura == id) {
                registrarBitacora(factura, "Factura eliminada");
                encontrado = true;
                continue;
            }
            temporal.write(reinterpret_cast<char*>(&factura), sizeof(Factura));
        }

        original.close();
        temporal.close();
        remove(archivoFacturas);
        rename("temp.bin", archivoFacturas);

        if (!encontrado) cout << "Factura no encontrada.\n";
        else cout << "Factura eliminada.\n";

        cout << "\n¿Desea regresar al menú principal? (1: Sí / 0: No): ";
        cin >> repetir;
    } while (repetir == 0);
}
