//Karina Alejandra Arriaza Ortiz
#include "inventario.h"
#include "producto.h"
#include "almacen.h"
#include "proveedor.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// Variable estática para el inventario
std::vector<Inventario> Inventario::listaInventario;

void Inventario::controlInventario(vector<Producto>& productos,
                                 vector<Almacen>& almacenes,
                                 vector<Proveedor>& proveedores) {
    // Cargar inventario al iniciar
    cargarDesdeArchivoBin(listaInventario);

    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| CONTROL DE INVENTARIO - LOGISTICA     |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Consultar stock" << endl;
        cout << "\t\t 2. Registrar mercancia" << endl;
        cout << "\t\t 3. Ajustar inventario" << endl;
        cout << "\t\t 4. Reporte de existencias" << endl;
        cout << "\t\t 5. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";

        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un número del 1 al 5: ";
        }

        switch(opcion) {
            case 1:
                consultarStock(productos, almacenes);
                break;
            case 2:
                registrarMercancia(productos, almacenes, proveedores);
                break;
            case 3:
                ajustarInventario(productos, almacenes);
                break;
            case 4:
                reporteExistencias(productos, almacenes);
                break;
            case 5:
                transferirEntreAlmacenes(almacenes, productos);
                break;
            case 6:
                guardarEnArchivoBin(listaInventario);
                auditoria.registrar(usuarioRegistrado.getNombre(),
                                  "INVENTARIO",
                                  "Salida de gestión de inventario");
                break;
        }
    } while(opcion != 6);
     auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REPORTE");
    system("pause");
}

void Inventario::registrarMercancia(vector<Producto>& productos,
                                  const vector<Almacen>& almacenes,
                                  const vector<Proveedor>& proveedores) {
    system("cls");
    cout << "\n\t\t[REGISTRANDO NUEVA MERCANCÍA...]" << endl;

    // Verificar datos disponibles
    if (productos.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay productos registrados.\n";
        system("pause");
        return;
    }

    if (almacenes.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay almacenes registrados.\n";
        system("pause");
        return;
    }

    if (proveedores.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay proveedores registrados.\n";
        system("pause");
        return;
    }

    Inventario nuevo;

    // Mostrar productos disponibles
    cout << "\n\t\t--- PRODUCTOS DISPONIBLES ---\n";
    for (const auto& producto : productos) {
        cout << "\t\tCódigo: " << producto.getCodigo()
             << " | Nombre: " << producto.getNombre()<< endl;
    }

    // Seleccionar producto
    while (true) {
        cout << "\n\t\tIngrese código del producto: ";
        cin >> nuevo.codigoProducto;

        if (any_of(productos.begin(), productos.end(),
            [&nuevo](const Producto& p) { return p.getCodigo() == nuevo.codigoProducto; })) {
            break;
        }
        cerr << "\t\tProducto no válido. Intente nuevamente.\n";
    }

    // Mostrar almacenes disponibles
    cout << "\n\t\t--- ALMACENES DISPONIBLES ---\n";
    for (const auto& almacen : almacenes) {
        cout << "\t\tID: " << almacen.getId()
             << " | Dirección: " << almacen.getDireccion()
             << " | Estado: " << almacen.getEstado() << endl;
    }

    // Seleccionar almacén
    while (true) {
        cout << "\n\t\tIngrese ID del almacén: ";
        cin >> nuevo.idAlmacen;

        if (any_of(almacenes.begin(), almacenes.end(),
            [&nuevo](const Almacen& a) { return a.getId() == nuevo.idAlmacen; })) {
            break;
        }
        cerr << "\t\tAlmacén no válido. Intente nuevamente.\n";
    }

    // Mostrar proveedores disponibles
    cout << "\n\t\t--- PROVEEDORES DISPONIBLES ---\n";
    for (const auto& proveedor : proveedores) {
        cout << "\t\tID: " << proveedor.getId()
             << " | Nombre: " << proveedor.getNombre()
             << " | Teléfono: " << proveedor.getTelefono() << endl;
    }

    // Seleccionar proveedor
    while (true) {
        cout << "\n\t\tIngrese ID del proveedor: ";
        cin >> nuevo.idProveedor;

        if (any_of(proveedores.begin(), proveedores.end(),
            [&nuevo](const Proveedor& p) { return p.getId() == nuevo.idProveedor; })) {
            break;
        }
        cerr << "\t\tProveedor no válido. Intente nuevamente.\n";
    }

    // Cantidad de mercancía
    cout << "\t\tIngrese cantidad a registrar: ";
    while (!(cin >> nuevo.cantidad) || nuevo.cantidad <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "\t\tCantidad inválida. Ingrese un número positivo: ";
    }

    // Fecha de registro (actual)
    nuevo.fechaRegistro = time(nullptr);

    // Agregar al inventario
    listaInventario.push_back(nuevo);

    // Actualizar stock del producto
    auto it = find_if(productos.begin(), productos.end(),
        [&nuevo](const Producto& p) { return p.getCodigo() == nuevo.codigoProducto; });

    if (it != productos.end()) {
        it->setStock(it->getStock() + nuevo.cantidad);
        Producto::guardarEnArchivoBin(productos);
    }

    guardarEnArchivoBin(listaInventario);
    auditoria.registrar(usuarioRegistrado.getNombre(),
                      "INVENTARIO",
                      "Mercancía registrada - Producto: " + nuevo.codigoProducto +
                      ", Almacén: " + nuevo.idAlmacen);
    cout << "\n\t\t¡Mercancía registrada exitosamente!" << endl;
    system("pause");
}

