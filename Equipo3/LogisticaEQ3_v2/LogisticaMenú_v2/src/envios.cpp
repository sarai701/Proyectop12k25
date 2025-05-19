#include "envios.h"       // Inclusión del archivo de cabecera de la clase Envios
#include <iostream>       // Para operaciones de entrada y salida
#include "transportistas.h"

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
//            case 2: asignarTransportista(); break;
//            case 3: rastrearEnvio(); break;
  //          case 4: confirmarEntrega(); break;
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
    //auditoria.insertar(usuarioRegistrado.getNombre(), "300", "GUIA"); // Código 300 para guía
    system("pause");
}

void Envios::crearEnvio(const std::string& idPedido,
                       const std::vector<Transportistas>& transportistas) {
    // Implementación para crear un envío
    // Por ejemplo:
    std::ofstream archivo("envios.dat", std::ios::app);
    if (archivo.is_open()) {
        archivo << "Pedido: " << idPedido << " - Transportistas asignados: ";
        for (const auto& t : transportistas) {
            archivo << t.id << " ";
        }
        archivo << "\n";
        archivo.close();
    }
}
