//Programaddo por Priscila Sarai Guzmán Calgua 9959-23-450
#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string nombreUsuario;  // Almacena el nombre de usuario
    std::string contrasena;     // Almacena la contraseña del usuario
    static const std::string ARCHIVO_LOGIN; // Declaración

public:
    // Constructor por defecto
    // Inicializa el nombre de usuario y la contraseña como cadenas vacías
    Usuario();

    // Constructor con parámetros
    // Inicializa el nombre de usuario y la contraseña con los valores proporcionados
    Usuario(const std::string& usuario, const std::string& contrasena);

    // Método para obtener el nombre de usuario
    // Devuelve el nombre del usuario
    std::string getNombreUsuario() const;

    // Método para obtener la contraseña
    // Devuelve la contraseña del usuario
    std::string getContrasena() const;

    // Método para establecer (modificar) el nombre de usuario
    // Recibe un nuevo nombre de usuario y lo asigna
    void setNombreUsuario(const std::string& usuario);

    // Método para establecer (modificar) la contraseña
    // Recibe una nueva contraseña y la asigna
    void setContrasena(const std::string& contrasena);

    // Método que verifica si el nombre de usuario y la contraseña proporcionados son correctos
    // Compara los valores proporcionados con los almacenados en el objeto
    bool autenticar(const std::string& usuario, const std::string& contrasena) const;

    // Métodos estáticos para control de acceso (no dependen de un objeto)

    // Inicia sesión verificando los datos desde el archivo "login.txt"
    // Retorna true si la autenticación es exitosa, de lo contrario false
    static bool iniciarSesion();

    // Registra un nuevo usuario en el archivo "login.txt"
    // Recibe el nombre de usuario y la contraseña y los guarda en el archivo
    // Retorna true si el registro es exitoso, de lo contrario false
    static bool registrarUsuario();

    // Muestra el menú de autenticación (iniciar sesión o registrar nuevo usuario)
    // Devuelve true si se inicia sesión correctamente, false si se cancela
    static bool menuAutenticacion();

    // Método para hacer una pausa y esperar que el usuario presione Enter para continuar
    // Esto ayuda a hacer la interfaz más interactiva
    static void pausar();
    static void limpiarPantalla();

    // Función para autenticar desde el archivo
    static bool autenticarDesdeArchivo();


};

#endif