void Inventario::consultarStock(const vector<Producto>& productos,
                              const vector<Almacen>& almacenes) {
    system("cls");
    cout << "\n\t\t[CONSULTANDO STOCK...]" << endl;

    if (listaInventario.empty()) {
        cout << "\n\t\tNo hay mercancía registrada en el inventario." << endl;
        system("pause");
        return;
    }

    // Filtrar por producto o almacén si se desea
    char filtro;
    cout << "\n\t\t¿Desea filtrar por producto (p), almacén (a) o ver todo (t)? ";
    cin >> filtro;

    string codigoFiltro;
    if (tolower(filtro) == 'p') {
        cout << "\t\tIngrese código de producto: ";
        cin >> codigoFiltro;
    } else if (tolower(filtro) == 'a') {
        cout << "\t\tIngrese ID de almacén: ";
        cin >> codigoFiltro;
    }

    cout << "\n\t\t=== INFORMACIÓN DE STOCK ===" << endl;
    cout << "\t\t" << string(90, '-') << endl;
    cout << "\t\t" << left << setw(15) << "Producto"
         << setw(15) << "Almacén"
         << setw(15) << "Proveedor"
         << setw(10) << "Cantidad"
         << setw(20) << "Fecha Registro"
         << setw(15) << "Estado" << endl;
    cout << "\t\t" << string(90, '-') << endl;

    for (const auto& item : listaInventario) {
        // Aplicar filtro si es necesario
        if ((tolower(filtro) == 'p' && item.codigoProducto != codigoFiltro) continue;
        if ((tolower(filtro) == 'a' && item.idAlmacen != codigoFiltro) continue;

        // Obtener nombres en lugar de IDs
        string nombreProducto = "No encontrado";
        auto prod = find_if(productos.begin(), productos.end(),
            [&item](const Producto& p) { return p.getCodigo() == item.codigoProducto; });
        if (prod != productos.end()) nombreProducto = prod->getNombre();

        string nombreAlmacen = "No encontrado";
        auto alm = find_if(almacenes.begin(), almacenes.end(),
            [&item](const Almacen& a) { return a.getId() == item.idAlmacen; });
        if (alm != almacenes.end()) nombreAlmacen = alm->getDireccion();

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&item.fechaRegistro));

        cout << "\t\t" << setw(15) << (nombreProducto.size() > 14 ? nombreProducto.substr(0, 12) + ".." : nombreProducto)
             << setw(15) << (nombreAlmacen.size() > 14 ? nombreAlmacen.substr(0, 12) + ".." : nombreAlmacen)
             << setw(15) << item.idProveedor
             << setw(10) << item.cantidad
             << setw(20) << buffer
             << setw(15) << item.estado << endl;
    }
    cout << "\t\t" << string(90, '-') << endl;

    auditoria.registrar(usuarioRegistrado.getNombre(),
                      "INVENTARIO",
                      "Consulta de stock");
    system("pause");
}

