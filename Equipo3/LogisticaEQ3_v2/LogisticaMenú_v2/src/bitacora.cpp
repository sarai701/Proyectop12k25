#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <chrono>

// Inicialización de los códigos de los módulos en la bitácora
std::unordered_map<std::string, int> CodigosBitacora::rangos = {
    {"AUTENTICACION", 3000}, {"USUARIOS", 3050}, {"PEDIDOS", 3100},
    {"CLIENTES", 3150}, {"PROVEEDORES", 3200}, {"PRODUCTOS", 3250},
    {"ALMACENES", 3300}, {"TRANSPORTISTAS", 3350}, {"FACTURACION", 3400},
    {"REPORTES", 3450}, {"INVENTARIO", 3500}, {"ENVIOS", 3550},
    {"SISTEMA", 3600}
};

// Obtiene el código asociado a un módulo. Si no existe, asigna un nuevo código.
int CodigosBitacora::getCodigo(const std::string& modulo) {
    // Si el módulo no existe, lo añade con el código inicial
    if (rangos.find(modulo) == rangos.end()) {
        rangos[modulo] = 3000;
    }
    return rangos[modulo]++; // Incrementa el código para el próximo uso
}

// Registra un evento en la bitácora
void bitacora::registrar(const std::string& usuario,
                         const std::string& modulo,
                         const std::string& descripcion) {
    // Verifica si el archivo está vacío para agregar encabezado
    std::ifstream check("bitacora.txt");
    bool isEmpty = check.peek() == std::ifstream::traits_type::eof();
    check.close();

    // Abre el archivo en modo de append (agregar al final)
    std::ofstream file("bitacora.txt", std::ios::app);
    int codigo = CodigosBitacora::getCodigo(modulo);

    // Obtiene la fecha y hora actual
    std::time_t now = std::time(nullptr);
    char fecha[100];
    std::strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", std::localtime(&now));

    if (file.is_open()) {
        // Si el archivo está vacío, agrega el encabezado
        if (isEmpty) {
            file << "-------------------------- BITÁCORA DEL SISTEMA --------------------------\n";
            file << std::left
                 << std::setw(12) << "ID_ACCION"
                 << std::setw(15) << "USUARIO"
                 << std::setw(20) << "MODULO"
                 << std::setw(35) << "DESCRIPCION"
                 << std::setw(20) << "FECHA_HORA" << "\n";
            file << "---------------------------------------------------------------------------\n";
        }

        // Escribe el nuevo registro en la bitácora
        file << std::left
             << std::setw(12) << codigo
             << std::setw(15) << usuario
             << std::setw(20) << modulo
             << std::setw(35) << descripcion
             << std::setw(20) << fecha << "\n";
    }
}

// Obtiene la fecha actual en formato "DD/MM/AAAA"
std::string bitacora::obtenerFechaActual() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

// Muestra el contenido de la bitácora en la consola
void bitacora::mostrarBitacora() {
#ifdef _WIN32
    system("cls");  // Limpiar consola en Windows
#else
    system("clear");  // Limpiar consola en Linux/Mac
#endif

    std::ifstream file("bitacora.txt");

    std::cout << "\t\t========================================================\n";
    std::cout << "\t\t|                      BITÁCORA                        |\n";
    std::cout << "\t\t========================================================\n";

    // Si el archivo está abierto, muestra su contenido
    if (file.is_open()) {
        std::string linea;
        while (std::getline(file, linea)) {
            std::cout << "\t\t" << linea << "\n";
        }
        file.close();
    } else {
        std::cout << "\t\tNo hay registros en la bitácora.\n";
    }

    std::cout << "\t\t===============================================================\n";
    system("pause"); // Pausa la ejecución para que el usuario vea la bitácora
}

// Genera un backup de la bitácora
void bitacora::generarBackup() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << "backup_bitacora_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".txt";

    std::ifstream src("bitacora.bin", std::ios::binary);
    std::ofstream dst(oss.str(), std::ios::binary);

    if (src && dst) {
        dst << src.rdbuf(); // Copia el contenido de la bitácora a un nuevo archivo
        registrar("SISTEMA", "SISTEMA", "Backup de bitácora generado: " + oss.str());
        std::cout << "\n\t\tBackup generado exitosamente: " << oss.str() << "\n";
    } else {
        std::cerr << "\n\t\tError al generar backup!\n";
    }
    system("pause");
}

// Reinicia el contenido de la bitácora (elimina todo)
void bitacora::reiniciarBitacora() {
    std::ofstream file("bitacora.txt", std::ios::trunc);  // Abre el archivo para truncarlo (vaciarlo)
    if (file.is_open()) {
        file.close();
        std::cout << "Bitácora reiniciada con éxito.\n";
    } else {
        std::cout << "Error al reiniciar la bitácora.\n";
    }
    system("pause");
}

// Permite buscar registros en la bitácora por el código de usuario
void bitacora::buscarPorCodigoUsuario() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::string usuarioBuscar;
    std::cout << "\n\t\tIngrese el ID o nombre del usuario a buscar: ";
    std::cin >> usuarioBuscar;

    std::ifstream file("bitacora.txt");
    bool encontrado = false;

    if (file.is_open()) {
        std::string linea;
        std::cout << "\n\t\tRegistros encontrados:\n";
        while (std::getline(file, linea)) {
            if (linea.find(usuarioBuscar) != std::string::npos) {
                std::cout << "\t\t" << linea << "\n";
                encontrado = true;
            }
        }
        file.close();
        if (!encontrado) {
            std::cout << "\t\tNo se encontraron registros para ese usuario.\n";
        }
    } else {
        std::cout << "\t\tNo se pudo abrir la bitácora.\n";
    }
    system("pause");
}

// Permite buscar registros en la bitácora por fecha
void bitacora::buscarPorFecha() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::string fechaBuscar;
    std::cout << "\n\t\tIngrese la fecha a buscar (formato DD/MM/AAAA): ";
    std::cin >> fechaBuscar;

    std::ifstream file("bitacora.txt");
    bool encontrado = false;

    if (file.is_open()) {
        std::string linea;
        std::cout << "\n\t\tRegistros encontrados:\n";
        while (std::getline(file, linea)) {
            if (linea.find(fechaBuscar) != std::string::npos) {
                std::cout << "\t\t" << linea << "\n";
                encontrado = true;
            }
        }
        file.close();
        if (!encontrado) {
            std::cout << "\t\tNo se encontraron registros para esa fecha.\n";
        }
    } else {
        std::cout << "\t\tNo se pudo abrir la bitácora.\n";
    }
    system("pause");
}

// Menú principal de la bitácora para el administrador
void bitacora::menuBitacora() {
    int opcion;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t|      ADMINISTRACIÓN DE BITÁCORA     |\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t 1. Ver registros completos\n";
        std::cout << "\t\t 2. Generar backup\n";
        std::cout << "\t\t 3. Buscar por código de usuario\n";
        std::cout << "\t\t 4. Buscar por fecha\n";
        std::cout << "\t\t 5. Reiniciar bitácora\n";
        std::cout << "\t\t 6. Volver al menú principal\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\tOpción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: mostrarBitacora(); break;
            case 2: generarBackup(); break;
            case 3: buscarPorCodigoUsuario(); break;
            case 4: buscarPorFecha(); break;
            case 5: reiniciarBitacora(); break;
            case 6: break;
            default:
                std::cout << "\n\t\tOpción inválida!";
                std::cin.ignore();
                std::cin.get();
        }
    } while (opcion != 6);
}
