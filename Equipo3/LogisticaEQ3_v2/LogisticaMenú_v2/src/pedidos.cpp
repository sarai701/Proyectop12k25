#include "pedidos.h"
#include "clientes.h"
#include "producto.h"
#include "Almacen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>
#include "envios.h"
#include "transportistas.h"

using namespace std;

// Inicialización de la lista estática
vector<Pedidos> Pedidos::listaPedidos;

// Rango de IDs para pedidos
const int CODIGO_INICIAL = 3400;
const int CODIGO_FINAL = 3500;

Pedidos::Pedidos() : fechaPedido(time(nullptr)), estado("pendiente") {}

string Pedidos::generarIdUnico(const vector<Pedidos>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

bool Pedidos::idDisponible(const vector<Pedidos>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(),
        [&id](const Pedidos& p) { return p.id == id; });
}

bool Pedidos::validarCliente(const string& idCliente, const vector<Clientes>& clientes) {
    return any_of(clientes.begin(), clientes.end(),
        [&idCliente](const Clientes& c) { return c.id == idCliente; });
}

bool Pedidos::validarProducto(const string& codigoProducto, const vector<Producto>& productos) {
    return any_of(productos.begin(), productos.end(),
        [&codigoProducto](const Producto& p) { return p.codigo == codigoProducto; });
}

bool Pedidos::validarAlmacen(const string& idAlmacen, const vector<Almacen>& almacenes) {
    return any_of(almacenes.begin(), almacenes.end(),
        [&idAlmacen](const Almacen& a) { return a.getId() == idAlmacen; });
}

string Pedidos::getDetalles() const {
    stringstream ss;
    ss << "Pedido ID: " << id << " - Cliente: " << idCliente << " - Estado: " << estado;
    return ss.str();
}

void Pedidos::gestionPedidos(const vector<Clientes>& clientes,
                           const vector<Producto>& productos,
                           const vector<Almacen>& almacenes) {
    // Cargar pedidos al iniciar
    cargarDesdeArchivo(listaPedidos);

    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| SISTEMA DE GESTION DE PEDIDOS        |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Crear nuevo pedido" << endl;
        cout << "\t\t 2. Consultar todos los pedidos" << endl;
        cout << "\t\t 3. Modificar pedido existente" << endl;
        cout << "\t\t 4. Cancelar pedido" << endl;
        cout << "\t\t 5. Completar pedido (envío)" << endl;
        cout << "\t\t 6. Volver al menú principal" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";

        while (!(cin >> opcion) || opcion < 1 || opcion > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un número del 1 al 7: ";
        }

        switch(opcion) {
            case 1: crearPedido(clientes, productos, almacenes); break;
            case 2: consultarPedidos(); break;
            case 3: modificarPedido(clientes, productos, almacenes); break;
            case 4: cancelarPedido(); break;
            case 5: {  // Completar pedido
                string idPedido;
                cout << "\n\t\tIngrese ID del pedido a completar: ";
                cin >> idPedido;
                completarPedido(idPedido, const_cast<vector<Producto>&>(productos));
                system("pause");
                break;
            }
            case 6:
                guardarEnArchivo(listaPedidos);
                auditoria.registrar(usuarioRegistrado.getNombre(),
                                  "PEDIDOS",
                                  "Salida de gestión de pedidos");
                break;
        }
    } while(opcion != 7);
}