void Inventario::ajustarInventario(vector<Producto>& productos,
                                 const vector<Almacen>& almacenes) {
    system("cls");
    cout << "\n\t\t[AJUSTANDO INVENTARIO...]" << endl;

    if (listaInventario.empty()) {
        cout << "\n\t\tNo hay mercancía registrada para ajustar." << endl;
        system("pause");
        return;
    }

    // Mostrar lista de registros de inventario
    cout << "\n\t\t=== REGISTROS DE INVENTARIO ===" << endl;
    for (size_t i = 0; i < listaInventario.size(); i++) {
        cout << "\t\t" << i+1 << ". Producto: " << listaInventario[i].codigoProducto
             << " | Almacén: " << listaInventario[i].idAlmacen
             << " | Cantidad: " << listaInventario[i].cantidad << endl;
    }

    size_t indice;
    cout << "\n\t\tSeleccione el número del registro a ajustar (0 para cancelar): ";
    while (!(cin >> indice) || indice < 0 || indice > listaInventario.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese un número entre 0 y " << listaInventario.size() << ": ";
    }

    if (indice == 0) {
        cout << "\t\tOperación cancelada." << endl;
        system("pause");
        return;
    }

    Inventario& item = listaInventario[indice-1];
    int cantidadAnterior = item.cantidad;
    int nuevaCantidad;

    cout << "\n\t\tRegistro seleccionado:" << endl;
    cout << "\t\tProducto: " << item.codigoProducto << endl;
    cout << "\t\tAlmacén: " << item.idAlmacen << endl;
    cout << "\t\tCantidad actual: " << item.cantidad << endl;
    cout << "\t\tIngrese nueva cantidad: ";

    while (!(cin >> nuevaCantidad) || nuevaCantidad < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tCantidad inválida. Ingrese un número positivo: ";
    }

    // Actualizar el registro de inventario
    item.cantidad = nuevaCantidad;
    item.fechaRegistro = time(nullptr); // Actualizar fecha

    // Actualizar el stock del producto
    auto it = find_if(productos.begin(), productos.end(),
        [&item](const Producto& p) { return p.getCodigo() == item.codigoProducto; });

    if (it != productos.end()) {
        // Calcular diferencia y ajustar stock
        int diferencia = nuevaCantidad - cantidadAnterior;
        it->setStock(it->getStock() + diferencia);
        Producto::guardarEnArchivoBin(productos);
    }

    guardarEnArchivoBin(listaInventario);
    auditoria.registrar(usuarioRegistrado.getNombre(),
                      "INVENTARIO",
                      "Ajuste de inventario - Producto: " + item.codigoProducto +
                      ", Almacén: " + item.idAlmacen +
                      ", Cantidad anterior: " + to_string(cantidadAnterior) +
                      ", Nueva cantidad: " + to_string(nuevaCantidad));
    cout << "\n\t\t¡Inventario ajustado exitosamente!" << endl;
    system("pause");
}

void Inventario::reporteExistencias(const vector<Producto>& productos,
                                  const vector<Almacen>& almacenes) {
    system("cls");
    cout << "\n\t\t[GENERANDO REPORTE DE EXISTENCIAS...]" << endl;

    if (listaInventario.empty()) {
        cout << "\n\t\tNo hay mercancía registrada en el inventario." << endl;
        system("pause");
        return;
    }

    // Agrupar por producto y almacén
    map<pair<string, string>, int> existencias;

    for (const auto& item : listaInventario) {
        pair<string, string> key = make_pair(item.codigoProducto, item.idAlmacen);
        existencias[key] += item.cantidad;
    }

    cout << "\n\t\t=== REPORTE DE EXISTENCIAS ===" << endl;
    cout << "\t\t" << string(100, '-') << endl;
    cout << "\t\t" << left << setw(15) << "Producto"
         << setw(40) << "Descripción"
         << setw(20) << "Almacén"
         << setw(15) << "Existencias"
         << setw(10) << "Estado" << endl;
    cout << "\t\t" << string(100, '-') << endl;

    for (const auto& [key, cantidad] : existencias) {
        const string& codigoProducto = key.first;
        const string& idAlmacen = key.second;

        // Obtener información del producto
        string nombreProducto = "No encontrado";
        string descripcion = "N/A";
        auto prod = find_if(productos.begin(), productos.end(),
            [&codigoProducto](const Producto& p) { return p.getCodigo() == codigoProducto; });
        if (prod != productos.end()) {
            nombreProducto = prod->getNombre();
            descripcion = prod->getDescripcion();
        }

        // Obtener información del almacén
        string nombreAlmacen = "No encontrado";
        string estadoAlmacen = "N/A";
        auto alm = find_if(almacenes.begin(), almacenes.end(),
            [&idAlmacen](const Almacen& a) { return a.getId() == idAlmacen; });
        if (alm != almacenes.end()) {
            nombreAlmacen = alm->getDireccion();
            estadoAlmacen = alm->getEstado();
        }

        cout << "\t\t" << setw(15) << (nombreProducto.size() > 14 ? nombreProducto.substr(0, 12) + ".." : nombreProducto)
             << setw(40) << (descripcion.size() > 39 ? descripcion.substr(0, 37) + ".." : descripcion)
             << setw(20) << (nombreAlmacen.size() > 19 ? nombreAlmacen.substr(0, 17) + ".." : nombreAlmacen)
             << setw(15) << cantidad
             << setw(10) << estadoAlmacen << endl;
    }
    cout << "\t\t" << string(100, '-') << endl;

    auditoria.registrar(usuarioRegistrado.getNombre(),
                      "INVENTARIO",
                      "Reporte de existencias generado");
    system("pause");
}

