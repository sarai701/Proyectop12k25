#include "envios.h"
 #include <iostream>
 using namespace std;

 extern usuarios usuarioRegistrado;
 extern bitacora auditoria;

 void Envios::gestionEnvios() {
     int opcion;
     do {
         system("cls");
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

         switch(opcion) {
             case 1: generarGuia(); break;
             //case 2: asignarTransportista(); break;
             //case 3: rastrearEnvio(); break;
             //case 4: confirmarEntrega(); break;
             //case 5: break;
             default: cout << "\n\t\tOpcion invalida!"; cin.get();
         }
     } while(opcion != 5);
 }

 void Envios::generarGuia() {
     cout << "\n\t\t[Generando guia de envio...]" << endl;
     auditoria.insertar(usuarioRegistrado.getNombre(), "300", "GUIA");
     system("pause");
 }
 // Implementar demás funciones...
