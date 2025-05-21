//JOnathan samuel Gonzalez Ixpata
#include "Contabilidad.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Bitacora.h"
#include "Moneda.h"

#ifdef _WIN32
#include <cstdlib> // Para system("cls") en Windows
#endif

// Instancia de bitácora para registrar actividades de Contabilidad
Bitacora bitacoralogContabilidad;

using namespace std;

// Limpia la pantalla según el sistema operativo
void Contabilidad::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa la ejecución hasta que el usuario presione ENTER
void Contabilidad::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void Contabilidad::setUsuario(const string& u) {
    usuario = u;
}

// Menú principal del módulo de contabilidad
void Contabilidad::menuContabilidad() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MENÚ CONTABILIDAD =====";
        cout << "\n1. Registrar Pago de Nómina";
        cout << "\n2. Desplegar Registro de Salarios";
        cout << "\n3. Volver al Menú Anterior";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: registroNomina(); break;               // Ir a registro de nómina
            case 2: desplegarRegistroSalarios(); break;    // Ir a visualización de salarios
            case 3: limpiarPantalla(); return;             // Salir del menú
            default:
                cout << "\n¡Opción inválida!";
                pausar();
        }
    } while (true);
}

// Registra el pago de nómina de un empleado
void Contabilidad::registroNomina() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== REGISTRO DE PAGO ===";
    cout << "\nIngrese el código del empleado: ";
    getline(cin, codigo);

    ifstream archivo("empleados.txt");
    string linea;
    bool encontrado = false;

    // Buscar al empleado por código en el archivo empleados.txt
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

            // Confirmar si el pago fue realizado
            char respuesta;
            cout << "\n¿Se ha realizado el pago? (Y/N): ";
            cin >> respuesta;
            cin.ignore();

            // Guardar el resultado en pagos.txt
            ofstream archivoPagos("pagos.txt", ios::app);
            archivoPagos << codigoArchivo << "," << (toupper(respuesta) == 'Y' ? "Sí" : "No") << "\n";
            archivoPagos.close();

            cout << "\n¡Registro guardado!";
            break;
        }
    }

    // Mostrar mensaje si no se encontró al empleado
    if (!encontrado) {
        cout << "\n¡Empleado no encontrado!";
    }

    // Registrar acción en la bitácora
    bitacoralogContabilidad.insertar(usuario, 4401, "Contabilidad", "Registro Nomina");

    pausar();
}

// Muestra el registro completo de salarios
void Contabilidad::desplegarRegistroSalarios() {
    limpiarPantalla();

    ifstream empleados("empleados.txt");
    ifstream pagos("pagos.txt");
    ofstream salarios("salarios.txt");

    vector<string> codigosPagados;
    string lineaPago;

    // Leer pagos y guardar los códigos pagados
    while (getline(pagos, lineaPago)) {
        stringstream ss(lineaPago);
        string codigo, estado;
        getline(ss, codigo, ',');
        getline(ss, estado);
        codigosPagados.push_back(codigo);
    }

    // Escribir encabezados en el archivo salarios.txt
    salarios << left << setw(30) << "NOMBRE"
             << setw(15) << "CODIGO"
             << setw(10) << "PAGADO" << "\n";

    string lineaEmpleado;

    // Leer empleados y verificar si han sido pagados
    while (getline(empleados, lineaEmpleado)) {
        stringstream ss(lineaEmpleado);
        string nombre, telefono, codigo, direccion, salario;

        getline(ss, nombre, ',');
        getline(ss, telefono, ',');
        getline(ss, codigo, ',');
        getline(ss, direccion, ',');
        getline(ss, salario);

        string estado = "No";
        if (find(codigosPagados.begin(), codigosPagados.end(), codigo) != codigosPagados.end()) {
            estado = "Si";
        }

        // Escribir el registro con alineación
        salarios << left << setw(30) << nombre
                 << setw(15) << codigo
                 << setw(10) << estado << "\n";
    }

    salarios.close();

    // Mostrar el contenido de salarios.txt en pantalla
    ifstream archivoSalarios("salarios.txt");
    cout << "\n=== REGISTRO DE SALARIOS ===\n";

    string linea;
    while (getline(archivoSalarios, linea)) {
        cout << linea << "\n";
    }

    pausar();

    // Registrar acción en la bitácora
    bitacoralogContabilidad.insertar(usuario, 4402, "Contabilidad", "Desplegar registro nomina");
}