void Inventario::transferirEntreAlmacenes(vector<Almacen>& almacenes,
                                        vector<Producto>& productos) {
    system("cls");
    cout << "\n\t\t[TRANSFIRIENDO ENTRE ALMACENES...]" << endl;

    if (listaInventario.empty()) {
        cout << "\n\t\tNo hay mercancía registrada para transferir." << endl;
        system("pause");
        return;
    }

    // Mostrar almacenes disponibles
    cout << "\n\t\t--- ALMACENES DISPONIBLES ---\n";
    for (const auto& almacen : almacenes) {
        cout << "\t\tID: " << almacen.getId()
             << " | Dirección: " << almacen.getDireccion()
             << " | Estado: " << almacen.getEstado() << endl;
    }

    string idAlmacenOrigen, idAlmacenDestino;
    cout << "\n\t\tIngrese ID del almacén de origen: ";
    cin >> idAlmacenOrigen;
    cout << "\t\tIngrese ID del almacén de destino: ";
    cin >> idAlmacenDestino;

    // Validar almacenes
    auto itOrigen = find_if(almacenes.begin(), almacenes.end(),
        [&idAlmacenOrigen](const Almacen& a) { return a.getId() == idAlmacenOrigen; });
    auto itDestino = find_if(almacenes.begin(), almacenes.end(),
        [&idAlmacenDestino](const Almacen& a) { return a.getId() == idAlmacenDestino; });

    if (itOrigen == almacenes.end() || itDestino == almacenes.end()) {
        cout << "\t\tAlmacén de origen o destino no válido." << endl;
        system("pause");
        return;
    }

    // Mostrar productos disponibles en el almacén de origen
    cout << "\n\t\t--- PRODUCTOS DISPONIBLES EN ALMACÉN " << idAlmacenOrigen << " ---\n";
    vector<string> productosDisponibles;
    for (const auto& item : listaInventario) {
        if (item.idAlmacen == idAlmacenOrigen && item.cantidad > 0) {
            auto prod = find_if(productos.begin(), productos.end(),
                [&item](const Producto& p) { return p.getCodigo() == item.codigoProducto; });

            if (prod != productos.end()) {
                cout << "\t\tCódigo: " << item.codigoProducto
                     << " | Nombre: " << prod->getNombre()
                     << " | Cantidad: " << item.cantidad << endl;
                productosDisponibles.push_back(item.codigoProducto);
            }
        }
    }

    if (productosDisponibles.empty()) {
        cout << "\t\tNo hay productos disponibles en el almacén de origen." << endl;
        system("pause");
        return;
    }

    string codigoProducto;
    cout << "\n\t\tIngrese código del producto a transferir: ";
    cin >> codigoProducto;

    // Verificar que el producto existe en el almacén de origen
    auto itProductoOrigen = find_if(listaInventario.begin(), listaInventario.end(),
        [&idAlmacenOrigen, &codigoProducto](const Inventario& i) {
            return i.idAlmacen == idAlmacenOrigen && i.codigoProducto == codigoProducto && i.cantidad > 0;
        });

    if (itProductoOrigen == listaInventario.end()) {
        cout << "\t\tProducto no disponible en el almacén de origen." << endl;
        system("pause");
        return;
    }

    int cantidadATransferir;
    cout << "\t\tIngrese cantidad a transferir (máx. " << itProductoOrigen->cantidad << "): ";
    while (!(cin >> cantidadATransferir) || cantidadATransferir <= 0 || cantidadATransferir > itProductoOrigen->cantidad) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tCantidad inválida. Ingrese un número entre 1 y " << itProductoOrigen->cantidad << ": ";
    }

    // Realizar la transferencia
    // 1. Reducir en el almacén de origen
    itProductoOrigen->cantidad -= cantidadATransferir;
    itProductoOrigen->fechaRegistro = time(nullptr);

    // 2. Aumentar en el almacén de destino (o crear nuevo registro)
    auto itProductoDestino = find_if(listaInventario.begin(), listaInventario.end(),
        [&idAlmacenDestino, &codigoProducto](const Inventario& i) {
            return i.idAlmacen == idAlmacenDestino && i.codigoProducto == codigoProducto;
        });

    if (itProductoDestino != listaInventario.end()) {
        itProductoDestino->cantidad += cantidadATransferir;
        itProductoDestino->fechaRegistro = time(nullptr);
    } else {
        Inventario nuevo;
        nuevo.codigoProducto = codigoProducto;
        nuevo.idAlmacen = idAlmacenDestino;
        nuevo.idProveedor = itProductoOrigen->idProveedor;
        nuevo.cantidad = cantidadATransferir;
        nuevo.fechaRegistro = time(nullptr);
        nuevo.estado = "activo";
        listaInventario.push_back(nuevo);
    }

    guardarEnArchivoBin(listaInventario);
    auditoria.registrar(usuarioRegistrado.getNombre(),
                      "INVENTARIO",
                      "Transferencia de " + to_string(cantidadATransferir) +
                      " unidades del producto " + codigoProducto +
                      " desde almacén " + idAlmacenOrigen +
                      " a almacén " + idAlmacenDestino);
    cout << "\n\t\t¡Transferencia realizada exitosamente!" << endl;
    system("pause");
}