void Pedidos::crearPedido(const std::vector<Clientes>& clientes,
                        const std::vector<Producto>& productos,
                        const std::vector<Almacen>& almacenes) {
    system("cls");
    cout << "\n\t\t[CREANDO NUEVO PEDIDO...]" << endl;

    // Verificar si hay datos disponibles
    if (clientes.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay clientes registrados.\n";
        cout << "\t\tDebe registrar al menos un cliente primero.\n";
        system("pause");
        return;
    }

    if (almacenes.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay almacenes registrados.\n";
        cout << "\t\tDebe registrar al menos un almacén primero.\n";
        system("pause");
        return;
    }

    if (productos.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay productos registrados.\n";
        cout << "\t\tDebe registrar al menos un producto primero.\n";
        system("pause");
        return;
    }

    Pedidos nuevo;
    nuevo.id = generarIdUnico(listaPedidos);

    if (nuevo.id.empty()) {
        cerr << "\n\t\tError: No hay IDs disponibles para nuevos pedidos\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== NUEVO PEDIDO (ID: " << nuevo.id << ") ===" << endl;

    // Mostrar lista de clientes disponibles
    cout << "\n\t\t--- CLIENTES DISPONIBLES ---\n";
    for (const auto& cliente : clientes) {
        cout << "\t\tID: " << cliente.getId() << " | Nombre: " << cliente.getNombre() << endl;
    }

    // Selección de cliente
    while (true) {
        cout << "\n\t\tIngrese ID del cliente: ";
        cin >> nuevo.idCliente;

        if (validarCliente(nuevo.idCliente, clientes)) break;
        cerr << "\t\tCliente no válido. Intente nuevamente.\n";
    }

    // Mostrar lista de almacenes disponibles
    cout << "\n\t\t--- ALMACENES DISPONIBLES ---\n";
    for (const auto& almacen : almacenes) {
        cout << "\t\tID: " << almacen.getId() << " | Dirección: " << almacen.getDireccion()
             << " | Estado: " << almacen.getEstado() << endl;
    }

    // Selección de almacén
    while (true) {
        cout << "\n\t\tIngrese ID del almacén: ";
        cin >> nuevo.idAlmacen;

        if (validarAlmacen(nuevo.idAlmacen, almacenes)) break;
        cerr << "\t\tAlmacén no válido. Intente nuevamente.\n";
    }

    // Agregar productos al pedido
    char continuar;
    do {
        // Mostrar lista de productos disponibles
        cout << "\n\t\t--- PRODUCTOS DISPONIBLES ---\n";
        for (auto& producto : productos) {
            cout << "\t\tCódigo: " << producto.getCodigo()
                 << " | Nombre: " << producto.getNombre()
                 << " | Stock: " << producto.getStock() << endl;
        }

        DetallePedido detalle;
        cout << "\n\t\t--- Agregar producto ---" << endl;

        // Selección de producto
        Producto* productoSeleccionado = nullptr;
        while (true) {
            cout << "\t\tIngrese código de producto: ";
            cin >> detalle.codigoProducto;

           // En la sección de selección de producto:
        auto it = find_if(productos.begin(), productos.end(),
            [&detalle](const Producto& p) { return p.getCodigo() == detalle.codigoProducto; });

        if (it != productos.end()) {
            Producto& productoSeleccionado = const_cast<Producto&>(*it);
                break;
            }
            cerr << "\t\tProducto no válido. Intente nuevamente.\n";
        }

        // Cantidad del producto
        while (true) {
            cout << "\t\tIngrese cantidad (Stock disponible: "
                 << productoSeleccionado->getStock() << "): ";
            if (cin >> detalle.cantidad && detalle.cantidad > 0) {
                if (detalle.cantidad <= productoSeleccionado->getStock()) {
                    // Actualizar stock
                    productoSeleccionado->setStock(productoSeleccionado->getStock() - detalle.cantidad);
                    break;
                } else {
                    cout << "\t\tNo hay suficiente stock. Intente con una cantidad menor.\n";
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\t\tCantidad inválida. Ingrese un número positivo: ";
            }
        }

        nuevo.detalles.push_back(detalle);

        cout << "\n\t\t¿Desea agregar otro producto? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    // Guardar cambios en productos
    Producto::guardarEnArchivo(productos);

    // Estado del pedido
    nuevo.estado = "pendiente";

    listaPedidos.push_back(nuevo);
    guardarEnArchivo(listaPedidos);

    auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Pedido creado - ID: " + nuevo.id);
    cout << "\n\t\tPedido registrado exitosamente!" << endl;
    system("pause");
}

void Pedidos::consultarPedidos() {
    system("cls");
    cout << "\n\t\t[CONSULTANDO PEDIDOS...]" << endl;

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos registrados." << endl;
        system("pause");
        return;
    }

    cout << "\n\t\t=== LISTA DE PEDIDOS ===" << endl;
    for (const auto& pedido : listaPedidos) {
        cout << "\t\tID: " << pedido.id << endl;
        cout << "\t\tCliente: " << pedido.idCliente << endl;
        cout << "\t\tAlmacén: " << pedido.idAlmacen << endl;

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&pedido.fechaPedido));
        cout << "\t\tFecha: " << buffer << endl;

        cout << "\t\tEstado: " << pedido.estado << endl;
        cout << "\t\tProductos:" << endl;

        double total = 0.0;
        for (const auto& detalle : pedido.detalles) {
            cout << "\t\t  - " << detalle.codigoProducto
                 << " x" << detalle.cantidad
                 << " @ $" << detalle.precioUnitario << endl;
            total += detalle.cantidad * detalle.precioUnitario;
        }

        cout << "\t\tTotal: $" << fixed << setprecision(2) << total << endl;
        cout << "\t\t----------------------------" << endl;
    }

    auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Consulta de pedidos");
    system("pause");
}

