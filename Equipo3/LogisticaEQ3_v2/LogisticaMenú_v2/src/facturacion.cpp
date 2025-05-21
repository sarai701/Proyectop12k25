// Angoly Araujo Mayo 2025 9959-24-17623

#include "facturacion.h"
#include "clientes.h"
#include "pedidos.h"
#include "bitacora.h"
#include "usuarios.h"
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <regex>

// Variables externas que se usan en este módulo
extern usuarios usuarioRegistrado; // Usuario actualmente registrado en sesión
extern bitacora auditoria;         // Bitácora para registrar acciones del sistema

// Genera un nuevo ID de factura
int Facturacion::generarIdFactura() {
    ifstream archivo("facturas.bin", ios::binary); // Abre archivo binario de facturas
    int ultimoId = 3554; // ID base mínimo
    Factura temp;

    // Lee facturas existentes para encontrar el último ID usado
    while (archivo.read(reinterpret_cast<char*>(&temp), sizeof(Factura))) {
        if (temp.idFactura > ultimoId)
            ultimoId = temp.idFactura;
    }

    archivo.close();

    // Control de rango de IDs permitidos
    if (ultimoId >= 3606) return -1; // ID fuera de rango permitido
    return ultimoId + 1; // Retorna el siguiente ID
}

// Guarda una factura en el archivo binario
void Facturacion::guardarEnArchivo(const Factura& factura) {
    ofstream archivo("facturas.bin", ios::binary | ios::app); // Abre en modo añadir
    archivo.write(reinterpret_cast<const char*>(&factura), sizeof(Factura)); // Escribe la factura
    archivo.close();
}

// Registra una acción en la bitácora del sistema
void Facturacion::registrarBitacora(const Factura& factura, const string& accion, const string& usuario) {
    ofstream bitacora("bitacora.bin", ios::app); // Abre archivo en modo añadir
    bitacora << accion << " de factura ID: " << factura.idFactura
             << " por usuario: " << usuario << endl;
    bitacora.close();
}

// Muestra el menú principal del módulo de facturación
void Facturacion::mostrarMenuFacturacion() {
    int opcion;
    do {
        system("cls"); // Limpia pantalla (en Windows)
        cout << "===========================================\n";
        cout << "        SISTEMA DE FACTURACION\n";
        cout << "     Usuario: " << usuarioRegistrado.getNombre() << "\n";
        cout << "===========================================\n";
        cout << " [1] Crear Factura\n";
        cout << " [2] Mostrar Facturas\n";
        cout << " [3] Modificar Factura\n";
        cout << " [4] Eliminar Factura\n";
        cout << " [0] Salir\n";
        cout << "-------------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada

        // Ejecuta la opción seleccionada
        switch (opcion) {
            case 1: crearFactura(); break;
            case 2: mostrarFacturas(); break;
            case 3: modificarFactura(); break;
            case 4: eliminarFactura(); break;
            case 0: cout << "\nSaliendo del modulo de facturacion...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n"; break;
        }

        if (opcion != 0) {
            cout << "\nPresione ENTER para continuar...";
            cin.get(); // Espera que el usuario presione ENTER
        }

    } while (opcion != 0); // Repite mientras no se seleccione salir
}

// Crea una nueva factura a partir de un pedido
void Facturacion::crearFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return; // Si el usuario desea volver, salir

    // Cargar pedidos desde archivo
    vector<Pedidos> listaPedidos;
    Pedidos::cargarDesdeArchivoBin(listaPedidos);

    // Verificar si hay pedidos disponibles
    if (listaPedidos.empty()) {
        cout << "No hay pedidos registrados." << endl;
        return;
    }

    // Mostrar lista de pedidos al usuario
    cout << "\n--- Lista de pedidos disponibles ---\n";
    for (const auto& pedido : listaPedidos) {
        cout << "ID Pedido: " << pedido.getId()
             << " | ID Cliente: " << pedido.getIdCliente()
             << " | Estado: " << pedido.getEstado() << endl;
    }

    // Solicita ID del pedido a facturar
    string idPedidoStr;
    cout << "Ingrese el ID del pedido para facturar: ";
    cin >> idPedidoStr;

    // Busca el pedido ingresado
    auto it = find_if(listaPedidos.begin(), listaPedidos.end(), [&idPedidoStr](const Pedidos& p) {
        return p.getId() == idPedidoStr;
    });

    if (it == listaPedidos.end()) {
        cout << "ID de pedido no encontrado." << endl;
        return;
    }

    // Crear nueva factura
    Factura nueva;
    nueva.idFactura = generarIdFactura();

    try {
        nueva.idPedido = stoi(it->getId());
        nueva.idCliente = stoi(it->getIdCliente());
    } catch (...) {
        cerr << "Error al convertir ID de pedido o cliente a entero." << endl;
        return;
    }

    nueva.monto = 0; // Inicializa monto
    nueva.pagada = false;
    memset(nueva.cliente, 0, sizeof(nueva.cliente)); // Limpia cadena de cliente

    // Calcular monto total desde los detalles del pedido
    string detalles = it->getDetalles();
    size_t pos = 0;

    // Procesa cada línea de detalle del pedido
    while ((pos = detalles.find('\n')) != string::npos) {
        string linea = detalles.substr(0, pos);
        detalles.erase(0, pos + 1);

        size_t precioPos = linea.find("Precio:");
        size_t cantPos = linea.find("Cantidad:");

        if (precioPos != string::npos && cantPos != string::npos) {
            try {
                string precioStr = linea.substr(precioPos + 7);
                string cantidadStr = linea.substr(cantPos + 9, precioPos - cantPos - 9);

                double precio = stod(precioStr);
                int cantidad = stoi(cantidadStr);

                nueva.monto += precio * cantidad; // Suma al total
            } catch (...) {
                cerr << "Error al extraer precio o cantidad de la linea: " << linea << endl;
            }
        }
    }

    // Obtener nombre y NIT del cliente asociado
    string nombreCliente = "No encontrado";
    string nitCliente = "No encontrado";

    vector<Clientes> listaClientes;
    Clientes::cargarDesdeArchivo(listaClientes);

    // Busca el cliente por ID
    for (const auto& c : listaClientes) {
        if (stoi(c.getId()) == nueva.idCliente) {
            nombreCliente = c.getNombre();
            nitCliente = c.getNit();
            strncpy(nueva.cliente, nombreCliente.c_str(), sizeof(nueva.cliente));
            break;
        }
    }

    // Guarda la factura en archivo
    guardarEnArchivo(nueva);
    registrarBitacora(nueva, "Creacion", usuarioRegistrado.getNombre());

    // Muestra los datos de la factura
    cout << "\n\n=====================================\n";
    cout << "              FACTURA                \n";
    cout << "=====================================\n";
    cout << "ID Factura : " << nueva.idFactura << endl;
    cout << "ID Cliente : " << nueva.idCliente << endl;
    cout << "Nombre     : " << nombreCliente << endl;
    cout << "NIT        : " << nitCliente << endl;
    cout << "ID Pedido  : " << nueva.idPedido << endl;
    cout << "Monto      : $" << fixed << setprecision(2) << nueva.monto << endl;
    cout << "Estado     : " << (nueva.pagada ? "Pagada" : "No Pagada") << endl;
    cout << "=====================================\n";
    cout << "Factura creada exitosamente.\n";
    cin.ignore();
    cin.get(); // Espera para que el usuario lea
}

