#include "envios.h"       // Inclusión del archivo de cabecera de la clase Envios
#include <iostream>       // Para operaciones de entrada y salida
using namespace std;

//JENNIFER BARRIOS COORD EQUIPO 3
//9959-24-10016
//MAYO 2025

// Declaraciones externas para acceder a las variables globales
extern usuarios usuarioRegistrado;  // Usuario actualmente autenticado
extern bitacora auditoria;          // Sistema de auditoría para registrar acciones

// Método principal de la clase 'Envios' para gestionar funciones relacionadas a la logística de envíos
void Envios::gestionEnvios() {
    int opcion;
    do {
        // Limpia la consola (funciona en sistemas Windows)
        system("cls");

        // Muestra el menú principal de gestión de envíos
        cout << "\t\t========================================" << endl;
        cout << "\t\t| GESTION DE ENVIOS - LOGISTICA        |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Generar guia de envio" << endl;
        cout << "\t\t 2. Asignar transportista" << endl;
        cout << "\t\t 3. Rastrear envio" << endl;
        cout << "\t\t 4. Confirmar entrega" << endl;
        cout << "\t\t 5. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";
        cin >> opcion;

        // Ejecuta la acción correspondiente a la opción elegida
        switch(opcion) {
            case 1: generarGuia(); break;
            case 2: asignarTransportista(); break;
            case 3: rastrearEnvio(); break;
            case 4: confirmarEntrega(); break;
            case 5: break; // Salir del menú
            default:
                cout << "\n\t\tOpcion invalida!";
                cin.get(); // Espera una tecla para continuar
        }
    } while(opcion != 5); // Repetir hasta que el usuario decida volver
}

// Genera una guía de envío y registra la acción en la bitácora
void Envios::generarGuia() {
    cout << "\n\t\t[Generando guia de envio...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "GUIA"); // Código 300 para guía
    system("pause");
}

// Asigna un transportista al envío y registra la acción
void Envios::asignarTransportista() {
    cout << "\n\t\t[Asignando a un transportista...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "301", "TRANSPORTISTA"); // Código 301 para asignación
    system("pause");
}

// Permite rastrear un envío y registra esta acción en la bitácora
void Envios::rastrearEnvio() {
    cout << "\n\t\t[Rastreando Envío...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "302", "RASTREO ENVIO"); // Código 302 para rastreo
    system("pause");
}

// Confirma que el envío ha sido entregado y lo registra en la bitácora
void Envios::confirmarEntrega() {
    cout << "\n\t\t[Entrega Confirmada...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "303", "CONFIRMACION DE ENTREGA"); // Código 303 para confirmación
    system("pause");
}
