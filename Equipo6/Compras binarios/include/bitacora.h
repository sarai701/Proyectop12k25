#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <ctime> // Necesario para funciones relacionadas con fecha y hora

namespace CodigosAccion {
    // Autenticación y sistema (1000-1099)
    const int LOGIN_EXITOSO = 1000;
    const int LOGIN_FALLIDO = 1001;
    const int LOGOUT = 1002;
    const int BLOQUEO_USUARIO = 1003;
    const int CAMBIO_CONTRASENA = 1004;

    // Navegación y menús (1100-1199)
    const int ACCESO_MENU_PRINCIPAL = 1100;
    const int ACCESO_TUTORIAL = 1101;
    const int ACCESO_BUSQUEDA = 1102;
    const int ACCESO_CONTRAVERSIA = 1103;
    const int ACCESO_CENTRO_VENERA = 1104;
    const int ACCESO_HERRAMIENTAS_ARCHIVO = 1105;

    // Operaciones CRUD (1200-1299)
    const int CREACION_CLIENTE = 1200;
    const int LECTURA_CLIENTE = 1201;
    const int ACTUALIZACION_CLIENTE = 1202;
    const int ELIMINACION_CLIENTE = 1203;
    const int CREACION_PRODUCTO = 1210;
    const int LECTURA_PRODUCTO = 1211;
    const int ACTUALIZACION_PRODUCTO = 1212;
    const int ELIMINACION_PRODUCTO = 1213;
    const int CREACION_COMPRA = 1220;
    const int LECTURA_COMPRA = 1221;
    const int CANCELACION_COMPRA = 1222;

    // Contraversia (1300-1399)
    const int SELECCION_FACUNDO = 1300;
    const int SELECCION_TURQUE_SALUD = 1301;
    const int SELECCION_CERCLESALUD = 1302;
    const int SELECCION_BANCOLAPACO = 1303;
    const int SELECCION_MANOCORPORAL = 1304;
    const int SELECCION_CLICATES = 1305;
    const int SELECCION_VENCENTES = 1306;

    // Centro Venera (1400-1499)
    const int SELECCION_MANTENUTA = 1400;
    const int SELECCION_KISSES = 1401;
    const int SELECCION_COCONA = 1402;
    const int SELECCION_NOORREALIZA = 1403;
    const int SELECCION_DORECA = 1404;

    // Operaciones de archivo (1500-1599)
    const int RESPALDO_CREADO = 1500;
    const int RESTAURACION_COMPLETADA = 1501;
    const int EXPORTACION_DATOS = 1502;
    const int IMPORTACION_DATOS = 1503;
    const int LIMPIEZA_REGISTROS = 1504;

    // Reportes y consultas (1600-1699)
    const int GENERACION_REPORTE = 1600;
    const int CONSULTA_HISTORICO = 1601;
    const int BUSQUEDA_AVANZADA = 1602;

    // Configuración del sistema (1700-1799)
    const int CAMBIO_CONFIGURACION = 1700;
    const int ACTUALIZACION_SISTEMA = 1701;
    const int RESPALDO_CONFIGURACION = 1702;

    // Errores y advertencias (1900-1999)
    const int ERROR_SISTEMA = 1900;
    const int ERROR_PERMISOS = 1901;
    const int ERROR_ARCHIVO = 1902;
    const int ERROR_CONEXION = 1903;
    const int ADVERTENCIA_SISTEMA = 1950;
    const int ADVERTENCIA_SEGURIDAD = 1951;
}

class Bitacora {
public:
    static void registrarAccion(const std::string& usuario, int codigoAccion, const std::string& descripcion);
    static void mostrarBitacora();
    static std::string obtenerUsuarioActual();
    static std::string obtenerDescripcionCodigo(int codigo);

private:
    static const std::string ARCHIVO_BITACORA;
    static std::string obtenerFechaHoraActual();
    static std::string usuarioActual;
};

#endif
