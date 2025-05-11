//Clase modificada por Astrid Ruíz 9/05/2025 9959 24 2976 - Se agregó todo el sistema de usuarios y backup
#include "usuarios.h"

#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <sstream>  // Agregado para procesar cada línea
#include "bitacora.h"
#include <limits> //para que se lea bien la limpiada del buffer de entrada
using namespace std;

usuarios::usuarios()
{
    //ctor
}

usuarios::~usuarios()
{
    //dtor
}

//INICIAN LOS CRUD

//Iniciar sesión de usuarios
bool usuarios::loginUsuarios(){
    string usuario, contra;
    int intentosIngreso=0;
    bool ingresa=false;

    do{
        system("cls");
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
            bitacora auditoria;
            auditoria.insertar("usuario", "100", "LOGF"); //log fallido
            cin.get();
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
        system("pause");
        bitacora auditoria;
        name=usuario;
        auditoria.insertar(name,"100", "LOGS");
        cin.get();
    }

    return ingresa;
}

//Registrar nuevo usuario
bool usuarios::registrarUsuario() {
    string nuevoId, nuevoNombre, nuevaContra;

    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t   REGISTRO DE USUARIO   " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    cout << "\t\tIngrese ID: ";
    cin.ignore();  // <--limpiar el buffer antes del getline
    getline(cin, nuevoId);

    cout << "\t\tIngrese Nombre: ";
    getline(cin, nuevoNombre);

    cout << "\t\tIngrese Contraseña: ";

    //contraseña ocualtado como en el login
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
    file << nuevoId << "|" << nuevoNombre << "|" << nuevaContra << endl;

    file.close();
    cout << "\n\n\t\tUsuario registrado exitosamente!" << endl;

    // Registrar en bitácora
    bitacora auditoria;
    auditoria.insertar(name, "100", "INSUS"); // insetar nuevo usuario

    return true;
}

//Consulta de todos los usuarios
//Lee y muestra los datos del archivo Usuarios.txt
bool usuarios::consultarUsuarios() {
    fstream file;
    string currentId, currentName, currentPass;
    int total = 0; // Contador para verificar si hay datos

    system("cls"); // Limpiar la pantalla al entrar
    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t LISTADO DE USUARIOS " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    //archivo en modo lectura
    file.open("Usuarios.txt", ios::in);
    if (!file) {
        cout << "\n\t\tNo hay información disponible de usuarios..." << endl;
        system("pause"); // Pausa la pantalla para que el usuario pueda leer el mensaje
        return false;
    }

    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        getline(ss, currentId, '|');
        getline(ss, currentName, '|');
        getline(ss, currentPass, '|');

        total++;
        cout << "\n\t\tID: " << currentId << endl;
        cout << "\t\tNombre: " << currentName << endl;
        cout << "\t\tContraseña: " << currentPass << endl;
    }
    system("pause"); // <-- Pausa para que se lean los mensajes

    file.close();

    if (total == 0) {
        cout << "\n\t\tNo hay usuarios registrados..." << endl;
    }

    // Registrar en bitácora
    bitacora auditoria;
    auditoria.insertar(name, "100", "SRCH"); //buscar usuario

    system("pause"); // Pausa para que el usuario vea la información
    return true;
}

//Modificar un usuario por medio del ID (Cambiar nombre y contraseña)
bool usuarios::modificarUsuario() {
    system("cls");
    fstream file, tempFile;
    string searchId;
    string currentId, currentName, currentPass;
    bool found = false;

    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t MODIFICACIÓN DE USUARIO " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    cout << "\t\tIngrese ID del usuario a modificar: ";
    cin.ignore();  // limpia el salto de línea pendiente
    getline(cin, searchId);

    file.open("Usuarios.txt", ios::in);
    if (!file) {
        cout << "\n\t\tNo hay información disponible..." << endl;
        return false;
    }

    //crear archivo temporal
    tempFile.open("Temp.txt", ios::out);

    string linea;
while (getline(file, linea)) {
    stringstream ss(linea);
    getline(ss, currentId, '|');
    getline(ss, currentName, '|');
    getline(ss, currentPass, '|');

    if (searchId == currentId) {
        found = true;

        cout << "\n\t\tDatos actuales:" << endl;
        cout << "\t\tID: " << currentId << endl;
        cout << "\t\tNombre: " << currentName << endl;
        cout << "\t\tContraseña: " << currentPass << endl << endl;

        string newName, newPass;
        cout << "\t\tNuevo nombre: ";
        getline(cin, newName);

        cout << "\t\tNueva contraseña: ";
        char caracter;
        newPass = "";
        caracter = getch();
        while (caracter != 13) {
            if (caracter != 8) {
                newPass.push_back(caracter);
                cout << "*";
            } else {
                if (!newPass.empty()) {
                    cout << "\b \b";
                    newPass.pop_back();
                }
            }
            caracter = getch();
        }

        tempFile << currentId << "|" << newName << "|" << newPass << endl;
        cout << "\n\n\t\tUsuario modificado exitosamente!" << endl;

        // Bitácora
        bitacora auditoria;
        auditoria.insertar(name, "100", "UPDUS");
    } else {
        tempFile << currentId << "|" << currentName << "|" << currentPass << endl;
    }
}
    file.close();
    tempFile.close();

    if (found) {
        remove("Usuarios.txt"); //borra archivo original
        rename("Temp.txt", "Usuarios.txt"); //Renombra temporal como original
        return true;
    }
    else {
        remove("Temp.txt"); //elimina temporal sin cambios
        cout << "\n\t\tNo se encontró el usuario con ID: " << searchId << endl;
        return false;
    }
}