void Inventario::guardarEnArchivoBin(const vector<Inventario>& lista) {
    ofstream archivo("inventario.bin", ios::binary | ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo abrir archivo de inventario!\n";
        return;
    }

    try {
        // Escribir cantidad de registros primero
        size_t cantidad = lista.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        // Escribir cada registro
        for (const auto& item : lista) {
            // Escribir campos básicos
            size_t codigoSize = item.codigoProducto.size();
            archivo.write(reinterpret_cast<const char*>(&codigoSize), sizeof(codigoSize));
            archivo.write(item.codigoProducto.c_str(), codigoSize);

            size_t almacenSize = item.idAlmacen.size();
            archivo.write(reinterpret_cast<const char*>(&almacenSize), sizeof(almacenSize));
            archivo.write(item.idAlmacen.c_str(), almacenSize);

            size_t proveedorSize = item.idProveedor.size();
            archivo.write(reinterpret_cast<const char*>(&proveedorSize), sizeof(proveedorSize));
            archivo.write(item.idProveedor.c_str(), proveedorSize);

            archivo.write(reinterpret_cast<const char*>(&item.cantidad), sizeof(item.cantidad));
            archivo.write(reinterpret_cast<const char*>(&item.fechaRegistro), sizeof(item.fechaRegistro));

            size_t estadoSize = item.estado.size();
            archivo.write(reinterpret_cast<const char*>(&estadoSize), sizeof(estadoSize));
            archivo.write(item.estado.c_str(), estadoSize);
        }

        archivo.flush();
        if (!archivo) {
            throw runtime_error("Error al escribir en archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al guardar inventario: " << e.what() << "\n";
        archivo.close();
        remove("inventario.bin");
        return;
    }

    archivo.close();
    system("pause");
}

void Inventario::cargarDesdeArchivoBin(vector<Inventario>& lista) {
    lista.clear();
    ifstream archivo("inventario.bin", ios::binary | ios::in);

    if (!archivo) {
        // Si el archivo no existe, no es un error (primera ejecución)
        return;
    }

    try {
        // Leer cantidad de registros
        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            Inventario item;

            // Leer campos básicos
            size_t codigoSize;
            archivo.read(reinterpret_cast<char*>(&codigoSize), sizeof(codigoSize));
            item.codigoProducto.resize(codigoSize);
            archivo.read(&item.codigoProducto[0], codigoSize);

            size_t almacenSize;
            archivo.read(reinterpret_cast<char*>(&almacenSize), sizeof(almacenSize));
            item.idAlmacen.resize(almacenSize);
            archivo.read(&item.idAlmacen[0], almacenSize);

            size_t proveedorSize;
            archivo.read(reinterpret_cast<char*>(&proveedorSize), sizeof(proveedorSize));
            item.idProveedor.resize(proveedorSize);
            archivo.read(&item.idProveedor[0], proveedorSize);

            archivo.read(reinterpret_cast<char*>(&item.cantidad), sizeof(item.cantidad));
            archivo.read(reinterpret_cast<char*>(&item.fechaRegistro), sizeof(item.fechaRegistro));

            size_t estadoSize;
            archivo.read(reinterpret_cast<char*>(&estadoSize), sizeof(estadoSize));
            item.estado.resize(estadoSize);
            archivo.read(&item.estado[0], estadoSize);

            lista.push_back(item);
        }

        if (archivo.bad()) {
            throw runtime_error("Error de lectura del archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al cargar inventario: " << e.what() << "\n";
        lista.clear(); // Limpiar lista parcialmente cargada
    }

    archivo.close();

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REPORTE");
    system("pause");
}