void Pedidos::modificarPedido(const vector<Clientes>& clientes,
                            const vector<Producto>& productos,
                            const vector<Almacen>& almacenes) {
    system("cls");
    cout << "\n\t\t[MODIFICANDO PEDIDO...]" << endl;

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos para modificar." << endl;
        system("pause");
        return;
    }

    // Mostrar lista de pedidos modificables
    cout << "\n\t\t=== PEDIDOS DISPONIBLES PARA MODIFICAR ===" << endl;
    for (const auto& pedido : listaPedidos) {
        if (pedido.estado == "pendiente" || pedido.estado == "procesado") {
            cout << "\t\tID: " << pedido.id << " - Estado: " << pedido.estado << endl;
        }
    }

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos para modificar." << endl;
        system("pause");
        return;
    }

    string id;
    cout << "\n\t\tIngrese ID del pedido a modificar (o 0 para volver): ";
    cin >> id;

    if (id == "0") return;

    auto it = find_if(listaPedidos.begin(), listaPedidos.end(),
        [&id](const Pedidos& p) { return p.id == id; });

    if (it != listaPedidos.end()) {
        cout << "\n\t\t=== MODIFICAR PEDIDO (ID: " << id << ") ===" << endl;

        // Modificar estado
        cout << "\t\tNuevo estado (pendiente/procesado/enviado/cancelado): ";
        cin >> it->estado;

        // Opción para modificar productos
        char opcion;
        cout << "\t\t¿Desea modificar los productos? (s/n): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') {
            it->detalles.clear();
            char continuar;
            do {
                DetallePedido detalle;
                cout << "\n\t\t--- Agregar producto ---" << endl;

                // Selección de producto
                while (true) {
                    cout << "\t\tCódigo de producto: ";
                    cin >> detalle.codigoProducto;

                    if (validarProducto(detalle.codigoProducto, productos)) {
                        // Buscar el producto para obtener el precio
                        auto prod = find_if(productos.begin(), productos.end(),
                            [&detalle](const Producto& p) { return p.codigo == detalle.codigoProducto; });
                        detalle.precioUnitario = prod->precio;
                        break;
                    }
                    cerr << "\t\tProducto no válido. Intente nuevamente.\n";
                }

                // Cantidad del producto
                cout << "\t\tCantidad: ";
                while (!(cin >> detalle.cantidad) || detalle.cantidad <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cerr << "\t\tCantidad inválida. Ingrese un número positivo: ";
                }

                it->detalles.push_back(detalle);

                cout << "\n\t\t¿Desea agregar otro producto? (s/n): ";
                cin >> continuar;
            } while (continuar == 's' || continuar == 'S');
        }

        guardarEnArchivo(listaPedidos);
        auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Pedido modificado - ID: " + id);
        cout << "\n\t\tPedido modificado exitosamente!" << endl;
    } else {
        cout << "\t\tPedido no encontrado." << endl;
    }
    system("pause");
}



