//Definicion de la clase catalogos

#include "catalogos.h"
#include "cliente.h"
#include "proveedor.h"
#include "acreedor.h"

#include <iostream>
using namespace std;

//Declaracion de objetos
cliente clientes;
proveedor proveedores;
acreedor acreedores;

Catalogos::Catalogos()
{
    //ctor
}

void Catalogos::menuCatalogos(){
    int opciones;
    do{
        system("cls"); // Limpia la pantalla
        cout << "\n\n\t\tMenu de Catalogos" << endl;
        cout << "\t\t------------------------" << endl;
        cout << "\t\t1. Catalogo de Clientes" << endl;
        cout << "\t\t2. Catalogo de Proveedores" << endl;
        cout << "\t\t3. Catalogo de Acreedores" << endl;
        cout << "\t\t4. Volver al menu principal" << endl;

        cout<<"\t\t Opcion a escoger:[1/2/3/4]"<<endl;
        cout << "\n\t\t Ingrese una opcion: ";
        cin >> opciones;

        switch (opciones) {
            case 1:
                clientes.menu();
                break;
            case 2:
                proveedores.menu();
                break;
            case 3:
                acreedores.menu();
                break;
            case 4:
                break;
            default:
                cout << "n\t\tOpción no válida. Intente de nuevo" << endl;
                system("pause");
        }
    } while (opciones != 4); // Repite el menú hasta que el usuario quiera salir
}
