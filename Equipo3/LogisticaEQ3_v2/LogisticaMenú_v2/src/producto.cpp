#include "Producto.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include "bitacora.h"

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

using namespace std;

// Rango de códigos válidos para productos (3209-3259)
const int CODIGO_INICIAL = 3209;
const int CODIGO_FINAL = 3259;

// Genera un código único que no haya sido usado, dentro del rango permitido
string Producto::generarCodigoUnico(const vector<Producto>& lista) {
    // Recorre el rango buscando el primer código disponible
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigoDisponible(lista, codigo)) {
            return codigo; // Retorna el primer código libre
        }
    }
    return ""; // Si no hay disponibles, retorna cadena vacía
}

// Verifica si un código aún no ha sido asignado a ningún producto
bool Producto::codigoDisponible(const vector<Producto>& lista, const string& codigo) {
    // Retorna true si ningún producto tiene ese código
    return none_of(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });
}

// Comprueba si un código está dentro del rango numérico permitido
bool Producto::esCodigoValido(const string& codigo) {
    try {
        int num = stoi(codigo); // Intenta convertir a entero
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false; // Si ocurre una excepción, el código no es válido
    }
}

// Agrega un nuevo producto a la lista de inventario
void Producto::agregar(vector<Producto>& lista, const string& usuarioActual) {
    Producto nuevo;
    nuevo.codigo = generarCodigoUnico(lista); // Asigna código único

    // Verifica si hay códigos disponibles
    if (nuevo.codigo.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles\n";
        system("pause");
        return;
    }

    // Solicita los datos del nuevo producto
    cout << "\n\t\t=== AGREGAR PRODUCTO (Código: " << nuevo.codigo << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia buffer

    // Captura del nombre del producto
    cout << "\t\tNombre del producto: ";
    getline(cin, nuevo.nombre);

    // Captura y validación del precio
    cout << "\t\tPrecio: ";
    while (!(cin >> nuevo.precio)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese precio: ";
    }

    // Captura y validación del stock
    cout << "\t\tStock inicial: ";
    while (!(cin >> nuevo.stock)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock: ";
    }

    // Agrega a la lista y guarda en archivo
    lista.push_back(nuevo);
    guardarEnArchivo(lista);

    // Registra en bitácora
    bitacora::registrar(usuarioActual, "PRODUCTOS", "Agregado: " + nuevo.codigo);
    cout << "\n\t\tProducto registrado!\n";
    system("pause");
}

// Muestra todos los productos en una tabla formateada
void Producto::mostrar(const vector<Producto>& lista) {
    system("cls");
    cout << "\n\t\t=== INVENTARIO ===\n";
    cout << "\t\t" << left << setw(10) << "Código" << setw(30) << "Nombre"
         << setw(15) << "Precio" << setw(10) << "Stock" << "\n";
    cout << "\t\t" << string(65, '-') << "\n";

    // Muestra los datos de cada producto
    for (const auto& producto : lista) {
        cout << "\t\t" << left << setw(10) << producto.codigo << setw(30) << producto.nombre
             << "$" << setw(14) << fixed << setprecision(2) << producto.precio
             << setw(10) << producto.stock << "\n";
    }
    system("pause");
}

