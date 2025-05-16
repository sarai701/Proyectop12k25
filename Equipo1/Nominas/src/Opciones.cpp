#include "Opciones.h"
#include "bitacora.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include "usuarios.h"
#include "Prestaciones.h"
#include "Empleados.h"
using namespace std;
bitacora Bitacora;
Prestaciones show;//objeto para llamar metodo menú general sobre prestaciones
Empleados mantenimiento;


void Opciones::menu()//Metodo de despliegue del menu-ANGEL ROQUEL
{
    int opciones;
    bool repetir = true;
    do
    {
        system("cls");
        cout<<"\n\n\t\tMenu General"<<endl;
        cout<<"\t --------------------"<<endl;
        cout<<"\t 1. Archivo: "<<endl;
        cout<<"\t 2. Catalogos: "<<endl;
        cout<<"\t 3. Procesos: "<<endl;
        cout<<"\t 4. Informes: "<<endl;
        cout<<"\t 5. Bitacora: "<<endl;
        cout<<"\t 6. Regresar: "<<endl;
        cout<<"\t 7. Salir sistema: "<<endl;
        cin>>opciones;
        switch (opciones)
        {
        case 1:
            {

            }
            break;
        case 2:
            {
             mantenimiento.menuEmpleados();
            }
            break;
        case 3:
            {
            show.MostrarMenu();
            }
            break;
        case 4:
            {

            }
            break;
        case 5:
            {
                Bitacora.menu();
            }
            break;
        case 6:
            repetir=false;
            break;
        case 7:
            {
            repetir=false;
            exit(0);
            }
            break;
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
	}
    }while(repetir);
}