// Modifica el estado de una factura existente
void Facturacion::modificarFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return;

    mostrarFacturas(); // Muestra facturas existentes

    int id;
    cout << "Ingrese el ID de la factura a modificar: ";
    cin >> id;

    fstream archivo("facturas.bin", ios::binary | ios::in | ios::out);
    Factura factura;
    bool encontrado = false;

    // Busca la factura por ID
    while (archivo.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
        if (factura.idFactura == id) {
            encontrado = true;

            // Cambia el estado de pago
            cout << "Modificar estado de pago (1: Pagada / 0: No Pagada): ";
            cin >> factura.pagada;

            // Retrocede para sobrescribir
            archivo.seekp(-static_cast<int>(sizeof(Factura)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&factura), sizeof(Factura));

            registrarBitacora(factura, "Modificacion", usuarioRegistrado.getNombre());
            cout << "Factura modificada correctamente.\n";
            break;
        }
    }

    if (!encontrado)
        cout << "Factura no encontrada.\n";

    archivo.close();
}

// Elimina una factura del sistema
void Facturacion::eliminarFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return;

    mostrarFacturas(); // Muestra facturas existentes

    int id;
    cout << "Ingrese el ID de la factura a eliminar: ";
    cin >> id;

    ifstream archivoLectura("facturas.bin", ios::binary);
    ofstream archivoTemp("temp.bin", ios::binary);

    Factura factura;
    bool eliminado = false;

    // Copia todas menos la factura a eliminar
    while (archivoLectura.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
        if (factura.idFactura == id) {
            eliminado = true;
            registrarBitacora(factura, "Eliminacion", usuarioRegistrado.getNombre());
        } else {
            archivoTemp.write(reinterpret_cast<const char*>(&factura), sizeof(Factura));
        }
    }

    archivoLectura.close();
    archivoTemp.close();

    // Sustituye el archivo original
    remove("facturas.bin");
    rename("temp.bin", "facturas.bin");

    if (eliminado)
        cout << "Factura eliminada correctamente.\n";
    else
        cout << "Factura no encontrada.\n";
}

// Muestra todas las facturas registradas
void Facturacion::mostrarFacturas() {
    ifstream archivo("facturas.bin", ios::binary);
    if (!archivo) {
        cout << "No hay facturas registradas.\n";
        return;
    }

    vector<Clientes> listaClientes;
    Clientes::cargarDesdeArchivo(listaClientes);

    Factura factura;
    cout << "\n======= LISTA DE FACTURAS =======\n";

    // Lee y muestra cada factura
    while (archivo.read(reinterpret_cast<char*>(&factura), sizeof(Factura))) {
        string nombre = "N/D";

        // Busca el nombre del cliente
        for (const auto& cliente : listaClientes) {
            if (stoi(cliente.getId()) == factura.idCliente) {
                nombre = cliente.getNombre();
                break;
            }
        }

        cout << "ID Factura : " << factura.idFactura << endl;
        cout << "ID Cliente : " << factura.idCliente << " (" << nombre << ")\n";
        cout << "ID Pedido  : " << factura.idPedido << endl;
        cout << "Monto      : $" << fixed << setprecision(2) << factura.monto << endl;
        cout << "Estado     : " << (factura.pagada ? "Pagada" : "No Pagada") << endl;
        cout << "----------------------------------\n";
    }

    archivo.close();
}
