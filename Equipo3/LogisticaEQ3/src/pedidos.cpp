#include "pedidos.h"
 #include <iostream>
 using namespace std;

 extern usuarios usuarioRegistrado;
 extern bitacora auditoria;

 void Pedidos::gestionPedidos() {
     int opcion;
     do {
         system("cls");
         cout << "\t\t========================================" << endl;
         cout << "\t\t| GESTION DE PEDIDOS - LOGISTICA       |" << endl;
         cout << "\t\t========================================" << endl;
         cout << "\t\t 1. Crear nuevo pedido" << endl;
         cout << "\t\t 2. Consultar pedidos" << endl;
         cout << "\t\t 3. Modificar pedido" << endl;
         cout << "\t\t 4. Cancelar pedido" << endl;
         cout << "\t\t 5. Historial de pedidos" << endl;
         cout << "\t\t 6. Volver al menu anterior" << endl;
         cout << "\t\t========================================" << endl;
         cout << "\t\tOpcion a escoger: ";
         cin >> opcion;

         switch(opcion) {
             case 1: crearPedido(); break;
             case 2: consultarPedidos(); break;
             //case 3: modificarPedido(); break;
             //case 4: cancelarPedido(); break;
             //case 5: verHistorial(); break;
             case 6: break;
             default: cout << "\n\t\tOpcion invalida!"; cin.get();
         }
     } while(opcion != 6);
 }

 void Pedidos::crearPedido() {
     cout << "\n\t\t[Creando nuevo pedido...]" << endl;
     auditoria.insertar(usuarioRegistrado.getNombre(), "100", "NEWPED");
     system("pause");
 }

  void Pedidos::consultarPedidos() {
     cout << "\n\t\t[Consultando nuevo pedido...]" << endl;
     auditoria.insertar(usuarioRegistrado.getNombre(), "100", "NEWPED");
     system("pause");
 }

  void Pedidos::modificarPedido() {
     cout << "\n\t\t[Modificando pedido...]" << endl;
     auditoria.insertar(usuarioRegistrado.getNombre(), "100", "NEWPED");
     system("pause");
 }

  void Pedidos::cancelarPedido() {
     cout << "\n\t\t[Cancelando pedido...]" << endl;
     auditoria.insertar(usuarioRegistrado.getNombre(), "100", "NEWPED");
     system("pause");
 }

  void Pedidos::verHistorial() {
     cout << "\n\t\t[Viendo el Historial de pedidos...]" << endl;
     auditoria.insertar(usuarioRegistrado.getNombre(), "100", "NEWPED");
     system("pause");
 }
