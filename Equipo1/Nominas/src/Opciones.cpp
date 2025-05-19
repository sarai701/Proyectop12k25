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
Empleados mantenimiento;


void Opciones::menu()//Metodo de despliegue del menu-ANGEL ROQUEL
{
    int opciones;
    bool repetir = true;
    do
    {
        system("cls");
        cout<<"\n\n\t      Menu General"<<endl;
        cout<<"\t ----------------------"<<endl;
        cout<<"\t | 1. Catalogos:      |"<<endl;
        cout<<"\t | 2. Procesos:       |"<<endl;
        //cout<<"\t 3. Informes: "<<endl;
        cout<<"\t | 3. Bitacora:       |"<<endl;
        cout<<"\t | 4. Regresar:       |"<<endl;
        cout<<"\t |                    |"<<endl;
        cout<<"\t | 5. Salir sistema:  |"<<endl;
        cout<<"\t ----------------------"<<endl<<endl;
        cout<<"   Ingrese opcion: ";
        cin>>opciones;
        switch (opciones)
        {
        case 1:
            {
            mantenimiento.menuEmpleados();
            }
            break;
        case 2:
            {
             mantenimiento.mostrarMenuNomina();
            }
            break;
        case 3:
            {
            Bitacora.menu();
            }
            break;
        case 4:
            {
            repetir=false;
            }
            break;
        case 5:
            {
            repetir=false;
            exit(0);
            }
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
	}
    }while(repetir);
}
