// clase para mantenimiento Factura Dulce Reyes
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <vector>
#include "factura.h"
#include "utilidades.h"

using namespace std;

// Función para obtener fecha actual en formato DD/MM/AAAA
string obtenerFechaActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y", ltm);
    return string(buffer);
}

// Función para formatear montos con Q y 2 decimales
string formatearMonto(double monto) {
    stringstream ss;
    ss << "Q" << fixed << setprecision(2) << monto;
    return ss.str();
}

// Función para obtener la hora actual
string obtenerHoraActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%H:%M:%S", ltm);
    return string(buffer);
}

// Validar formato de fecha (DD/MM/AAAA)
bool validarFecha(const string& fecha) {
    if (fecha.length() != 10) return false;
    if (fecha[2] != '/' || fecha[5] != '/') return false;

    int dia = stoi(fecha.substr(0, 2));
    int mes = stoi(fecha.substr(3, 2));
    int anio = stoi(fecha.substr(6, 4));

    return (dia >= 1 && dia <= 31) &&
           (mes >= 1 && mes <= 12) &&
           (anio >= 2000 && anio <= 2100);
}

// Función para registrar factura por tipo (Cliente, Acreedor, Proveedor)
void registrarFacturaPorTipo(const string& tipo) {
    Factura f;
    ofstream archivo("facturas.bin", ios::binary);

    string idBuscar;
    string nombreCliente = "", nitCliente = "";

    cout << "\n--- REGISTRAR FACTURA (" << tipo << ") ---\n";

    // Solicitar ID
    cout << "Ingrese ID del " << tipo << ": ";
    cin >> idBuscar;

    // Buscar datos según tipo
    bool encontrado = false;

    if (tipo == "Cliente") {
        encontrado = obtenerDatosClientePorID(idBuscar, nombreCliente, nitCliente);
    }
    else if (tipo == "Acreedor") {
        encontrado = obtenerDatosAcreedorPorID(idBuscar, nombreCliente, nitCliente);
    }
    else if (tipo == "Proveedor") {
        encontrado = obtenerDatosProveedorPorID(idBuscar, nombreCliente, nitCliente);
    }

    if (!encontrado) {
        cout << tipo << " no encontrado. No se puede registrar la factura.\n";
        pausar();
        return;
    }

    // Código
    cout << "Código de factura: ";
    while (!(cin >> f.codigo) || f.codigo <= 0) {
        limpiarEntrada();
        cout << "Error: Ingrese un código válido (número positivo): ";
    }
    cin.ignore();

    // Monto
    cout << "Monto (ejemplo: 1250.50): ";
    while (!(cin >> f.monto) || f.monto <= 0) {
        limpiarEntrada();
        cout << "Error: Ingrese un monto válido (ejemplo: 1500.75): ";
    }
    cin.ignore();

    // Fecha y hora
    f.fecha = obtenerFechaActual();
    f.hora = obtenerHoraActual();
    f.tipo = tipo;
    f.tipoOperacion = (tipo == "Cliente") ? "Por cobrar" : "Por pagar";

    // Estado
    cout << "Estado (1. Pendiente / 2. Solvente): ";
    int op;
    while (!(cin >> op) || (op != 1 && op != 2)) {
        limpiarEntrada();
        cout << "Error: Ingrese 1 o 2: ";
    }
    f.estado = (op == 1) ? "Pendiente" : "Solvente";
    cin.ignore();

    // Guardar en archivo
    archivo << f.codigo << "," << nombreCliente << "," << nitCliente << ","
            << fixed << setprecision(2) << f.monto << ","
            << f.fecha << "," << f.hora << ","
            << f.tipo << "," << f.tipoOperacion << "," << f.estado << endl;

    archivo.close();

    cout << "\nFactura registrada con éxito.\n";
    pausar();
}

