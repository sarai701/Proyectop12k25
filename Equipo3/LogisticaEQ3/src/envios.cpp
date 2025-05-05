#include "envios.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// Transportistas predefinidos
const vector<string> transportistas = {
    "Transportes Rápidos S.A.",
    "Envíos Seguros Ltda.",
    "Logística Nacional",
    "Mensajería Express",
    "Carga Confiable"
};

void Envios::gestionEnvios() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t\t========================================";
        cout << "\n\t\t|       GESTIÓN DE ENVÍOS             |";
        cout << "\n\t\t========================================";
        cout << "\n\t\t| 1. Generar guía de envío            |";
        cout << "\n\t\t| 2. Asignar transportista            |";
        cout << "\n\t\t| 3. Rastrear envío                   |";
        cout << "\n\t\t| 4. Confirmar entrega                |";
        cout << "\n\t\t| 5. Cancelar envío                   |";
        cout << "\n\t\t| 6. Volver al menú principal         |";
        cout << "\n\t\t========================================";
        cout << "\n\t\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: generarGuia(); break;
            case 2: asignarTransportista(); break;
            case 3: rastrearEnvio(); break;
            case 4: confirmarEntrega(); break;
            case 5: cancelarEnvio(); break;
            case 6: break;
            default:
                cout << "\n\t\tOpción inválida!";
                cin.get();
        }
    } while(opcion != 6);
}

void Envios::generarGuia() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       GENERAR GUÍA DE ENVÍO         |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tNúmero de pedido: ";
    getline(cin, numeroPedido);

    cout << "\t\tNombre del destinatario: ";
    getline(cin, destinatario);

    cout << "\t\tDirección de entrega: ";
    getline(cin, direccion);

    cout << "\t\tCiudad: ";
    getline(cin, ciudad);

    cout << "\t\tTeléfono de contacto: ";
    getline(cin, telefono);

    // Generar número de guía automático
    srand(time(0));
    numeroGuia = "G" + to_string(rand() % 9000 + 1000);
    estado = "Pendiente";
    fechaGeneracion = obtenerFechaActual();

    guardarEnvio();

    cout << "\n\t\t========================================";
    cout << "\n\t\t| ¡GUÍA GENERADA CON ÉXITO!            |";
    cout << "\n\t\t========================================";
    cout << "\n\t\tNúmero de guía: " << numeroGuia;
    cout << "\n\t\tEstado: " << estado;
    cout << "\n\t\tFecha: " << fechaGeneracion;
    cout << "\n\t\t========================================";

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "GUIA-GENERADA-" + numeroGuia);
    system("pause");
}

void Envios::asignarTransportista() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|    ASIGNAR TRANSPORTISTA            |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tNúmero de guía: ";
    getline(cin, numeroGuia);

    if (!existeEnvio(numeroGuia)) {
        cout << "\n\t\t¡Guía no encontrada!";
        system("pause");
        return;
    }

    // Selección aleatoria de transportista
    srand(time(0));
    transportista = transportistas[rand() % transportistas.size()];

    actualizarEnvio("transportista", transportista);
    actualizarEnvio("estado", "En camino");

    cout << "\n\t\tTransportista asignado: " << transportista;
    cout << "\n\t\tEstado actualizado: En camino";

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "TRANS-ASIGNADO-" + numeroGuia);
    system("pause");
}

void Envios::rastrearEnvio() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|      RASTREO DE ENVÍO               |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tNúmero de guía: ";
    getline(cin, numeroGuia);

    ifstream archivo("envios.txt");
    bool encontrado = false;

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            size_t pos = linea.find("|");
            string guia = linea.substr(0, pos);

            if (guia == numeroGuia) {
                encontrado = true;
                vector<string> datos = split(linea, '|');

                cout << "\n\t\tINFORMACIÓN DEL ENVÍO";
                cout << "\n\t\t--------------------------------";
                cout << "\n\t\tGuía: " << datos[0];
                cout << "\n\t\tEstado: " << datos[4];
                cout << "\n\t\tTransportista: " << datos[3];
                cout << "\n\t\tÚltima actualización: " << datos[5];
                cout << "\n\t\t--------------------------------";
                cout << "\n\t\tHISTORIAL DE MOVIMIENTOS:";
                cout << "\n\t\t1. " << datos[5] << " - Envío registrado";
                cout << "\n\t\t2. " << datos[5] << " - En proceso de empaque";
                cout << "\n\t\t3. " << datos[5] << " - En ruta de entrega";

                if (datos[4] == "Entregado") {
                    cout << "\n\t\t4. " << datos[5] << " - Paquete entregado";
                }
                break;
            }
        }
        archivo.close();
    }

    if (!encontrado) {
        cout << "\n\t\t¡Guía no encontrada!";
    }

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "RASTREO-GUIA-" + numeroGuia);
    system("pause");
}

