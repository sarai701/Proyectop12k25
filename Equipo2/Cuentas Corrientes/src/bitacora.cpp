//Documentado por Britany Hernandez 10/05/2025 9959-24-4178
//Implementacion de la bitacora para el registro y visualizacion de acciones realizadas
#include "bitacora.h"

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include <ctime>

using namespace std;
using namespace std;
//Constructor de la clase
bitacora::bitacora()
{
    //ctor
}
//Menu principal para la gestion de la bitacora
void bitacora::menu(){
    int choice;
    char x;
    //Ciclo que muestra el menu hasta que se elija salir
    do{
        system("cls");
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t |   SISTEMA GESTION BITACORA  |"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t 1. Despliegue Bitacora"<<endl;
        cout<<"\t\t\t 2. Exit"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tOpcion a escoger:[1/2]"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tIngresa tu Opcion: ";
        cin>>choice;

        switch (choice){
        case 1:
            desplegar();
            break;
        case 2:
            break;
        default:
            cout <<"\n\t\t\t Opccion invalida intente denuevo...";
            system("pause");
        }
    }while (choice !=2);
}

//Se encarga de llevar el registro de acciones que se realizan insertando un nuevo registro
//Toma como parametros el nombre del usuario registrado, su aplicacion y  la accion realizada
void bitacora::insertar(string nombre, string aplicacion, string accion){
    system("cls");
    fstream file;
    file.open("bitacora.txt", ios::app | ios::out);//Abre o crea el archivo bitacora

    //Se obtiene la fecha y la hora en que se realize la accion
    time_t now =time(0);
    tm* ltm = localtime(&now);
    char dt[30];
    strftime(dt, sizeof(dt), "%m-%d-%Y %I:%M %p", ltm);// Formato: mm-dd-yyyy hh:mm AM/PM

    //Acrear al archivo
    file<<left<<setw(15)<<nombre<<left<<setw(15)<<aplicacion
        <<left<<setw(15)<<accion<<dt<<"\n";
    file.close();
}
//Muestra todos los registros de la bitacora
void bitacora::desplegar(){

    system("cls");
    fstream file;
    int total=0;
	cout<<"\n-------------------------Tabla de Detalles de Bitacora -------------------------"<<endl;
	file.open("bitacora.txt", ios::in); //Apertura el archivo bitacore solo para lectura

	if(!file){
	    cout<<"\n\t\t\tNo hay informacion.."; //Mensaje si el archivo esta vacio o no existe
	    file.close();
	}
	else{
        cout << left << setw(15) << "Nombre" << setw(15) << "Aplicacion"  << setw(15) << "accion"
        << setw(15) << "Fecha y hora"<< endl;
        cout << "------------------------------------------------------------------------------\n";
        //Ciclo para desplegar los registros en la bitacora
        while (file >> nombre >> aplicacion >> accion){
            total++;
            //Se usa gerline para leer la fecha con espacios y para que salga completa
            getline(file,fecha);
            cout << left << setw(15) << nombre << setw(15) << aplicacion  << setw(15)
            << accion << fecha << endl;
        }

        if (total==0){
            cout <<"\n\t\t\t No hay informacion...";
        }
	}
	system("pause");
	file.close();
}
