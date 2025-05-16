#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void mostrarTitulo(const string& titulo) {
    clearScreen();
    cout << "==============================================" << endl;
    cout << "   " << titulo << endl;
    cout << "==============================================" << endl << endl;
}

class Producto {
private:
    int id;
    string nombre, descripcion, categoria, proveedor;
    double precio;
    int stock;

public:
    Producto(int id, const string& nombre, const string& descripcion, double precio,
             const string& categoria, const string& proveedor, int stock)
        : id(id), nombre(nombre), descripcion(descripcion), precio(precio),
          categoria(categoria), proveedor(proveedor), stock(stock) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    double getPrecio() const { return precio; }
    string getCategoria() const { return categoria; }
    string getProveedor() const { return proveedor; }
    int getStock() const { return stock; }

    void mostrarInfo() const {
        cout << "\n----- Detalles del Producto -----" << endl;
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Descripcion: " << descripcion << endl;
        cout << "Precio: Q" << precio << endl;
        cout << "Categoria: " << categoria << endl;
        cout << "Proveedor: " << proveedor << endl;
        cout << "Stock: " << stock << endl;
        cout << "---------------------------------" << endl;
    }
};

class Compra {
private:
    int id;
    string cliente;
    string producto;
    int cantidad;
    double precioUnitario;

public:
    Compra(int id, const string& cliente, const string& producto, int cantidad, double precio)
        : id(id), cliente(cliente), producto(producto), cantidad(cantidad), precioUnitario(precio) {}

    int getId() const { return id; }
    string getCliente() const { return cliente; }
    string getProducto() const { return producto; }
    int getCantidad() const { return cantidad; }
    double getPrecioUnitario() const { return precioUnitario; }
    double getTotal() const { return cantidad * precioUnitario; }

    void mostrar() const {
        cout << "\n----- Detalles de la Compra -----" << endl;
        cout << "ID: " << id << endl;
        cout << "Cliente: " << cliente << endl;
        cout << "Producto: " << producto << endl;
        cout << "Cantidad: " << cantidad << endl;
        cout << "Precio Unitario: Q" << precioUnitario << endl;
        cout << "Total: Q" << getTotal() << endl;
        cout << "---------------------------------" << endl;
    }
};

class ModuloCatalogos {
private:
    vector<Producto> productos;
    int siguienteId = 1;
    const string archivo = "productos.csv";