void Envios::confirmarEntrega() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|     CONFIRMACIÓN DE ENTREGA         |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tNúmero de guía: ";
    getline(cin, numeroGuia);

    if (!existeEnvio(numeroGuia)) {
        cout << "\n\t\t¡Guía no encontrada!";
        system("pause");
        return;
    }

    cout << "\t\tNombre de quien recibe: ";
    getline(cin, receptor);

    cout << "\t\tDNI/Cédula de quien recibe: ";
    getline(cin, documentoReceptor);

    cout << "\t\tObservaciones: ";
    getline(cin, observaciones);

    actualizarEnvio("estado", "Entregado");
    actualizarEnvio("fechaEntrega", obtenerFechaActual());

    cout << "\n\t\t¡Entrega confirmada con éxito!";

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "ENTREGA-CONFIRMADA-" + numeroGuia);
    system("pause");
}

void Envios::cancelarEnvio() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       CANCELACIÓN DE ENVÍO          |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tNúmero de guía: ";
    getline(cin, numeroGuia);

    if (!existeEnvio(numeroGuia)) {
        cout << "\n\t\t¡Guía no encontrada!";
        system("pause");
        return;
    }

    cout << "\t\tMotivo de cancelación: ";
    string motivo;
    getline(cin, motivo);

    // Eliminar el envío del archivo
    ifstream archivo("envios.txt");
    ofstream temp("temp.txt");

    if (archivo.is_open() && temp.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            if (linea.find(numeroGuia) == string::npos) {
                temp << linea << endl;
            }
        }
        archivo.close();
        temp.close();
        remove("envios.txt");
        rename("temp.txt", "envios.txt");
    }

    cout << "\n\t\t¡Envío cancelado con éxito!";

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "ENVIO-CANCELADO-" + numeroGuia + "-MOTIVO:" + motivo);
    system("pause");
}

// Funciones auxiliares
bool Envios::existeEnvio(const string& guia) {
    ifstream archivo("envios.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            if (linea.find(guia) != string::npos) {
                archivo.close();
                return true;
            }
        }
        archivo.close();
    }
    return false;
}

void Envios::actualizarEnvio(const string& campo, const string& valor) {
    ifstream archivo("envios.txt");
    ofstream temp("temp.txt");

    if (archivo.is_open() && temp.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            if (linea.find(numeroGuia) != string::npos) {
                vector<string> datos = split(linea, '|');

                if (campo == "transportista") datos[3] = valor;
                else if (campo == "estado") datos[4] = valor;
                else if (campo == "fechaEntrega") datos[5] = valor;

                // Reconstruir la línea
                string nuevaLinea = datos[0];
                for (size_t i = 1; i < datos.size(); i++) {
                    nuevaLinea += "|" + datos[i];
                }
                temp << nuevaLinea << endl;
            } else {
                temp << linea << endl;
            }
        }
        archivo.close();
        temp.close();
        remove("envios.txt");
        rename("temp.txt", "envios.txt");
    }
}

void Envios::guardarEnvio() {
    ofstream archivo("envios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << numeroGuia << "|" << numeroPedido << "|" << destinatario << "|"
                << transportista << "|" << estado << "|" << fechaGeneracion << "|"
                << direccion << "|" << ciudad << "|" << telefono << endl;
        archivo.close();
    }
}

vector<string> Envios::split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string Envios::obtenerFechaActual() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
}
