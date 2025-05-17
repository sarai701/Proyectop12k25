#include "bitacora.h"
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

const string Bitacora::ARCHIVO_BITACORA = "bitacora.txt";
string Bitacora::usuarioActual = "";

const map<int, string> DESCRIPCIONES_CODIGOS = {
    // Autenticación
    {CodigosAccion::LOGIN_EXITOSO, "Inicio de sesión exitoso"},
    {CodigosAccion::LOGIN_FALLIDO, "Intento fallido de inicio de sesión"},
    {CodigosAccion::LOGOUT, "Cierre de sesión"},
    {CodigosAccion::BLOQUEO_USUARIO, "Usuario bloqueado"},
    {CodigosAccion::CAMBIO_CONTRASENA, "Cambio de contraseña"},

    // Operaciones CRUD
    {CodigosAccion::CREACION_CLIENTE, "Creación de nuevo cliente"},
    {CodigosAccion::LECTURA_CLIENTE, "Consulta de cliente"},
    {CodigosAccion::ACTUALIZACION_CLIENTE, "Actualización de cliente"},
    {CodigosAccion::ELIMINACION_CLIENTE, "Eliminación de cliente"},
    {CodigosAccion::CREACION_PRODUCTO, "Creación de producto"},
    {CodigosAccion::ACTUALIZACION_PRODUCTO, "Actualización de producto"},
    {CodigosAccion::ELIMINACION_PRODUCTO, "Eliminación de producto"},

    // Contraversia
    {CodigosAccion::SELECCION_FACUNDO, "Selección de Menú Facundo"},
    {CodigosAccion::SELECCION_TURQUE_SALUD, "Selección de Turque Salud"},

    // Archivos
    {CodigosAccion::RESPALDO_CREADO, "Respaldo de datos creado"},
    {CodigosAccion::RESTAURACION_COMPLETADA, "Datos restaurados desde respaldo"},
    {CodigosAccion::EXPORTACION_DATOS, "Exportación de datos"},

    // Errores
    {CodigosAccion::ERROR_SISTEMA, "Error del sistema"},
    {CodigosAccion::ERROR_ARCHIVO, "Error al acceder a archivo"},
    {CodigosAccion::ERROR_PERMISOS, "Error de permisos"}
};

string Bitacora::obtenerDescripcionCodigo(int codigo) {
    auto it = DESCRIPCIONES_CODIGOS.find(codigo);
    if (it != DESCRIPCIONES_CODIGOS.end()) {
        return it->second;
    }
    return "Código no reconocido";
}

void Bitacora::registrarAccion(const std::string& usuario, int codigoAccion, const std::string& descripcion) {
    usuarioActual = usuario;
    ofstream archivo(ARCHIVO_BITACORA, ios::app);
    if (archivo.is_open()) {
        archivo << obtenerFechaHoraActual() << " | "
                << "Usuario: " << usuario << " | "
                << "Código: " << codigoAccion << " (" << obtenerDescripcionCodigo(codigoAccion) << ") | "
                << "Detalles: " << descripcion << endl;
        archivo.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo de bitácora para escritura." << endl;
    }
}

void Bitacora::mostrarBitacora() {
    ifstream archivo(ARCHIVO_BITACORA);
    if (archivo.is_open()) {
        cout << "\n=== CONTENIDO DE LA BITÁCORA ===" << endl;
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        cout << "=== FIN DE LA BITÁCORA ===" << endl;
        archivo.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo de bitácora para lectura." << endl;
    }
}

string Bitacora::obtenerFechaHoraActual() {
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tiempoLocal);
    return string(buffer);
}

string Bitacora::obtenerUsuarioActual() {
    return usuarioActual;
}
