#include "usuarios.h"

#include <fstream>
#include<cstdlib>
#include<conio.h>
#include<iostream>

#include "bitacora.h"
using namespace std;

usuarios::usuarios()
{
    //ctor
}

usuarios::~usuarios()
{
    //dtor
}

bool usuarios::loginUsuarios(){
    string usuario, contra;
    int intentosIngreso=0;
    bool ingresa=false;

    do{
        cout<<"\n\t\t-------------------------"<<endl;
        cout<<"\t\t   INGRESO DE USUARIOS   "<<endl;
        cout<<"\t\t-------------------------"<<endl<<endl;

        cout<<"\t\tUsuario: ";
        getline(cin, usuario);

        cout<<"\n\t\tContraseña: ";
        char caracter;
        caracter=getch();
        contra="";

        while (caracter != 13)
        {
            if (caracter !=8){
                contra.push_back(caracter);
                cout<<"*";
            }
            else{
                if (contra.length() > 0){
                    cout<<"\b \b";
                    contra=contra.substr(0,contra.length() -1);
                }
            }
            caracter = getch();
        }

        if (buscar(usuario, contra)){
            ingresa=true;
        }
        else{
            cout << "\n\t\tEl Usuario y/o contraseña son incorrectos"<<endl;
            cin.get(); //PREGUNTAR AL PROFE
            intentosIngreso++;
        }

    }while (ingresa==false && intentosIngreso<3);


    if (ingresa == false){
        cout<<"\t\t\nIngreso denegado...\n\t\tUsuario y/o contraseña invalidos.Intentos agotados"<<endl;
        bitacora auditoria;
        auditoria.insertar("usuario", "100", "LOGF");
        cin.get();
    }
    else{
        cout<< "\t\t\n\nINGRESANDO AL SISTEMA..."<<endl;
        bitacora auditoria;
        auditoria.insertar("usuario","100", "LOGS");
        name=usuario;
        cin.get();
    }

    return ingresa;
}

bool usuarios::registrarUsuario() {
    string nuevoId, nuevoNombre, nuevaContra;

    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t   REGISTRO DE USUARIO   " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    cout << "\t\tIngrese ID: ";
    getline(cin, nuevoId);

    cout << "\t\tIngrese Nombre: ";
    getline(cin, nuevoNombre);

     cout << "\t\tIngrese Contraseña: ";
    char caracter;
    caracter = getch();
    nuevaContra = "";
    while (caracter != 13) {
        if (caracter != 8) {
            nuevaContra.push_back(caracter);
            cout << "*";
        }
        else {
            if (nuevaContra.length() > 0) {
                cout << "\b \b";
                nuevaContra = nuevaContra.substr(0, nuevaContra.length() - 1);
            }
        }
        caracter = getch();
    }

    fstream file;
    file.open("Usuarios.txt", ios::app); // Abre el archivo en modo append

    if (!file) {
        // Si el archivo no existe, lo crea
        file.open("Usuarios.txt", ios::out);
        if (!file) {
            cout << "\n\t\tError al crear el archivo." << endl;
            system("pause");
            return false;
        }
    }

    // Escribir el nuevo usuario
    file << nuevoId << "        " << nuevoNombre << "       " << nuevaContra << "       " << endl;

    file.close();
    cout << "\n\n\t\tUsuario registrado exitosamente!" << endl;
    system("pause");
    return true;
}
bool usuarios::buscar(string user, string passw){
    cout <<"\n\n\t\tBUSCANDO... "<< endl;
    fstream file;
    int encontrados=0;
    file.open("Usuarios.txt", ios::in);

    if (!file){
		cout<<"\n-------------------------Datos de la Persona buscada------------------------"<<endl;
		cout<<"\n\t\t\tNo hay informacion...";
		system("pause");
		return false; //si no existe el archivo
    }
    else{
        file >> id >> name >> pass;
        while (!file.eof()){
            if (user==name){
                if(passw==pass){
                    encontrados++;
                }
            }
            file >> id >> name >> pass;
        }
        if (encontrados==0){
            return false;
        }else{
            return true;
        }
        file.close();
    }
}
string usuarios::getNombre()
{
    return name;
}
void usuarios::setNombre(string nombre)
{
    name=nombre;
}
