//Jonathan Samuel Gonzalez Ixpata
#include "Auditoria.h"
#include <iostream>       // Para entrada y salida estándar
#include <fstream>        // Para leer y escribir archivos
#include "Bitacora.h"     // Para registrar acciones en la bitácora

#ifdef _WIN32
#include <cstdlib>        // Para usar system("cls") en Windows
#endif

Bitacora bitacoralogAuditoria;    // Objeto global para registrar acciones en la bitácora
using namespace std;

// Función para limpiar la pantalla dependiendo del sistema operativo
void Auditoria::limpiarPantalla() {
#ifdef _WIN32
    system("cls");        // Limpia la pantalla en Windows
#else
    system("clear");      // Limpia la pantalla en Linux o Mac
#endif
}

// Función para pausar el programa hasta que el usuario presione ENTER
void Auditoria::pausar() {
    cout << "\nPresione ENTER para continuar...";  // Mensaje para el usuario
    cin.ignore();        // Ignora entrada previa
    cin.get();           // Espera a que el usuario presione ENTER
}

void Auditoria::setUsuario(const string& u) {
    usuario = u;
}

// Menú principal de Auditoría
void Auditoria::menuAuditoria() {
    int opcion;          // Variable para almacenar la opción del usuario
    do {
        limpiarPantalla();    // Limpia pantalla antes de mostrar el menú
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MENÚ DE AUDITORÍA =====";
        cout << "\n1. Gestión de Auditores";
        cout << "\n2. Registros Realizados";
        cout << "\n3. Volver al menú anterior";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;        // Lee la opción del usuario
        cin.ignore();         // Limpia el buffer

        switch (opcion) {
            case 1: submenuAuditor(); break;             // Ir al submenú de auditores
            case 2: registrosRealizados(); break;        // Mostrar registros de auditoría
            case 3: limpiarPantalla(); return;           // Volver al menú anterior
            default:
                cout << "\n¡Opción inválida!";           // Mensaje de error
                pausar();                                // Pausar para que el usuario vea el mensaje
        }
    } while (true);      // Bucle infinito hasta que se seleccione la opción 3
}

// Submenú para gestionar auditores
void Auditoria::submenuAuditor() {
    int opcion;          // Variable para almacenar la opción del usuario
    do {
        limpiarPantalla();    // Limpia pantalla antes de mostrar el submenú
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== GESTIÓN DE AUDITORES =====";
        cout << "\n1. Registrar Auditor";
        cout << "\n2. Borrar Auditor";
        cout << "\n3. Desplegar Auditores";
        cout << "\n4. Volver";
        cout << "\nSeleccione: ";
        cin >> opcion;        // Lee la opción del usuario
        cin.ignore();         // Limpia el buffer

        switch (opcion) {
            case 1: registrarAuditor(); break;           // Registrar un nuevo auditor
            case 2: borrarAuditor(); break;              // Eliminar un auditor existente
            case 3: despliegueAuditores(); break;        // Mostrar la lista de auditores
            case 4: limpiarPantalla(); return;           // Volver al menú anterior
            default:
                cout << "\n¡Opción inválida!";           // Mensaje de error
                pausar();                                // Pausar para que el usuario vea el mensaje
        }
    } while (true);      // Bucle infinito hasta que se seleccione la opción 4
}

// Registrar nuevo auditor
void Auditoria::registrarAuditor() {
    limpiarPantalla();           // Limpia la pantalla
    Auditores a;                 // Crear objeto auditor

    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== REGISTRAR AUDITOR ===";
    cout << "\nNombre: ";
    getline(cin, a.nombre);      // Leer nombre del auditor
    cout << "Código: ";
    getline(cin, a.codigo);      // Leer código del auditor

    auditores.push_back(a);      // Agregar auditor al vector

    ofstream archivo("auditores.txt", ios::app);   // Abrir archivo para agregar datos
    archivo << a.nombre << "," << a.codigo << "\n"; // Escribir datos en el archivo
    archivo.close();              // Cerrar archivo

    cout << "\n¡Auditor registrado!";              // Confirmación
    bitacoralogAuditoria.insertar(usuario, 4301, "Auditoria", "Registrar"); // Registrar acción en bitácora
    pausar();                      // Esperar al usuario
}

// Borrar auditor por código
void Auditoria::borrarAuditor() {
    limpiarPantalla();            // Limpia la pantalla
    string codigo;                // Variable para almacenar el código
    cout << "\n=== BORRAR AUDITOR ===";
    cout << "\nCódigo del auditor: ";
    getline(cin, codigo);         // Leer código del auditor

    vector<Auditores> nuevaLista; // Lista temporal para los que no serán eliminados
    bool eliminado = false;       // Bandera para saber si se eliminó un auditor

    for (const auto& a : auditores) {
        if (a.codigo != codigo) {
            nuevaLista.push_back(a);  // Mantener auditores que no coincidan
        } else {
            eliminado = true;         // Se encontró y eliminó el auditor
        }
    }

    if (eliminado) {
        auditores = nuevaLista;      // Reemplazar lista original con la nueva
        ofstream archivo("auditores.txt");  // Reescribir el archivo completo
        for (const auto& a : auditores) {
            archivo << a.nombre << "," << a.codigo << "\n"; // Escribir auditor no eliminado
        }
        archivo.close();             // Cerrar archivo
        cout << "\n¡Auditor eliminado!";    // Confirmación
    } else {
        cout << "\n¡Código no encontrado!"; // Mensaje si no se encuentra el código
    }

    bitacoralogAuditoria.insertar(usuario, 4302, "Auditoria", "Borrar"); // Registrar acción en bitácora
    pausar();                    // Esperar al usuario
}

// Mostrar todos los auditores
void Auditoria::despliegueAuditores() {
    limpiarPantalla();           // Limpia la pantalla
    ifstream archivo("auditores.txt");   // Abrir archivo de auditores

    cout << "\n=== LISTA DE AUDITORES ===";
    cout << "\nNombre\t\tCódigo\n";

    string linea;                // Variable para leer línea del archivo
    while (getline(archivo, linea)) {
        size_t pos = linea.find(",");       // Buscar posición de la coma
        string nombre = linea.substr(0, pos);  // Extraer nombre
        string codigo = linea.substr(pos + 1); // Extraer código

        cout << nombre << "\t\t" << codigo << "\n";  // Mostrar datos
    }

    archivo.close();             // Cerrar archivo
    bitacoralogAuditoria.insertar(usuario, 4303, "Auditoria", "Desplegar"); // Registrar acción en bitácora
    pausar();                    // Esperar al usuario
}

// Tabla genérica de registros
void Auditoria::registrosRealizados() {
    limpiarPantalla();           // Limpia la pantalla
    cout << "\n=== REGISTROS DE AUDITORÍA ===";
    cout << "\nFecha\t\tAcción\t\tUsuario";
    cout << "\n2023-10-01\tRevisión\tAuditor1";       // Registro de ejemplo
    cout << "\n2023-10-02\tVerificación\tAuditor2";    // Registro de ejemplo
    bitacoralogAuditoria.insertar(usuario, 4304, "Auditoria", "registrosRealizados"); // Registrar acción en bitácora
    pausar();                    // Esperar al usuario
}