// Función para mostrar facturas
void mostrarFacturasPorTipo(const string& tipo) {
    ifstream archivo("facturas.bin");
    if (!archivo) {
        cout << "\nNo hay facturas registradas.\n";
        pausar();
        return;
    }

    vector<Factura> facturas;
    string linea;
    double totalMonto = 0.0;  // 👉 Variable para acumular el total

    // Leer y filtrar facturas
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        Factura f;

        string nombreCliente, nitCliente;

        getline(ss, campo, ',');
        f.codigo = stoi(campo);
        getline(ss, nombreCliente, ',');
        getline(ss, nitCliente, ',');

        getline(ss, campo, ',');
        f.monto = stod(campo);

        getline(ss, f.fecha, ',');
        getline(ss, f.hora, ',');
        getline(ss, f.tipo, ',');
        getline(ss, f.tipoOperacion, ',');
        getline(ss, f.estado);

        if (f.tipo == tipo) {
            cout << left
                 << setw(8) << f.codigo
                 << setw(25) << (nombreCliente.substr(0, 22) + (nombreCliente.length() > 22 ? "..." : ""))
                 << setw(15) << nitCliente
                 << setw(15) << formatearMonto(f.monto)
                 << setw(12) << f.fecha
                 << setw(10) << f.hora
                 << setw(15) << f.tipoOperacion
                 << setw(12) << f.estado << endl;

            totalMonto += f.monto;  // 👉 Sumar monto
        }
    }

    archivo.close();

    // 👉 Mostrar total
    cout << "\nTotal de montos (" << tipo << "): " << formatearMonto(totalMonto) << "\n";

    pausar();
}


// Función para modificar facturas
void modificarFacturaPorTipo(const string& tipo) {
    ifstream archivo("facturas.bin");
    if (!archivo) {
        cout << "\n No hay facturas para modificar.\n";
        pausar();
        return;
    }

    vector<string> lineas;
    string linea;
    bool modificado = false;
    int codigoBuscar;

    // Leer todas las líneas
    while (getline(archivo, linea)) {
        lineas.push_back(linea);
    }
    archivo.close();

    cout << "\n--- MODIFICAR FACTURA (" << tipo << ") ---\n";
    cout << "Ingrese código: ";
    cin >> codigoBuscar;
    cin.ignore();

    for (auto& linea : lineas) {
        stringstream ss(linea);
        string campo;
        Factura f;
        string nombreCliente, nitCliente;

        getline(ss, campo, ',');
        f.codigo = stoi(campo);
        getline(ss, nombreCliente, ',');
        getline(ss, nitCliente, ',');

        getline(ss, campo, ',');
        f.monto = stod(campo);
        getline(ss, f.fecha, ',');
        getline(ss, f.hora, ',');
        getline(ss, f.tipo, ',');
        getline(ss, f.tipoOperacion, ',');
        getline(ss, f.estado);

        if (f.codigo == codigoBuscar && f.tipo == tipo) {
            cout << "\n Editando factura #" << f.codigo << "\n";
            cout << "1. Nombre: " << nombreCliente << "\n";
            cout << "2. NIT: " << nitCliente << "\n";
            cout << "3. Monto: " << formatearMonto(f.monto) << "\n";
            cout << "4. Fecha: " << f.fecha << "\n";
            cout << "5. Estado: " << f.estado << "\n";
            cout << "0. Cancelar\n";
            cout << "Campo a modificar (1-5): ";

            int opcion;
            while (!(cin >> opcion) || opcion < 0 || opcion > 5) {
                limpiarEntrada();
                cout << "Opción inválida. Ingrese 1-5 o 0 para cancelar: ";
            }
            cin.ignore();

            if (opcion == 0) {
                cout << "Modificación cancelada.\n";
                pausar();
                return;
            }

            switch (opcion) {
                case 1:
                    cout << "Nuevo nombre: ";
                    getline(cin, nombreCliente);
                    break;
                case 2:
                    cout << "Nuevo NIT: ";
                    getline(cin, nitCliente);
                    break;
                case 3:
                    cout << "Nuevo monto: ";
                    while (!(cin >> f.monto) || f.monto <= 0) {
                        limpiarEntrada();
                        cout << "Monto inválido. Ingrese valor positivo: ";
                    }
                    cin.ignore();
                    break;
                case 4:
                    cout << "Nueva fecha (DD/MM/AAAA): ";
                    getline(cin, f.fecha);
                    while (!validarFecha(f.fecha)) {
                        cout << "Formato inválido. Use DD/MM/AAAA: ";
                        getline(cin, f.fecha);
                    }
                    break;
                case 5:
                    cout << "Nuevo estado (1. Pendiente / 2. Solvente): ";
                    int estado;
                    while (!(cin >> estado) || (estado != 1 && estado != 2)) {
                        limpiarEntrada();
                        cout << "Ingrese 1 o 2: ";
                    }
                    f.estado = (estado == 1) ? "Pendiente" : "Solvente";
                    cin.ignore();
                    break;
            }

            f.hora = obtenerHoraActual();
            stringstream nuevaLinea;
            nuevaLinea << f.codigo << "," << nombreCliente << "," << nitCliente << ","
                       << fixed << setprecision(2) << f.monto << ","
                       << f.fecha << "," << f.hora << ","
                       << f.tipo << "," << f.tipoOperacion << "," << f.estado;
            linea = nuevaLinea.str();
            modificado = true;
            cout << "\n Factura modificada.\n";
            break;
        }
    }

    if (modificado) {
        ofstream nuevoArchivo("facturas.bin");
        for (const auto& l : lineas) {
            nuevoArchivo << l << endl;
        }
        nuevoArchivo.close();
    } else {
        cout << "\n Factura no encontrada.\n";
    }

    pausar();
}

