#include "usuario.h"
#include "bitacora.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>

using namespace std;

const string Usuario::ARCHIVO_USUARIOS = "usuarios.dat";
const char XOR_KEY = 0x55; // Clave XOR para encriptación simple

bool isShiftPressed() {
    return (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
}

void aplicarXOR(string& data) {
    transform(data.begin(), data.end(), data.begin(),
        [](char c) { return c ^ XOR_KEY; });
}

string Usuario::leerContrasenaOculta(bool mostrarCaracter, char caracterOculto) {
    string contrasena;
    char ch;
    bool revelar = false;

    while ((ch = _getch()) != '\r' && ch != '\n') {
        bool shiftActual = isShiftPressed();
        if (shiftActual != revelar) {
            revelar = shiftActual;
            cout << string(contrasena.length(), '\b') << flush;
            cout << (revelar ? contrasena : string(contrasena.length(), caracterOculto)) << flush;
            continue;
        }

        if (ch == '\b') {
            if (!contrasena.empty()) {
                contrasena.pop_back();
                cout << "\b \b" << flush;
            }
        }
        else if (isprint(ch)) {
            contrasena += ch;
            cout << (revelar || mostrarCaracter ? ch : caracterOculto) << flush;
        }
    }
    cout << endl;
    return contrasena;
}

bool Usuario::usuarioExiste(const string& usuario) {
    ifstream archivo(ARCHIVO_USUARIOS, ios::binary);
    if (!archivo) return false;

    string usuarioArchivo;
    size_t length;

    while (archivo.read(reinterpret_cast<char*>(&length), sizeof(size_t))) {
        usuarioArchivo.resize(length);
        archivo.read(&usuarioArchivo[0], length);
        aplicarXOR(usuarioArchivo);

        archivo.read(reinterpret_cast<char*>(&length), sizeof(size_t));
        archivo.ignore(length); // ignorar la contraseña

        if (usuarioArchivo == usuario) {
            return true;
        }
    }
    return false;
}

bool Usuario::registrarUsuario(const string& usuario, const string& contrasena) {
    if (usuarioExiste(usuario)) {
        cerr << "❌ El usuario ya existe\n";
        return false;
    }

    ofstream archivo(ARCHIVO_USUARIOS, ios::binary | ios::app);
    if (!archivo) {
        cerr << "❌ Error al abrir o crear el archivo de usuarios\n";
        Bitacora::registrarAccion(usuario, CodigosAccion::ERROR_ARCHIVO, "No se pudo abrir/crear el archivo de usuarios.");
        return false;
    }

    string usuarioEncriptado = usuario;
    string contrasenaEncriptada = contrasena;
    aplicarXOR(usuarioEncriptado);
    aplicarXOR(contrasenaEncriptada);

    size_t lenUsuario = usuarioEncriptado.size();
    size_t lenContrasena = contrasenaEncriptada.size();

    archivo.write(reinterpret_cast<const char*>(&lenUsuario), sizeof(size_t));
    archivo.write(usuarioEncriptado.c_str(), lenUsuario);

    archivo.write(reinterpret_cast<const char*>(&lenContrasena), sizeof(size_t));
    archivo.write(contrasenaEncriptada.c_str(), lenContrasena);

    cout << "✔ Usuario registrado exitosamente\n";
    Bitacora::registrarAccion(usuario, CodigosAccion::CREACION_CLIENTE, "Nuevo usuario registrado.");
    return true;
}

bool Usuario::iniciarSesion(const string& usuario, const string& contrasena) {
    ifstream archivo(ARCHIVO_USUARIOS, ios::binary);
    if (!archivo) {
        Bitacora::registrarAccion(usuario, CodigosAccion::ERROR_ARCHIVO, "Archivo de usuarios no accesible.");
        return false;
    }

    string usuarioArchivo, contrasenaArchivo;
    size_t length;

    while (archivo.read(reinterpret_cast<char*>(&length), sizeof(size_t))) {
        usuarioArchivo.resize(length);
        archivo.read(&usuarioArchivo[0], length);
        aplicarXOR(usuarioArchivo);

        archivo.read(reinterpret_cast<char*>(&length), sizeof(size_t));
        contrasenaArchivo.resize(length);
        archivo.read(&contrasenaArchivo[0], length);
        aplicarXOR(contrasenaArchivo);

        if (usuarioArchivo == usuario && contrasenaArchivo == contrasena) {
            Bitacora::registrarAccion(usuario, CodigosAccion::LOGIN_EXITOSO, "Inicio de sesión correcto.");
            return true;
        }
    }

    Bitacora::registrarAccion(usuario, CodigosAccion::LOGIN_FALLIDO, "Intento fallido de inicio de sesión.");
    return false;
}