    int generarId() {
        return siguienteId++;
    }

public:
    void menu() {
        int opcion;
        do {
            mostrarTitulo("MODULO DE CATALOGOS");
            cout << "1. Agregar producto\n";
            cout << "2. Buscar por ID\n";
            cout << "3. Buscar por nombre\n";
            cout << "4. Buscar por categoria\n";
            cout << "5. Listar todos los productos\n";
            cout << "6. Eliminar producto\n";
            cout << "7. Guardar en archivo\n";
            cout << "8. Cargar desde archivo\n";
            cout << "9. Volver al menu principal\n";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: agregarProducto(); break;
                case 2: buscarPorId(); break;
                case 3: buscarPorNombre(); break;
                case 4: buscarPorCategoria(); break;
                case 5: listarProductos(); break;
                case 6: eliminarProducto(); break;
                case 7: guardarArchivo(); break;
                case 8: cargarArchivo(); break;
                case 9: break;
                default:
                    cout << "\nOpcion invalida. Intente de nuevo." << endl;
            }
            if (opcion != 9) {
                cout << "\nPresione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (opcion != 9);
    }

    void agregarProducto() {
        mostrarTitulo("AGREGAR NUEVO PRODUCTO");

        string nombre, descripcion, categoria, proveedor;
        double precio;
        int stock;

        cout << "Ingrese los datos del producto:\n";
        cout << "Nombre del producto: ";
        getline(cin, nombre);

        cout << "Descripcion: ";
        getline(cin, descripcion);

        cout << "Precio (Q): ";
        while (!(cin >> precio) || precio <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Precio invalido. Ingrese un valor positivo: ";
        }
        cin.ignore();

        cout << "Categoria: ";
        getline(cin, categoria);

        cout << "Proveedor: ";
        getline(cin, proveedor);

        cout << "Stock: ";
        while (!(cin >> stock) || stock < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Stock invalido. Ingrese un numero entero positivo: ";
        }
        cin.ignore();

        int nuevoId = generarId();
        productos.emplace_back(nuevoId, nombre, descripcion, precio, categoria, proveedor, stock);
        cout << "\nProducto agregado con ID: " << nuevoId << endl;
    }

    Producto* buscarProductoPorId(int id) {
        for (auto& p : productos) {
            if (p.getId() == id) {
                return &p;
            }
        }
        return nullptr;
    }

    void buscarPorId() {
        mostrarTitulo("BUSCAR PRODUCTO POR ID");

        int id;
        cout << "Ingrese el ID del producto a buscar: ";
        while (!(cin >> id) || id <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ID invalido. Ingrese un numero positivo: ";
        }
        cin.ignore();

        Producto* producto = buscarProductoPorId(id);
        if (producto != nullptr) {
            producto->mostrarInfo();
        } else {
            cout << "\nNo se encontro ningun producto con ID: " << id << endl;
        }
    }

    vector<Producto*> buscarProductosPorNombre(const string& nombre) {
        vector<Producto*> encontrados;
        for (auto& p : productos) {
            string nombreProducto = p.getNombre();
            string nombreBusqueda = nombre;

            transform(nombreProducto.begin(), nombreProducto.end(), nombreProducto.begin(), ::tolower);
            transform(nombreBusqueda.begin(), nombreBusqueda.end(), nombreBusqueda.begin(), ::tolower);

            if (nombreProducto.find(nombreBusqueda) != string::npos) {
                encontrados.push_back(&p);
            }
        }
        return encontrados;
    }

    void buscarPorNombre() {
        mostrarTitulo("BUSCAR PRODUCTOS POR NOMBRE");

        string nombre;
        cout << "Ingrese el nombre o parte del nombre a buscar: ";
        getline(cin, nombre);

        auto resultados = buscarProductosPorNombre(nombre);

        if (resultados.empty()) {
            cout << "\nNo se encontraron productos con ese nombre." << endl;
        } else {
            cout << "\nSe encontraron " << resultados.size() << " productos:" << endl;
            for (auto p : resultados) {
                p->mostrarInfo();
                cout << endl;
            }
        }
    }

    vector<Producto*> buscarPorCategoria(const string& categoria) {
        vector<Producto*> encontrados;
        for (auto& p : productos) {
            if (p.getCategoria() == categoria) {
                encontrados.push_back(&p);
            }
        }
        return encontrados;
    }

    void buscarPorCategoria() {
        mostrarTitulo("BUSCAR PRODUCTOS POR CATEGORIA");

        string categoria;
        cout << "Ingrese la categoria a buscar: ";
        getline(cin, categoria);

        auto resultados = buscarPorCategoria(categoria);

        if (resultados.empty()) {
            cout << "\nNo se encontraron productos en esta categoria." << endl;
        } else {
            cout << "\nSe encontraron " << resultados.size() << " productos en la categoria '"
                 << categoria << "':" << endl;
            for (auto p : resultados) {
                p->mostrarInfo();
                cout << endl;
            }
        }
    }

    void listarProductos() {
        mostrarTitulo("LISTADO DE PRODUCTOS");

        if (productos.empty()) {
            cout << "No hay productos registrados." << endl;
            return;
        }

        cout << "Total de productos: " << productos.size() << endl << endl;
        for (const auto& producto : productos) {
            producto.mostrarInfo();
            cout << endl;
        }
    }

    bool eliminarProducto(int id) {
        auto it = remove_if(productos.begin(), productos.end(),
                            [id](const Producto& p) { return p.getId() == id; });
        if (it != productos.end()) {
            productos.erase(it, productos.end());
            return true;
        }
        return false;
    }

    void eliminarProducto() {
        mostrarTitulo("ELIMINAR PRODUCTO");

        int id;
        cout << "Ingrese el ID del producto a eliminar: ";
        while (!(cin >> id) || id <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ID invalido. Ingrese un numero positivo: ";
        }
        cin.ignore();

        if (eliminarProducto(id)) {
            cout << "\nProducto con ID " << id << " eliminado correctamente." << endl;
        } else {
            cout << "\nNo se encontro ningun producto con ID: " << id << endl;
        }
    }

    void guardarArchivo() {
        ofstream out(archivo);
        if (!out.is_open()) {
            cout << "Error al abrir el archivo para escritura." << endl;
            return;
        }

        for (const auto& p : productos) {
            out << p.getId() << "," << p.getNombre() << "," << p.getDescripcion() << ","
                << p.getPrecio() << "," << p.getCategoria() << "," << p.getProveedor() << ","
                << p.getStock() << "\n";
        }
        out.close();
        cout << "\nDatos guardados correctamente en " << archivo << endl;
    }

    void cargarArchivo() {
        ifstream in(archivo);
        if (!in.is_open()) {
            cout << "No se pudo abrir el archivo o no existe." << endl;
            return;
        }

        productos.clear();
        string linea;
        while (getline(in, linea)) {
            stringstream ss(linea);
            string temp;

            int id, stock;
            string nombre, descripcion, categoria, proveedor;
            double precio;

            getline(ss, temp, ','); id = stoi(temp);
            getline(ss, nombre, ',');
            getline(ss, descripcion, ',');
            getline(ss, temp, ','); precio = stod(temp);
            getline(ss, categoria, ',');
            getline(ss, proveedor, ',');
            getline(ss, temp); stock = stoi(temp);

            productos.emplace_back(id, nombre, descripcion, precio, categoria, proveedor, stock);
            if (id >= siguienteId) siguienteId = id + 1;
        }
        in.close();
        cout << "\nDatos cargados correctamente desde " << archivo << endl;
    }
};

class ModuloProcesos {
private:
    vector<Compra> compras;
    int siguienteId = 1;

public:
    void menu() {
        int opcion;
        do {
            mostrarTitulo("MODULO DE PROCESOS");
            cout << "1. Registrar nueva compra\n";
            cout << "2. Ver todas las compras\n";
            cout << "3. Buscar compra por ID\n";
            cout << "4. Eliminar compra\n";
            cout << "5. Volver al menu principal\n";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcion) {
                case 1: registrarCompra(); break;
                case 2: listarCompras(); break;
                case 3: buscarCompraPorId(); break;
                case 4: eliminarCompra(); break;
                case 5: break;
                default:
                    cout << "\nOpcion invalida. Intente de nuevo." << endl;
            }
            if (opcion != 5) {
                cout << "\nPresione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (opcion != 5);
    }

    void registrarCompra() {
        mostrarTitulo("REGISTRAR NUEVA COMPRA");

        string cliente, producto;
        int cantidad;
        double precio;

        cout << "Ingrese los datos de la compra:\n";
        cout << "Nombre del cliente: ";
        getline(cin, cliente);

        cout << "Nombre del producto: ";
        getline(cin, producto);

        cout << "Cantidad: ";
        while (!(cin >> cantidad) || cantidad <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Cantidad invalida. Ingrese un numero positivo: ";
        }

        cout << "Precio unitario (Q): ";
        while (!(cin >> precio) || precio <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Precio invalido. Ingrese un valor positivo: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int nuevoId = siguienteId++;
        compras.emplace_back(nuevoId, cliente, producto, cantidad, precio);
        cout << "\nCompra registrada con ID: " << nuevoId << endl;
        cout << "Total: Q" << compras.back().getTotal() << endl;
    }

    void listarCompras() const {
        mostrarTitulo("LISTADO DE COMPRAS");

        if (compras.empty()) {
            cout << "No hay compras registradas." << endl;
            return;
        }

        cout << "Total de compras: " << compras.size() << endl << endl;
        for (const auto& compra : compras) {
            compra.mostrar();
            cout << endl;
        }
    }

    void buscarCompraPorId() const {
        mostrarTitulo("BUSCAR COMPRA POR ID");

        int id;
        cout << "Ingrese el ID de la compra a buscar: ";
        while (!(cin >> id) || id <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ID invalido. Ingrese un numero positivo: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool encontrado = false;
        for (const auto& compra : compras) {
            if (compra.getId() == id) {
                compra.mostrar();
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "\nNo se encontro ninguna compra con ID: " << id << endl;
        }
    }

    bool eliminarCompra(int id) {
        auto it = remove_if(compras.begin(), compras.end(),
                            [id](const Compra& c) { return c.getId() == id; });
        if (it != compras.end()) {
            compras.erase(it, compras.end());
            return true;
        }
        return false;
    }

    void eliminarCompra() {
        mostrarTitulo("ELIMINAR COMPRA");

        int id;
        cout << "Ingrese el ID de la compra a eliminar: ";
        while (!(cin >> id) || id <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ID invalido. Ingrese un numero positivo: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (eliminarCompra(id)) {
            cout << "\nCompra con ID " << id << " eliminada correctamente." << endl;
        } else {
            cout << "\nNo se encontro ninguna compra con ID: " << id << endl;
        }
    }
};

class ModuloInformes {
private:
    vector<Compra> compras;
    int siguienteId = 1;

public:
    void menu() {
        int opcion;
        do {
            mostrarTitulo("MODULO DE INFORMES");
            cout << "1. Registrar compra\n";
            cout << "2. Generar informe\n";
            cout << "3. Volver al menu principal\n";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcion) {
                case 1: registrarCompra(); break;
                case 2: generarInforme(); break;
                case 3: break;
                default:
                    cout << "\nOpcion invalida. Intente de nuevo." << endl;
            }
            if (opcion != 3) {
                cout << "\nPresione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (opcion != 3);
    }

    void registrarCompra() {
        mostrarTitulo("REGISTRAR COMPRA PARA INFORME");

        string cliente, producto;
        int cantidad;
        double precio;

        cout << "Ingrese los datos de la compra:\n";
        cout << "Nombre del cliente: ";
        getline(cin, cliente);

        cout << "Nombre del producto: ";
        getline(cin, producto);

        cout << "Cantidad: ";
        while (!(cin >> cantidad) || cantidad <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Cantidad invalida. Ingrese un numero positivo: ";
        }

        cout << "Precio unitario (Q): ";
        while (!(cin >> precio) || precio <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Precio invalido. Ingrese un valor positivo: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int nuevoId = siguienteId++;
        compras.emplace_back(nuevoId, cliente, producto, cantidad, precio);
        cout << "\nCompra registrada con ID: " << nuevoId << endl;
        cout << "Total: Q" << compras.back().getTotal() << endl;
    }

    void generarInforme() const {
        mostrarTitulo("INFORME DE COMPRAS");

        if (compras.empty()) {
            cout << "No hay compras registradas para generar informe." << endl;
            return;
        }

        double totalGeneral = 0;
        double maxTotal = compras[0].getTotal();
        double minTotal = compras[0].getTotal();
        int idMax = compras[0].getId(), idMin = compras[0].getId();

        for (const auto& c : compras) {
            double total = c.getTotal();
            totalGeneral += total;

            if (total > maxTotal) {
                maxTotal = total;
                idMax = c.getId();
            }
            if (total < minTotal) {
                minTotal = total;
                idMin = c.getId();
            }
        }

        double promedio = totalGeneral / compras.size();

        cout << "\n----- Estadisticas Generales -----" << endl;
        cout << "Total de compras registradas: " << compras.size() << endl;
        cout << "Monto total acumulado: Q" << totalGeneral << endl;
        cout << "Promedio por compra: Q" << promedio << endl;
        cout << "Compra con mayor total (ID " << idMax << "): Q" << maxTotal << endl;
        cout << "Compra con menor total (ID " << idMin << "): Q" << minTotal << endl;

        cout << "\n----- Detalle de Compras -----" << endl;
        for (const auto& c : compras) {
            c.mostrar();
            cout << endl;
        }
    }
};

void mostrarMenuPrincipal() {
    mostrarTitulo("Menu General");
    cout << "1. Archivo\n";
    cout << "2. Catalogos\n";
    cout << "3. Procesos\n";
    cout << "4. Informes\n";
    cout << "5. Salir del sistema\n";
    cout << "\nSeleccione una opcion: ";
}

int main() {
    ModuloCatalogos moduloCatalogos;
    ModuloProcesos moduloProcesos;
    ModuloInformes moduloInformes;

    int opcion;
    do {
        mostrarMenuPrincipal();
        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nOpcion invalida. Ingrese un numero del 1 al 5: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                mostrarTitulo("MODULO DE ARCHIVO");
                cout << "\nFuncionalidad en desarrollo." << endl;
                break;
            case 2:
                moduloCatalogos.menu();
                break;
            case 3:
                moduloProcesos.menu();
                break;
            case 4:
                moduloInformes.menu();
                break;
            case 5:
                cout << "\nSaliendo del sistema... Hasta pronto!" << endl;
                break;
        }
        if (opcion != 5) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcion != 5);

    return 0;
}