// Función para eliminar facturas
void eliminarFacturaPorTipo(const string& tipo) {
    ifstream archivo("facturas.bin");
    if (!archivo) {
        cout << "\n No hay facturas para eliminar.\n";
        pausar();
        return;
    }

    vector<string> lineas;
    string linea;
    bool eliminado = false;
    int codigoBuscar;

    while (getline(archivo, linea)) {
        lineas.push_back(linea);
    }
    archivo.close();

    cout << "\n--- ELIMINAR FACTURA (" << tipo << ") ---\n";
    cout << "Ingrese código: ";
    cin >> codigoBuscar;
    cin.ignore();

    for (auto it = lineas.begin(); it != lineas.end(); ++it) {
        stringstream ss(*it);
        string campo;
        Factura f;
        string nombreCliente, nitCliente;

        getline(ss, campo, ',');
        f.codigo = stoi(campo);
        getline(ss, nombreCliente, ',');
        getline(ss, nitCliente, ',');

        getline(ss, campo, ',');
        f.monto = stod(campo);
        getline(ss, f.fecha, ',');
        getline(ss, f.hora, ',');
        getline(ss, f.tipo, ',');
        getline(ss, f.tipoOperacion, ',');
        getline(ss, f.estado);

        if (f.codigo == codigoBuscar && f.tipo == tipo) {
            cout << "\nFactura a eliminar:\n";
            cout << "Código: " << f.codigo << "\n";
            cout << "Nombre: " << nombreCliente << "\n";
            cout << "Monto: " << formatearMonto(f.monto) << "\n";
            cout << "Fecha: " << f.fecha << "\n";

            cout << "\n¿Confirmar eliminación? (s/n): ";
            char confirmar;
            cin >> confirmar;
            cin.ignore();

            if (tolower(confirmar) == 's') {
                lineas.erase(it);
                eliminado = true;
                cout << " Factura eliminada.\n";
            } else {
                cout << " Eliminación cancelada.\n";
            }
            break;
        }
    }

    if (eliminado) {
        ofstream nuevoArchivo("facturas.bin");
        for (const auto& l : lineas) {
            nuevoArchivo << l << endl;
        }
        nuevoArchivo.close();
    } else {
        cout << "\nFactura no encontrada.\n";
    }
    pausar();
}

// Menús específicos por tipo de factura
void menuFacturaCliente() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t FACTURAS CLIENTE (Por cobrar)\n";
        cout << "\t--------------------------------\n";
        cout << "\t1. Registrar factura\n";
        cout << "\t2. Modificar factura\n";
        cout << "\t3. Eliminar factura\n";
        cout << "\t4. Mostrar facturas\n";
        cout << "\t5. Volver\n";
        cout << "\tSeleccione: ";

        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: registrarFacturaPorTipo("Cliente"); break;
            case 2: modificarFacturaPorTipo("Cliente"); break;
            case 3: eliminarFacturaPorTipo("Cliente"); break;
            case 4: mostrarFacturasPorTipo("Cliente"); break;
            case 5: break;
            default:
                cout << "Opción inválida\n";
                system("pause");
        }
    } while (opcion != 5);
}

void menuFacturaProveedor() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t ACTURAS PROVEEDOR (Por pagar)\n";
        cout << "\t---------------------------------\n";
        cout << "\t1. Registrar factura\n";
        cout << "\t2. Modificar factura\n";
        cout << "\t3. Eliminar factura\n";
        cout << "\t4. Mostrar facturas\n";
        cout << "\t5. Volver\n";
        cout << "\tSeleccione: ";

        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: registrarFacturaPorTipo("Proveedor"); break;
            case 2: modificarFacturaPorTipo("Proveedor"); break;
            case 3: eliminarFacturaPorTipo("Proveedor"); break;
            case 4: mostrarFacturasPorTipo("Proveedor"); break;
            case 5: break;
            default:
                cout << "Opción inválida\n";
                system("pause");
        }
    } while (opcion != 5);
}