//Eliminar usuario por ID
bool usuarios::eliminarUsuario() {
    system("cls");
    fstream file, tempFile;
    string searchId;
    string currentId, currentName, currentPass;
    bool found = false;

    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t ELIMINACIÓN DE USUARIO  " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    cout << "\t\tIngrese ID del usuario a eliminar: ";
    cin.ignore();
    getline(cin, searchId);

    file.open("Usuarios.txt", ios::in);
    if (!file) {
        cout << "\n\t\tNo hay información disponible..." << endl;
        return false;
    }
    //abrir archivo temporal
    tempFile.open("Temp.txt", ios::out);
    //leer datos del archivo original
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        getline(ss, currentId, '|');
        getline(ss, currentName, '|');
        getline(ss, currentPass, '|');

        if (searchId == currentId) {
            found = true;

            cout << "\n\t\tDatos del usuario a eliminar:" << endl;
            cout << "\t\tID: " << currentId << endl;
            cout << "\t\tNombre: " << currentName << endl;
            cout << "\t\tContraseña: " << currentPass << endl << endl;

            char confirmar;
            cout << "\t\t¿Está seguro de eliminar este usuario? (S/N): ";
            cin >> confirmar;
            cin.ignore();

            if (confirmar == 'S' || confirmar == 's') {
                cout << "\n\t\tUsuario eliminado exitosamente." << endl;
                // Bitácora
                bitacora auditoria;
                auditoria.insertar(name, "100", "DELUS");
            } else {
                tempFile << currentId << "|" << currentName << "|" << currentPass << endl;
                cout << "\n\t\tEliminación cancelada por el usuario." << endl;
            }

        } else {
            // Copia las líneas no modificadas
            tempFile << currentId << "|" << currentName << "|" << currentPass << endl;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("Usuarios.txt");
        rename("Temp.txt", "Usuarios.txt");
        return true;
    } else {
        remove("Temp.txt");
        cout << "\n\t\tNo se encontró el usuario con ID: " << searchId << endl;
        return false;
    }
}

//Realizando respaldo de usuarios
//Se copia todo el contenido de Usuarios.txt a BackupUsuarios.txt
bool usuarios::backupUsuarios() {
    system("cls");
    fstream file, backupFile;
    string linea;

    cout << "\n\t\t---------------------------------" << endl;
    cout << "\t\t  BACKUP DE USUARIOS   " << endl;
    cout << "\t\t---------------------------------" << endl << endl;

    file.open("Usuarios.txt", ios::in);
    if (!file) {
        cout << "\n\t\tNo hay información disponible para realizar el backup..." << endl;
        return false;
    }

    backupFile.open("Usuarios_Backup.txt", ios::out);
    if (!backupFile) {
        cout << "\n\t\tError al crear el archivo de backup." << endl;
        file.close();
        return false;
    }

    cout << "\n\t\tRealizando backup de datos..." << endl;

    // Copia línea por línea del archivo original al de backup
    while (getline(file, linea)) {
        backupFile << linea << endl;
    }

    file.close();
    backupFile.close();

    cout << "\n\t\tBackup realizado con éxito en 'Usuarios_Backup.txt'" << endl;

    // Registrar en bitácora
    bitacora auditoria;
    auditoria.insertar(name, "100", "BACK");

    return true;
}

bool usuarios::restaurarBackup() {
    system("cls");
    fstream backupFile, mainFile;
    string linea;

    cout << "\n\t\t---------------------------------" << endl;
    cout << "\t\t  RESTAURACIÓN DE BACKUP        " << endl;
    cout << "\t\t---------------------------------" << endl << endl;

    backupFile.open("Usuarios_Backup.txt", ios::in);
    if (!backupFile) {
        cout << "\n\t\tNo se encontró archivo de backup para restaurar..." << endl;
        return false;
    }

    mainFile.open("Usuarios.txt", ios::out);
    if (!mainFile) {
        cout << "\n\t\tError al abrir el archivo principal." << endl;
        backupFile.close();
        return false;
    }

    cout << "\n\t\tRestaurando datos del backup..." << endl;

    while (getline(backupFile, linea)) {
        mainFile << linea << endl;
    }
    backupFile.close();
    mainFile.close();

    cout << "\n\t\tRestauración completada con éxito!" << endl;

    // Registrar en bitácora
    bitacora auditoria;
    auditoria.insertar(name, "100", "RESTBC");

    return true;
}

bool usuarios::buscar(string user, string passw) {
    fstream file;
    file.open("Usuarios.txt", ios::in);

    if (!file) {
        cout << "\n\t\tNo hay información de usuarios disponible..." << endl;
        return false;
    }

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        string tempId, tempName, tempPass;

        getline(iss, tempId, '|');
        getline(iss, tempName, '|');
        getline(iss, tempPass, '|');

        if (user == tempName && passw == tempPass) {
            id = tempId;
            name = tempName;
            pass = tempPass;
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


string usuarios::getNombre()
{
    return name;
}

void usuarios::setNombre(string nombre)
{
    name = nombre;
}
