#include "bitacora.h"

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<conio.h>
#include<iomanip>

using namespace std;

bitacora::bitacora()
{
    //ctor
}

void bitacora::menu(){
    int choice;
    char x;
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
            cin.get();
        }
    }while (choice !=2);
}

//Se encarga de llevar el registro de acciones que se realizan
void bitacora::insertar(string nombre, string aplicacion, string accion){
    system("cls");
    fstream file;
    file.open("bitacora.txt", ios::app | ios::out);
    file<<left<<setw(15)<<nombre<<left<<setw(15)<<aplicacion<<left<<setw(15)<<accion<<"\n";
    file.close();
}

void bitacora::desplegar(){

    system("cls");
    fstream file;
    int total=0;
	cout<<"\n-------------------------Tabla de Detalles de Bitacora -------------------------"<<endl;
	file.open("bitacora.txt", ios::in);

	if(!file){
	    cout<<"\n\t\t\tNo hay informacion..";
	    file.close();
	}
	else{
        file >> nombre >> aplicacion >> accion;
        while (!file.eof()){
            total++;
            cout <<"\n\n\t\t\t Nombre Usuario: " << nombre<<endl;
            cout <<"\t\t\t No. Aplicacion: " <<aplicacion<<endl;
            cout <<"\t\t\t Accion Realizada: "<< accion<< endl;

            file >> nombre >> aplicacion >> accion;
        }

        if (total==0){
            cout <<"\n\t\t\t No hay informacion...";
        }
        system("cls");
	}
	file.close();
}