void menuFacturaAcreedor() {
    int opcion;
    do {
        system("cls");
        cout << "\n\tFACTURAS ACREEDOR (Por pagar)\n";
        cout << "\t--------------------------------\n";
        cout << "\t1. Registrar factura\n";
        cout << "\t2. Modificar factura\n";
        cout << "\t3. Eliminar factura\n";
        cout << "\t4. Mostrar facturas\n";
        cout << "\t5. Volver\n";
        cout << "\tSeleccione: ";

        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: registrarFacturaPorTipo("Acreedor"); break;
            case 2: modificarFacturaPorTipo("Acreedor"); break;
            case 3: eliminarFacturaPorTipo("Acreedor"); break;
            case 4: mostrarFacturasPorTipo("Acreedor"); break;
            case 5: break;
            default:
                cout << "Opción inválida\n";
                system("pause");
        }
    } while (opcion != 5);
}
void menuReporteFactura() {
    system("cls");
    ifstream archivo("facturas.bin");

    if (!archivo) {
        cout << "\n\t\tNo hay facturas registradas.\n";
        system("pause");
        return;
    }

    // Encabezado del reporte
    cout << "\n\t\tREPORTE GENERAL DE FACTURAS\n";
    cout << "\t\t==========================\n\n";

    cout << left
         << setw(8) << "Código"
         << setw(25) << "Nombre"
         << setw(15) << "NIT"
         << setw(15) << "Monto"
         << setw(12) << "Fecha"
         << setw(10) << "Hora"
         << setw(15) << "Tipo"
         << setw(15) << "Operación"
         << setw(12) << "Estado" << endl;

    cout << string(120, '-') << endl;

    string linea;
    int totalFacturas = 0;

    // Leer todas las facturas
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;

        // Variables para almacenar los datos
        int codigo;
        string nombre, nit, fecha, hora, tipo, tipoOperation, estado;
        double monto;

        // Leer cada campo separado por comas
        getline(ss, campo, ',');
        codigo = stoi(campo);

        getline(ss, nombre, ',');
        getline(ss, nit, ',');

        getline(ss, campo, ',');
        monto = stod(campo);

        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, tipo, ',');
        getline(ss, tipoOperation, ',');
        getline(ss, estado);

        // Mostrar la factura
        cout << left
             << setw(8) << codigo
             << setw(25) << (nombre.substr(0, 22) + (nombre.length() > 22 ? "..." : ""))
             << setw(15) << nit
             << setw(15) << formatearMonto(monto)
             << setw(12) << fecha
             << setw(10) << hora
             << setw(15) << tipo
             << setw(15) << tipoOperation
             << setw(12) << estado << endl;

        totalFacturas++;
    }

    archivo.close();

    cout << "\n\t\tTotal de facturas registradas: " << totalFacturas << endl;

    // Opción para guardar en archivo
    cout << "\n\t\t¿Desea guardar este reporte en un archivo? (S/N): ";
    char opcion;
    cin >> opcion;

    if (toupper(opcion) == 'S') {
        ofstream reporteFile("reporte_facturas.txt");

        if (reporteFile) {
            reporteFile << "REPORTE GENERAL DE FACTURAS\n";
            reporteFile << "===========================\n\n";

            reporteFile << left
                       << setw(8) << "Código"
                       << setw(25) << "Nombre"
                       << setw(15) << "NIT"
                       << setw(15) << "Monto"
                       << setw(12) << "Fecha"
                       << setw(10) << "Hora"
                       << setw(15) << "Tipo"
                       << setw(15) << "Operación"
                       << setw(12) << "Estado" << endl;

            reporteFile << string(120, '-') << endl;

            // Volver a leer el archivo para guardar en el reporte
            ifstream archivo2("facturas.bin");
            while (getline(archivo2, linea)) {
                stringstream ss(linea);
                string campo;

                getline(ss, campo, ',');
                int codigo = stoi(campo);

                string nombre, nit, fecha, hora, tipo, tipoOperation, estado;
                getline(ss, nombre, ',');
                getline(ss, nit, ',');

                getline(ss, campo, ',');
                double monto = stod(campo);

                getline(ss, fecha, ',');
                getline(ss, hora, ',');
                getline(ss, tipo, ',');
                getline(ss, tipoOperation, ',');
                getline(ss, estado);

                reporteFile << left
                           << setw(8) << codigo
                           << setw(25) << nombre
                           << setw(15) << nit
                           << setw(15) << formatearMonto(monto)
                           << setw(12) << fecha
                           << setw(10) << hora
                           << setw(15) << tipo
                           << setw(15) << tipoOperation
                           << setw(12) << estado << endl;
            }

            archivo2.close();
            reporteFile.close();

            cout << "\n\t\tReporte guardado en 'reporte_facturas.txt'\n";
        } else {
            cout << "\n\t\tError al crear el archivo de reporte.\n";
        }
    }

    system("pause");


}