// Modifica los datos de un producto existente
void Producto::modificar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    // Busca el producto por su código
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    // Si se encuentra, permite modificarlo
    if (it != lista.end()) {
        cout << "\n\t\t=== MODIFICAR PRODUCTO (Código: " << codigo << ") ===\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia buffer

        // Modificación del nombre
        cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        // Modificación del precio
        cout << "\t\tNuevo precio (" << it->precio << "): ";
        while (!(cin >> it->precio)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor numérico para el precio: ";
        }

        // Modificación del stock
        cout << "\t\tNuevo stock (" << it->stock << "): ";
        while (!(cin >> it->stock)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor entero para el stock: ";
        }

        // Guarda cambios y registra modificación
        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto modificado - Código: " + codigo);
        cout << "\n\t\tProducto modificado exitosamente!\n";
    } else {
        // Si no se encuentra el producto
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

// Elimina un producto de la lista por su código
void Producto::eliminar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    // Busca el producto por código
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    // Si lo encuentra, lo elimina
    if (it != lista.end()) {
        lista.erase(it); // Elimina producto
        guardarEnArchivo(lista); // Guarda cambios
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto eliminado - Código: " + codigo);
        cout << "\n\t\tProducto eliminado exitosamente!\n";
    } else {
        // Producto no encontrado
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

// Guarda la lista de productos en el archivo de texto
void Producto::guardarEnArchivo(const vector<Producto>& lista) {
    // Crea archivo temporal para evitar pérdida de datos
    ofstream archivo("Productos.tmp", ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo crear archivo temporal!\n";
        return;
    }

    // Escribe cada producto en el archivo
    bool errorEscritura = false;
    for (const auto& producto : lista) {
        if (!(archivo << producto.codigo << ","
                     << producto.nombre << ","
                     << producto.precio << ","
                     << producto.stock << "\n")) {
            // Error al escribir un producto
            cerr << "\n\t\tError al escribir producto Código: " << producto.codigo << "\n";
            errorEscritura = true;
        }
    }

    // Fuerza guardado y verifica integridad
    archivo.flush();
    if (!archivo || errorEscritura) {
        cerr << "\n\t\tError: No se pudieron guardar todos los datos!\n";
        archivo.close();
        remove("Productos.tmp"); // Elimina archivo temporal
        return;
    }
    archivo.close();

    // Reemplaza el archivo anterior por el nuevo
    if (remove("Productos.txt") != 0 && errno != ENOENT) {
        cerr << "\n\t\tAdvertencia: No se pudo eliminar archivo anterior\n";
    }
    if (rename("Productos.tmp", "Productos.txt") != 0) {
        cerr << "\n\t\tError crítico: Falló el guardado final!\n";
    }
}

// Carga los productos desde el archivo a la lista en memoria
void Producto::cargarDesdeArchivo(vector<Producto>& lista) {
    // Limpia la lista actual
    lista.clear();

    // Abre archivo existente o lo crea si no existe
    ifstream archivo("Productos.txt");
    if (!archivo) {
        ofstream nuevoArchivo("Productos.txt");
        if (!nuevoArchivo) {
            cerr << "\n\t\tError crítico: No se pudo crear archivo de productos!\n";
        }
        return;
    }

    // Contadores de estadísticas
    int cargados = 0, omitidos = 0;
    string linea;

    // Lee línea por línea
    while (getline(archivo, linea)) {
        // Elimina espacios innecesarios
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;

        istringstream ss(linea);
        Producto temp;
        string campo;

        // Intenta extraer los campos del producto
        try {
            if (!getline(ss, temp.codigo, ',') ||
                !getline(ss, temp.nombre, ',') ||
                !(ss >> temp.precio) ||
                !(ss.ignore() && (ss >> temp.stock))) {
                throw runtime_error("Formato inválido");
            }

            // Verifica validez del código
            if (!esCodigoValido(temp.codigo)) {
                throw runtime_error("Código fuera de rango");
            }

            // Verifica duplicados
            if (!codigoDisponible(lista, temp.codigo)) {
                throw runtime_error("Código duplicado");
            }

            // Agrega a la lista
            lista.push_back(temp);
            cargados++;
        } catch (const exception& e) {
            // Muestra advertencia y omite producto
            cerr << "\n\t\tAdvertencia: Producto omitido (" << e.what() << "): " << linea << "\n";
            omitidos++;
        }
    }

    // Verifica error de lectura
    if (archivo.bad()) {
        cerr << "\n\t\tError: Fallo durante la lectura del archivo!\n";
    }

    // Muestra resumen de carga
    cout << "\n\t\tCarga completada. " << cargados << " productos cargados, "
         << omitidos << " omitidos.\n";
}

void Producto::setStock(int nuevoStock) {
    stock = nuevoStock;
}
