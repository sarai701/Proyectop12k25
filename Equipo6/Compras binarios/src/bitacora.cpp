#include "bitacora.h"
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

const string Bitacora::ARCHIVO_BITACORA = "bitacora.txt";
string Bitacora::usuarioActual = "";

// Mapa completo de descripciones de códigos de acción
const map<int, string> DESCRIPCIONES_CODIGOS = {
    // Autenticación
    {CodigosAccion::LOGIN_EXITOSO, "Inicio de sesión exitoso"},
    {CodigosAccion::LOGIN_FALLIDO, "Intento fallido de inicio de sesión"},
    {CodigosAccion::LOGOUT, "Cierre de sesión"},
    {CodigosAccion::BLOQUEO_USUARIO, "Usuario bloqueado"},
    {CodigosAccion::CAMBIO_CONTRASENA, "Cambio de contraseña"},

    // Accesos
    {CodigosAccion::ACCESO_MENU_PRINCIPAL, "Acceso al menú principal"},
    {CodigosAccion::ACCESO_TUTORIAL, "Acceso al tutorial"},
    {CodigosAccion::ACCESO_BUSQUEDA, "Acceso a búsqueda"},
    {CodigosAccion::ACCESO_CONTRAVERSIA, "Acceso al módulo Contraversia"},
    {CodigosAccion::ACCESO_CENTRO_VENERA, "Acceso al Centro Venera"},
    {CodigosAccion::ACCESO_HERRAMIENTAS_ARCHIVO, "Acceso a herramientas de archivo"},

    // CRUD de clientes y productos
    {CodigosAccion::CREACION_CLIENTE, "Creación de nuevo cliente"},
    {CodigosAccion::LECTURA_CLIENTE, "Consulta de cliente"},
    {CodigosAccion::ACTUALIZACION_CLIENTE, "Actualización de cliente"},
    {CodigosAccion::ELIMINACION_CLIENTE, "Eliminación de cliente"},
    {CodigosAccion::CREACION_PRODUCTO, "Creación de producto"},
    {CodigosAccion::LECTURA_PRODUCTO, "Consulta de producto"},
    {CodigosAccion::ACTUALIZACION_PRODUCTO, "Actualización de producto"},
    {CodigosAccion::ELIMINACION_PRODUCTO, "Eliminación de producto"},

    // Compras
    {CodigosAccion::CREACION_COMPRA, "Creación de compra"},
    {CodigosAccion::LECTURA_COMPRA, "Consulta de compra"},
    {CodigosAccion::CANCELACION_COMPRA, "Cancelación de compra"},

    // Selecciones (Contraversia)
    {CodigosAccion::SELECCION_FACUNDO, "Selección de Facundo"},
    {CodigosAccion::SELECCION_TURQUE_SALUD, "Selección de Turque Salud"},
    {CodigosAccion::SELECCION_CERCLESALUD, "Selección de CercleSalud"},
    {CodigosAccion::SELECCION_BANCOLAPACO, "Selección de BancoLapaco"},
    {CodigosAccion::SELECCION_MANOCORPORAL, "Selección de ManoCorporal"},
    {CodigosAccion::SELECCION_CLICATES, "Selección de Clicates"},
    {CodigosAccion::SELECCION_VENCENTES, "Selección de Vencentes"},
    {CodigosAccion::SELECCION_MANTENUTA, "Selección de Mantenuta"},
    {CodigosAccion::SELECCION_KISSES, "Selección de Kisses"},
    {CodigosAccion::SELECCION_COCONA, "Selección de Cocona"},
    {CodigosAccion::SELECCION_NOORREALIZA, "Selección de NoorRealiza"},
    {CodigosAccion::SELECCION_DORECA, "Selección de Doreca"},

    // Gestión de archivos
    {CodigosAccion::RESPALDO_CREADO, "Respaldo de datos creado"},
    {CodigosAccion::RESTAURACION_COMPLETADA, "Restauración completada"},
    {CodigosAccion::EXPORTACION_DATOS, "Exportación de datos"},
    {CodigosAccion::IMPORTACION_DATOS, "Importación de datos"},
    {CodigosAccion::LIMPIEZA_REGISTROS, "Limpieza de registros"},

    // Consultas y reportes
    {CodigosAccion::GENERACION_REPORTE, "Generación de reporte"},
    {CodigosAccion::CONSULTA_HISTORICO, "Consulta del historial"},
    {CodigosAccion::BUSQUEDA_AVANZADA, "Búsqueda avanzada"},

    // Configuraciones
    {CodigosAccion::CAMBIO_CONFIGURACION, "Cambio de configuración"},
    {CodigosAccion::ACTUALIZACION_SISTEMA, "Actualización del sistema"},
    {CodigosAccion::RESPALDO_CONFIGURACION, "Respaldo de configuración"},

    // Errores y advertencias
    {CodigosAccion::ERROR_SISTEMA, "Error del sistema"},
    {CodigosAccion::ERROR_PERMISOS, "Error de permisos"},
    {CodigosAccion::ERROR_ARCHIVO, "Error al acceder al archivo"},
    {CodigosAccion::ERROR_CONEXION, "Error de conexión"},
    {CodigosAccion::ADVERTENCIA_SISTEMA, "Advertencia del sistema"},
    {CodigosAccion::ADVERTENCIA_SEGURIDAD, "Advertencia de seguridad"}
};

string Bitacora::obtenerDescripcionCodigo(int codigo) {
    auto it = DESCRIPCIONES_CODIGOS.find(codigo);
    return (it != DESCRIPCIONES_CODIGOS.end()) ? it->second : "Código no reconocido";
}

void Bitacora::registrarAccion(const string& usuario, int codigoAccion, const string& descripcion) {
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
    tm* tiempo = localtime(&ahora);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tiempo);
    return string(buffer);
}

string Bitacora::obtenerUsuarioActual() {
    return usuarioActual;
}
