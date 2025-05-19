//JOnathan samuel Gonzalez Ixpata
#include "Contabilidad.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Bitacora.h"
#include "Moneda.h"

#ifdef _WIN32
#include <cstdlib>
#endif

Bitacora bitacoralog5;
using namespace std;

void Contabilidad::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Contabilidad::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Menú principal de Contabilidad
void Contabilidad::menuContabilidad() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== MENÚ CONTABILIDAD =====";
        cout << "\n1. Registrar Pago de Nómina";
        cout << "\n2. Desplegar Registro de Salarios";
        cout << "\n3. Volver al Menú Anterior";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: registroNomina(); break;
            case 2: desplegarRegistroSalarios(); break;
            case 3: limpiarPantalla();  // Limpia pantalla antes de regresar al menú principal
                return;
            default:
                cout << "\n¡Opción inválida!";
                pausar();
        }
    } while (true);
}

// Opción 1: Buscar empleado y registrar pago
void Contabilidad::registroNomina() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== REGISTRO DE PAGO ===";
    cout << "\nIngrese el código del empleado: ";
    getline(cin, codigo);

    ifstream archivo("empleados.txt");
    string linea;
    bool encontrado = false;

    // Buscar empleado en empleados.txt
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, telefono, codigoArchivo, direccion, salario;

        getline(ss, nombre, ',');
        getline(ss, telefono, ',');
        getline(ss, codigoArchivo, ',');
        getline(ss, direccion, ',');
        getline(ss, salario);

        if (codigoArchivo == codigo) {
            encontrado = true;
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre: " << nombre;
            cout << "\nCódigo: " << codigoArchivo;
            cout << "\nSalario: " << Moneda::getSimbolo()
         << Moneda::convertirDesdeGtq(stod(salario));

            // Registrar pago
            char respuesta;
            cout << "\n¿Se ha realizado el pago? (Y/N): ";
            cin >> respuesta;
            cin.ignore();

            // Guardar en pagos.txt
            ofstream archivoPagos("pagos.txt", ios::app);
            archivoPagos << codigoArchivo << "," << (toupper(respuesta) == 'Y' ? "Sí" : "No") << "\n";
            archivoPagos.close();

            cout << "\n¡Registro guardado!";
            break;
        }
    }

    if (!encontrado) {
        cout << "\n¡Empleado no encontrado!";
    }
     bitacoralog5.insertar("Admin", 4401, "Contabilidad", "Registro Nomina");

    pausar();
}

// Opción 2: Generar salarios.txt y mostrar registros
void Contabilidad::desplegarRegistroSalarios() {
    limpiarPantalla();

    // Leer empleados.txt y pagos.txt
    ifstream empleados("empleados.txt");
    ifstream pagos("pagos.txt");
    ofstream salarios("salarios.txt");

    vector<string> codigosPagados;
    string lineaPago;

    // Procesar pagos.txt
    while (getline(pagos, lineaPago)) {
        stringstream ss(lineaPago);
        string codigo, estado;
        getline(ss, codigo, ',');
        getline(ss, estado);
        codigosPagados.push_back(codigo);
    }

    // Encabezados con formato
    salarios << left << setw(30) << "NOMBRE"
             << setw(15) << "CODIGO"
             << setw(10) << "PAGADO" << "\n";

    // Procesar empleados.txt
    string lineaEmpleado;
    while (getline(empleados, lineaEmpleado)) {
        stringstream ss(lineaEmpleado);
        string nombre, telefono, codigo, direccion, salario;

        getline(ss, nombre, ',');
        getline(ss, telefono, ',');
        getline(ss, codigo, ',');
        getline(ss, direccion, ',');
        getline(ss, salario);

        // Verificar pago
        string estado = "No";
        if (find(codigosPagados.begin(), codigosPagados.end(), codigo) != codigosPagados.end()) {
            estado = "Si";
        }

        // Escribir en salarios.txt con formato
        salarios << left << setw(30) << nombre
                 << setw(15) << codigo
                 << setw(10) << estado << "\n";
    }

    salarios.close();

    // Mostrar salarios.txt con alineación
    ifstream archivoSalarios("salarios.txt");
    cout << "\n=== REGISTRO DE SALARIOS ===\n";

    string linea;
    while (getline(archivoSalarios, linea)) {
        cout << linea << "\n";
    }

    pausar();
    bitacoralog5.insertar("Admin", 4402, "Contabilidad", "Desplegar registro nomina");
}
