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

// Genera un código único dentro del rango establecido
string Producto::generarCodigoUnico(const vector<Producto>& lista) {
    // Busca secuencialmente el primer código disponible
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigoDisponible(lista, codigo)) {
            return codigo;
        }
    }
    return ""; // Retorna vacío si no hay códigos disponibles
}

// Verifica si un código no está siendo usado
bool Producto::codigoDisponible(const vector<Producto>& lista, const string& codigo) {
    // Busca en toda la lista sin coincidencias
    return none_of(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });
}

// Valida que el código esté dentro del rango permitido
bool Producto::esCodigoValido(const string& codigo) {
    try {
        int num = stoi(codigo);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false; // Captura errores de conversión
    }
}

// Agrega un nuevo producto al inventario
void Producto::agregar(vector<Producto>& lista, const string& usuarioActual) {
    Producto nuevo;
    nuevo.codigo = generarCodigoUnico(lista);

    // Verifica disponibilidad de códigos
    if (nuevo.codigo.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR PRODUCTO (Código: " << nuevo.codigo << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

    // Captura nombre
    cout << "\t\tNombre del producto: ";
    getline(cin, nuevo.nombre);

    // Validación de precio
    cout << "\t\tPrecio: ";
    while (!(cin >> nuevo.precio)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese precio: ";
    }

    // Validación de stock
    cout << "\t\tStock inicial: ";
    while (!(cin >> nuevo.stock)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock: ";
    }

    lista.push_back(nuevo);
    guardarEnArchivo(lista);
    bitacora::registrar(usuarioActual, "PRODUCTOS", "Agregado: " + nuevo.codigo);
    cout << "\n\t\tProducto registrado!\n";
    system("pause");
}

// Muestra todos los productos en formato de tabla
void Producto::mostrar(const vector<Producto>& lista) {
    system("cls");
    cout << "\n\t\t=== INVENTARIO ===\n";
    cout << "\t\t" << left << setw(10) << "Código" << setw(30) << "Nombre"
         << setw(15) << "Precio" << setw(10) << "Stock" << "\n";
    cout << "\t\t" << string(65, '-') << "\n";

    for (const auto& producto : lista) {
        cout << "\t\t" << left << setw(10) << producto.codigo << setw(30) << producto.nombre
             << "$" << setw(14) << fixed << setprecision(2) << producto.precio
             << setw(10) << producto.stock << "\n";
    }
    system("pause");
}

void Producto::modificar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        cout << "\n\t\t=== MODIFICAR PRODUCTO (Código: " << codigo << ") ===\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

        cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "\t\tNuevo precio (" << it->precio << "): ";
        while (!(cin >> it->precio)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor numérico para el precio: ";
        }

        cout << "\t\tNuevo stock (" << it->stock << "): ";
        while (!(cin >> it->stock)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor entero para el stock: ";
        }

        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto modificado - Código: " + codigo);
        cout << "\n\t\tProducto modificado exitosamente!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

void Producto::eliminar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto eliminado - Código: " + codigo);
        cout << "\n\t\tProducto eliminado exitosamente!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

void Producto::guardarEnArchivo(const vector<Producto>& lista) {
    // 1. Crear archivo temporal para escritura segura
    ofstream archivo("Productos.tmp", ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo crear archivo temporal!\n";
        return;
    }

    // 2. Escribir todos los productos con verificación
    bool errorEscritura = false;
    for (const auto& producto : lista) {
        if (!(archivo << producto.codigo << ","
                     << producto.nombre << ","
                     << producto.precio << ","
                     << producto.stock << "\n")) {
            cerr << "\n\t\tError al escribir producto Código: " << producto.codigo << "\n";
            errorEscritura = true;
        }
    }

    // 3. Forzar escritura y verificar
    archivo.flush();
    if (!archivo || errorEscritura) {
        cerr << "\n\t\tError: No se pudieron guardar todos los datos!\n";
        archivo.close();
        remove("Productos.tmp"); // Eliminar archivo temporal corrupto
        return;
    }
    archivo.close();

    // 4. Reemplazar archivo existente (operación atómica)
    if (remove("Productos.txt") != 0 && errno != ENOENT) {
        cerr << "\n\t\tAdvertencia: No se pudo eliminar archivo anterior\n";
    }
    if (rename("Productos.tmp", "Productos.txt") != 0) {
        cerr << "\n\t\tError crítico: Falló el guardado final!\n";
    }
}

void Producto::cargarDesdeArchivo(vector<Producto>& lista) {
    // 1. Limpiar lista existente
    lista.clear();

    // 2. Abrir archivo con verificación
    ifstream archivo("Productos.txt");
    if (!archivo) {
        // Crear archivo vacío si no existe
        ofstream nuevoArchivo("Productos.txt");
        if (!nuevoArchivo) {
            cerr << "\n\t\tError crítico: No se pudo crear archivo de productos!\n";
        }
        return;
    }

    // 3. Contadores para estadísticas
    int cargados = 0, omitidos = 0;
    string linea;

    // 4. Procesar cada línea
    while (getline(archivo, linea)) {
        // Eliminar espacios y saltos de línea
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;

        istringstream ss(linea);
        Producto temp;
        string campo;

        // 5. Parsear campos con verificación
        try {
            if (!getline(ss, temp.codigo, ',') ||
                !getline(ss, temp.nombre, ',') ||
                !(ss >> temp.precio) ||
                !(ss.ignore() && (ss >> temp.stock))) {
                throw runtime_error("Formato inválido");
            }

            // 6. Validar código
            if (!esCodigoValido(temp.codigo)) {
                throw runtime_error("Código fuera de rango");
            }

            if (!codigoDisponible(lista, temp.codigo)) {
                throw runtime_error("Código duplicado");
            }

            lista.push_back(temp);
            cargados++;
        } catch (const exception& e) {
            cerr << "\n\t\tAdvertencia: Producto omitido (" << e.what() << "): " << linea << "\n";
            omitidos++;
        }
    }

    // 7. Verificar estado final
    if (archivo.bad()) {
        cerr << "\n\t\tError: Fallo durante la lectura del archivo!\n";
    }

    // 8. Mostrar resumen (opcional)
    cout << "\n\t\tCarga completada. " << cargados << " productos cargados, "
         << omitidos << " omitidos.\n";
}
