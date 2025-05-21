// Programado por Priscila Sarai Guzmán Calgua 9959-23-450
#ifndef USUARIO_H
#define USUARIO_H

#include "Bitacora.h"
#include <string>
using namespace std;

// Estructura fija para el almacenamiento binario de usuarios
struct RegistroUsuario {
    char nombreUsuario[30];
    char contrasena[30];
};

class Usuario {
private:
    string usuario;               // Usuario autenticado (para bitácora)
    string nombreUsuario;         // Almacena el nombre de usuario
    string contrasena;            // Almacena la contraseña del usuario
    static const string ARCHIVO_LOGIN; // Nombre del archivo binario login.dat

public:
    void setUsuario(const string& u); // Establece el usuario autenticado (bitácora)

    // Constructor por defecto
    Usuario();

    // Constructor con parámetros
    Usuario(const string& usuario, const string& contrasena);

    // Obtiene el nombre del usuario
    string getNombreUsuario() const;

    // Obtiene la contraseña del usuario
    string getContrasena() const;

    // Establece/modifica el nombre de usuario
    void setNombreUsuario(const string& usuario);

    // Establece/modifica la contraseña
    void setContrasena(const string& contrasena);

    // Verifica si usuario y contraseña coinciden con los almacenados en el objeto
    bool autenticar(const string& usuario, const string& contrasena) const;

    // Autenticación directa desde archivo binario login.dat
    bool autenticarDesdeArchivo(string& usuarioAutenticado);

    // Inicia sesión verificando desde archivo binario login.dat
    bool iniciarSesion();

    // Registra nuevo usuario en archivo binario login.dat
    string registrarUsuario();

    // Muestra menú de autenticación
    bool menuAutenticacion(string& usuarioAutenticado);

    // Espera que el usuario presione Enter para continuar
    void pausar();

    // Limpia pantalla (multiplataforma)
    static void limpiarPantalla();
};

#endif