void Pedidos::cancelarPedido() {
    system("cls");
    cout << "\n\t\t[CANCELANDO PEDIDO...]" << endl;

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos para cancelar." << endl;
        system("pause");
        return;
    }

    string id;
    cout << "\n\t\tIngrese ID del pedido a cancelar: ";
    cin >> id;

    auto it = find_if(listaPedidos.begin(), listaPedidos.end(),
        [&id](const Pedidos& p) { return p.id == id; });

    if (it != listaPedidos.end()) {
        // Cambiar estado a cancelado en lugar de eliminar
        it->estado = "cancelado";
        guardarEnArchivo(listaPedidos);
        auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Pedido cancelado - ID: " + id);
        cout << "\n\t\tPedido cancelado exitosamente!" << endl;
    } else {
        cout << "\t\tPedido no encontrado." << endl;
    }
    system("pause");
}


void Pedidos::guardarEnArchivo(const vector<Pedidos>& lista) {
    ofstream archivo("pedidos.dat", ios::binary | ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo abrir archivo de pedidos!\n";
        return;
    }

    try {
        // Escribir cantidad de pedidos primero
        size_t cantidad = lista.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        // Escribir cada pedido
        for (const auto& pedido : lista) {
            // Escribir campos básicos
            size_t idSize = pedido.id.size();
            archivo.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
            archivo.write(pedido.id.c_str(), idSize);

            size_t clienteSize = pedido.idCliente.size();
            archivo.write(reinterpret_cast<const char*>(&clienteSize), sizeof(clienteSize));
            archivo.write(pedido.idCliente.c_str(), clienteSize);

            size_t almacenSize = pedido.idAlmacen.size();
            archivo.write(reinterpret_cast<const char*>(&almacenSize), sizeof(almacenSize));
            archivo.write(pedido.idAlmacen.c_str(), almacenSize);

            archivo.write(reinterpret_cast<const char*>(&pedido.fechaPedido), sizeof(pedido.fechaPedido));

            size_t estadoSize = pedido.estado.size();
            archivo.write(reinterpret_cast<const char*>(&estadoSize), sizeof(estadoSize));
            archivo.write(pedido.estado.c_str(), estadoSize);

            // Escribir detalles del pedido
            size_t detallesSize = pedido.detalles.size();
            archivo.write(reinterpret_cast<const char*>(&detallesSize), sizeof(detallesSize));

            for (const auto& detalle : pedido.detalles) {
                size_t codigoSize = detalle.codigoProducto.size();
                archivo.write(reinterpret_cast<const char*>(&codigoSize), sizeof(codigoSize));
                archivo.write(detalle.codigoProducto.c_str(), codigoSize);

                archivo.write(reinterpret_cast<const char*>(&detalle.cantidad), sizeof(detalle.cantidad));
                archivo.write(reinterpret_cast<const char*>(&detalle.precioUnitario), sizeof(detalle.precioUnitario));
            }
        }

        archivo.flush();
        if (!archivo) {
            throw runtime_error("Error al escribir en archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al guardar pedidos: " << e.what() << "\n";
        archivo.close();
        remove("pedidos.dat");
        return;
    }

    archivo.close();
}

void Pedidos::cargarDesdeArchivo(vector<Pedidos>& lista) {
    lista.clear();
    ifstream archivo("pedidos.dat", ios::binary | ios::in);

    if (!archivo) {
        // Si el archivo no existe, no es un error (primera ejecución)
        return;
    }

    try {
        // Leer cantidad de pedidos
        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            Pedidos pedido;

            // Leer campos básicos
            size_t idSize;
            archivo.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
            pedido.id.resize(idSize);
            archivo.read(&pedido.id[0], idSize);

            size_t clienteSize;
            archivo.read(reinterpret_cast<char*>(&clienteSize), sizeof(clienteSize));
            pedido.idCliente.resize(clienteSize);
            archivo.read(&pedido.idCliente[0], clienteSize);

            size_t almacenSize;
            archivo.read(reinterpret_cast<char*>(&almacenSize), sizeof(almacenSize));
            pedido.idAlmacen.resize(almacenSize);
            archivo.read(&pedido.idAlmacen[0], almacenSize);

            archivo.read(reinterpret_cast<char*>(&pedido.fechaPedido), sizeof(pedido.fechaPedido));

            size_t estadoSize;
            archivo.read(reinterpret_cast<char*>(&estadoSize), sizeof(estadoSize));
            pedido.estado.resize(estadoSize);
            archivo.read(&pedido.estado[0], estadoSize);

            // Leer detalles del pedido
            size_t detallesSize;
            archivo.read(reinterpret_cast<char*>(&detallesSize), sizeof(detallesSize));

            for (size_t j = 0; j < detallesSize; ++j) {
                DetallePedido detalle;

                size_t codigoSize;
                archivo.read(reinterpret_cast<char*>(&codigoSize), sizeof(codigoSize));
                detalle.codigoProducto.resize(codigoSize);
                archivo.read(&detalle.codigoProducto[0], codigoSize);

                archivo.read(reinterpret_cast<char*>(&detalle.cantidad), sizeof(detalle.cantidad));
                archivo.read(reinterpret_cast<char*>(&detalle.precioUnitario), sizeof(detalle.precioUnitario));

                pedido.detalles.push_back(detalle);
            }

            lista.push_back(pedido);
        }

        if (archivo.bad()) {
            throw runtime_error("Error de lectura del archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al cargar pedidos: " << e.what() << "\n";
        lista.clear(); // Limpiar lista parcialmente cargada
    }

    archivo.close();
}

void Pedidos::completarPedido(const std::string& idPedido,
                            std::vector<Producto>& productos) {
    system("cls");
    cout << "\n\t\t[COMPLETANDO PEDIDO...]" << endl;

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos para completar." << endl;
        system("pause");
        return;
    }

    // Mostrar lista de pedidos que se pueden completar
    cout << "\n\t\t=== PEDIDOS DISPONIBLES PARA COMPLETAR ===" << endl;
    for (const auto& pedido : listaPedidos) {
        if (pedido.estado == "procesado") {
            cout << "\t\tID: " << pedido.id << endl;
        }
    }

    string id;
    cout << "\n\t\tIngrese ID del pedido a completar (o 0 para volver): ";
    cin >> id;

    if (id == "0") return;

    // Find the pedido in the list
    auto it = find_if(listaPedidos.begin(), listaPedidos.end(),
        [&id](const Pedidos& p) { return p.id == id; });

    if (it != listaPedidos.end()) {
        if (it->estado == "cancelado") {
            cout << "\n\t\tNo se puede completar un pedido cancelado.\n";
            system("pause");
            return;
        }

        // Cambiar estado a completado
        it->estado = "completado";

        // Registrar envío
        cout << "\n\t\tRegistrando envío para el pedido " << id << "...\n";
        Envios::crearEnvio(id, Transportistas::getTransportistasDisponibles());

        // Actualizar archivos
        guardarEnArchivo(listaPedidos);
        Producto::guardarEnArchivo(productos);

        auditoria.registrar(usuarioRegistrado.getNombre(),
                          "PEDIDOS",
                          "Pedido completado - ID: " + id);

        cout << "\n\t\tPedido completado exitosamente!\n";
    } else {
        cout << "\n\t\tPedido no encontrado.\n";
    }
    system("pause");
}
