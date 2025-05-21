// Incluye el archivo de encabezado para la clase Empleados
#include "Empleados.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include "bitacora.h"
// Objeto creado de la clase Empleados
Empleados empleados;
bitacora bitacoraempleado;
// Creado y documentado Por Isaias Cedillo (9959-24-1672) "IsaC8-bit y Xander reyes(prestaciones)"
// Constructor de la clase Empleados. Actualmente no realiza ninguna acción específica.
Empleados::Empleados()
{
}
// Metodo que muestra el menú de nómina
void Empleados::mostrarMenuNomina(const std::string& usuarioRegistrante)
{
    // Inicia un bucle que se ejecuta hasta que la opción sea 3.
    do{
        // Limpia la pantalla de la consola.
        system ("cls");
        // Muestra el encabezado del menú.
        cout << "\n -----MENU DE PRESTACIONES LABORALES -----\n";
        cout << "\n -----------------------------------------\n";
        cout << "1. Mostrar nomina general"<<endl;
        cout << "2. Mostrar nomina en especifico"<<endl<<endl;
        cout << "3. Regresar\n";
        cout << "\n -----------------------------------------\n";
        cout << "\n -----------------NOMIREG-----------------\n";
        // Solicita al usuario que seleccione una opción y la lee.
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        // Inicia una estructura switch para ejecutar diferentes acciones según la opción.
        switch (opcion)
        {
        // Mostrar nómina general.
        case 1:
            //mensaje indicando que la función está en desarrollo.
            cout<<"EN DESAROLLO...."<<endl;
            break;
        // Mostrar nómina específica.
        case 2:
            // Llama a la función buscarEmpleado del objeto empleados.
            buscarEmpleado(usuarioRegistrante);
            break;
        // Opción no válida.
        default:
            cout<<"Saliendo del sistema..."<<endl;
            break;
        }
        system("pause");
    // Continúa el bucle mientras la opción no sea 3.
    }while (opcion!=3);
}

// Muestra el menú principal para la gestión de empleados.
void Empleados::menuEmpleados(const std::string& usuarioRegistrante)
{
    // Inicializa la variable para la elección del usuario.
    int eleccion = 0;
    // Inicializa la variable para la confirmación del usuario.
    char x;
    // Inicia un bucle que se ejecuta hasta que la elección sea 5.
    do
    {
        // Limpia la pantalla de la consola.
        system("cls");
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t |     Registro de empleados   |" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t 1. Ingreso de Empleados" << endl;
        cout << "\t\t\t 2. Despliegue de Empleados" << endl;
        cout << "\t\t\t 3. Modificar Empleados" << endl;
        cout << "\t\t\t 4. Borrar Empleados" << endl;
        cout << "\t\t\t 5. Regresar" << endl<<endl;
        // Solicita al usuario que ingrese el número de la opción.
        cout << "\t\t Ingrese numero de opcion: ";
        // Lee la elección del usuario.
        cin >> eleccion;
        // Inicia una estructura switch.
        switch(eleccion)
        {
            // Ingreso de empleados.
            case 1:
                cout << "Opcion escogida... \n";
                // Llama a la función registroEmpleados para ingresar un nuevo empleado.
                registroEmpleados(usuarioRegistrante);
                // Pregunta si hay más empleados para añadir.
                cout << "Hay más empleados por añadir? Y/N \n";
                cin >> x;
                // Inicia un bucle para permitir el ingreso de múltiples empleados.
                while (x == 'y' || x == 'Y') {
                    // Llama a la función registroEmpleados para ingresar otro empleado.
                    registroEmpleados(usuarioRegistrante);
                    cout << "¿Desea ingresar otro empleado? Y/N \n";
                    cin >> x;
                }
                break;
            //Despliegue de empleados.
            case 2:
                cout << "Opcion escogida...\n";
                // Llama a la función listaEmpleados para mostrar la lista de empleados.
                listaEmpleados(usuarioRegistrante);
                break;
            //Modificar empleados.
            case 3:
                cout << "Opcion escogida \n";
                // Llama a la función cambioEmpleados para modificar la información de un empleado.
                cambioEmpleados(usuarioRegistrante);
                break;
            //Borrar empleados.
            case 4:
                cout << "Opcion escogida \n";
                // Llama a la función borrarEmpleados para eliminar un empleado.
                borrarEmpleados(usuarioRegistrante);
                break;
            // Regresar.
            case 5:
                cout <<"Regresando...."<<endl;
                break;
            // Opción no válida.
            default:
                // Muestra un mensaje indicando que la opción no es válida.
                cout << "Opcion no valida" << endl;
                break;
        }
        // Pausa la consola para que el usuario pueda ver la salida.
        system("pause");
    // Continúa el bucle mientras la elección no sea 5.
    } while(eleccion != 5);
}

// Registra la información de un nuevo empleado.
void Empleados::registroEmpleados(const std::string& usuarioRegistrante)
{
    // Limpia la pantalla de la consola.
    system("cls");
    // Declara un objeto fstream para trabajar con archivos.
    fstream file;
    cout << "\n--------------------- Agregar Empleado ---------------------" << endl;

    // Limpia el búfer de entrada antes de leer el nombre.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Lee el nombre completo del empleado, permitiendo espacios.
    cout << "Nombre completo: ";
    getline(cin, Nombre);

    // Solicita el sueldo del empleado.
    cout << "Sueldo: Q";
    // Lee el sueldo del empleado.
    cin >> sueldo;
    // Abre el archivo "Empleados.bin" .
    file.open("Empleados.bin", ios::app | ios::out);
    // Verifica si el nombre está vacío o el sueldo es menor a 4000.
    if ( Nombre.empty() || sueldo < 4000)
    {
        cout << "Error: campos inválidos.\n";
        return;
    }
    // Verifica si el archivo se abrió correctamente.
    if (!file.is_open())
    {
        // Muestra un mensaje de error si no se pudo abrir el archivo.
        cout << "Error al abrir el archivo!" << endl;
        // Sale de la función.
        return;
    }
    // Escribe la información del empleado en el archivo, utilizando "|" como delimitador.
    file << tipoEmpleado << "|" << Nombre << "|" << sueldo << "\n";
    // Cierra el archivo.
    file.close();

    string codigoAplicacion = bitacoraempleado.generarCodigoAplicacion();
    // Inserta un registro en la bitácora indicando el ingreso de un empleado.
    bitacoraempleado.insertar(usuarioRegistrante, codigoAplicacion, "Ing");
}

// Muestra la lista de todos los empleados registrados.
void Empleados::listaEmpleados(const std::string& usuarioRegistrante)
{
    // Limpia la pantalla de la consola.
    system("cls");
    // Declara un objeto fstream para trabajar con archivos.
    fstream file;
    // Inicializa un contador para el número total de empleados.
    int total = 0;

    // Muestra el encabezado de la lista de empleados.
    cout << "\n==================== LISTA DE EMPLEADOS ====================" << endl;
    // Abre el archivo "Empleados.bin" en modo input (lectura).
    file.open("Empleados.bin", ios::in);
    // Verifica si el archivo se abrió correctamente.
    if (!file.is_open())
    {
        // Muestra un mensaje si no hay empleados registrados o el archivo no existe.
        cout << "\nNo hay empleados registrados o el archivo no existe.\n";
        return;
    }
    // Declara una variable para almacenar cada línea leída del archivo.
    string linea;
    // Lee el archivo línea por línea.
    while (getline(file, linea))
    {
        // Busca la posición del primer delimitador "|".
        size_t pos1 = linea.find("|");
        // Busca la posición del segundo delimitador "|" después del primero.
        size_t pos2 = linea.find("|", pos1 + 1);
        // Verifica si ambos delimitadores fueron encontrados.
        if (pos1 != string::npos && pos2 != string::npos)
        {
            // Extrae el tipo de empleado (actualmente no se usa en la impresión).
            tipoEmpleado = linea.substr(0, pos1);
            // Extrae el nombre del empleado.
            Nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            // Extrae y convierte el sueldo a float.
            sueldo = stof(linea.substr(pos2 + 1));
            // Muestra una línea separadora.
            cout << "-----------------------------"<<endl;
            // Muestra el nombre del empleado.
            cout << "Nombre: " << Nombre << endl;
            // Muestra el sueldo del empleado con formato de dos decimales.
            cout << "Sueldo: Q" << fixed << setprecision(2) << sueldo << endl;
            // Incrementa el contador total de empleados.
            total++;
        }
    }
    // Verifica si no se encontraron empleados.
    if (total == 0)
    {
        // Muestra un mensaje si no hay empleados registrados.
        cout << "\nNo hay empleados registrados.\n";
    }
    else
        // Muestra el número total de empleados registrados.
        cout << "\nTotal de empleados: " << total << endl;
        system("pause");
    // Cierra el archivo.
    file.close();

    string codigoAplicacion = bitacoraempleado.generarCodigoAplicacion();
    // Inserta un registro en la bitácora indicando la consulta de la lista de empleados.
    bitacoraempleado.insertar(usuarioRegistrante, codigoAplicacion, "Cons");
}

// Permite modificar el sueldo de un empleado.
void Empleados::cambioEmpleados(const std::string& usuarioRegistrante) {
    // Limpia la pantalla de la consola.
    system("cls");
    // Declara objetos fstream para trabajar con el archivo original y temporal.
    fstream file;
    fstream file1;
    // Declara una variable para almacenar el nombre del empleado a modificar.
    string NombreCambio;
    // Declara una variable para almacenar el nuevo sueldo del empleado.
    float sueldoCambio;
    // Inicializa un contador para verificar si se encontró al empleado.
    int found = 0;

    // Muestra el encabezado para la modificación de empleados.
    cout << "\n-------------------------Cambios laborales (no despidos)-------------------------" << endl;

    // Solicita el nombre del empleado a modificar.
    cout << "\n Ingrese el nombre de la persona a modificar: ";
    // Limpia el búfer de entrada.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Lee el nombre del empleado a modificar.
    getline(cin, NombreCambio);

    // Abre el archivo "Empleados.bin" en modo input (lectura).
    file.open("Empleados.bin", ios::in);
    // Verifica si el archivo se abrió correctamente.
    if (!file.is_open()) {
        // Muestra un mensaje si no hay informacion
        cout << "\n\t\t\tNo hay información o no se pudo abrir el archivo..." << endl;
        return;
    }
    // Declara una variable de tipo string llamada 'linea' para almacenar cada línea leída del archivo.
    string linea;
    // Inicia un bucle while que continúa mientras se puedan leer líneas del archivo 'file' y almacenarlas en 'linea'.
    while (getline(file, linea)) {
        // Busca la posición de la primera ocurrencia del delimitador "|" en la línea actual.
        size_t pos1 = linea.find("|");
        // Busca la posición de la segunda ocurrencia del delimitador "|" en la línea actual, comenzando la búsqueda después de la primera ocurrencia.
        size_t pos2 = linea.find("|", pos1 + 1);
        // Verifica si se encontraron ambas ocurrencias del delimitador "|" en la línea.
        if (pos1 != string::npos && pos2 != string::npos) {
            // Extrae el nombre del empleado de la línea actual, que se encuentra entre el primer y el segundo delimitador "|".
            string nombreTemp = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            // Compara el nombre extraído ('nombreTemp') con el nombre del empleado que se está buscando para modificar ('NombreCambio').
            if (nombreTemp == NombreCambio) {
                // Si los nombres coinciden, incrementa el contador 'found' para indicar que se encontró al empleado.
                found++;
                // Sale del bucle while ya que se encontró al empleado que se desea modificar.
                break;
            }
        }
    }
    // Cierra el archivo 'file' después de la búsqueda.
    file.close();

    // Verifica si no se encontró al usuario con el nombre ingresado.
    if (found == 0) {
        // Muestra un mensaje indicando que el usuario no fue encontrado.
        cout << "\n\t\t\tUsuario no encontrado..." << endl;
        // Sale de la función 'cambioEmpleados' sin realizar modificaciones.
        return;
    }

    // Solicitar los nuevos datos
    // Muestra un mensaje solicitando el nuevo sueldo del empleado.
    cout << "\n Ingrese el nuevo sueldo: ";
    // Lee el nuevo sueldo ingresado por el usuario y lo almacena en la variable 'sueldoCambio'.
    cin >> sueldoCambio;
    // Verifica si el nuevo sueldo ingresado es menor que 4000 (posible validación según ley).
    if (sueldoCambio<4000)
    {
        // Muestra un mensaje indicando que el sueldo ingresado no es válido según la ley.
        cout<<"Ingrese un sueldo valido segun ley.."<<endl;
        // Pausa la ejecución del programa para que el usuario pueda ver el mensaje.
        system("pause");
    }else
    {
        // Crear archivo temporal para escribir los datos actualizados
        // Abre el archivo "Empleados.bin" en modo input (lectura).
        file.open("Empleados.bin", ios::in);
        // Abre un nuevo archivo llamado "Record.txt" en modo output (escritura). Este archivo se utilizará como temporal para guardar los datos actualizados.
        file1.open("Record.txt", ios::out);
        // Verifica si el archivo temporal se abrió correctamente.
        if (!file1.is_open()) {
            // Muestra un mensaje de error si no se pudo crear el archivo temporal.
            cout << "\n\t\t\tError al crear archivo temporal." << endl;
            // Cierra el archivo original.
            file.close();
            // Sale de la función 'cambioEmpleados' debido al error.
            return;
        }

        // Inicia un bucle while para leer el archivo original línea por línea.
        while (getline(file, linea)) {
            // Busca la posición de la primera ocurrencia del delimitador "|" en la línea actual.
            size_t pos1 = linea.find("|");
            // Busca la posición de la segunda ocurrencia del delimitador "|" en la línea actual, comenzando la búsqueda después de la primera ocurrencia.
            size_t pos2 = linea.find("|", pos1 + 1);
            // Verifica si se encontraron ambas ocurrencias del delimitador "|" en la línea.
            if (pos1 != string::npos && pos2 != string::npos) {
                // Extrae el tipo de empleado de la línea actual.
                string tipoTemp = linea.substr(0, pos1);
                // Extrae el nombre del empleado de la línea actual.
                string nombreTemp = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                // Extrae y convierte el sueldo del empleado de la línea actual a tipo float.
                float sueldoTemp = stof(linea.substr(pos2 + 1));
                // Escribe los datos en el archivo temporal
                if (nombreTemp == NombreCambio)
                    // Guarda en el archivo temporal el nombre junto con el nuevo sueldo
                    file1 << tipoTemp << "|" << nombreTemp << "|" << sueldoCambio << endl;
                else
                    // Si no coincide el nombre, escribe la línea original en el archivo temporal.
                    file1 << linea << endl;
            } else {
                // Si la línea no tiene el formato esperado, escribe la línea original en el archivo temporal.
                file1 << linea << endl;
            }
        }
        // Cerrar archivos
        // Cierra el archivo original.
        file.close();
        // Cierra el archivo temporal.
        file1.close();
        // Eliminar el archivo original
        // Elimina el archivo "Empleados.bin".
        remove("Empleados.bin");
        // Renombrar el archivo temporal
        // Renombra el archivo "Record.txt" a "Empleados.bin".
        rename("Record.txt", "Empleados.bin");
        // Mensaje de éxito
        // Muestra un mensaje indicando que se ha modificado el registro del empleado.
        cout << "\n\t\t\tRegistro modificado exitosamente..." << endl;
    }
    // Genera un código de aplicación para la bitácora.
    string codigoAplicacion = bitacoraempleado.generarCodigoAplicacion();
    // Inserta un registro en la bitácora indicando la modificación de un empleado.
    bitacoraempleado.insertar(usuarioRegistrante, codigoAplicacion, "Mod");
}

void Empleados::borrarEmpleados(const std::string& usuarioRegistrante)
{
// Limpiar la pantalla
system("cls");
fstream file, file1;
string CambioNombreBorrar;
int found = 0;

cout << "\n-------------------------Detalles Persona a Borrar-------------------------" << endl;

// Abrir el archivo de empleados para lectura
file.open("Empleados.bin", ios::in);
if (!file.is_open())
{
    cout << "\n\t\t\tNo hay información o no se pudo abrir el archivo..." << endl;
    return;
}

// Solicitar el nombre del empleado a borrar
cout << "\n Ingrese el nombre de la Persona que quiere borrar: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
getline(cin, CambioNombreBorrar); // Leer nombre completo con espacios

// Abrir archivo temporal donde se guardarán los empleados no eliminados
file1.open("Record.txt", ios::out);
if (!file1.is_open())
{
    cout << "\n\t\t\tError al crear archivo temporal." << endl;
    file.close();
    return;
}

string linea;
// Leer el archivo original línea por línea
while (getline(file, linea))
{
    // Buscar posiciones del delimitador |
    size_t pos1 = linea.find("|");
    size_t pos2 = linea.find("|", pos1 + 1);

    // Verificar que los delimitadores existan
    if (pos1 != string::npos && pos2 != string::npos)
    {
        // Extraer campos de la línea
        tipoEmpleado = linea.substr(0, pos1);
        Nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        sueldo = stof(linea.substr(pos2 + 1));

        // Si el nombre no coincide con el que se quiere borrar, se escribe en el archivo temporal
        if (CambioNombreBorrar != Nombre)
        {
            file1 << tipoEmpleado << "|" << Nombre << "|" << sueldo << "\n";
        }
        else
        {
            found++; // Se encontró el empleado a borrar
            cout << "\n\t\t\tBorrado exitoso" << endl;
        }
    }
}

file.close();
file1.close();

// Revisión final: si se encontró y eliminó al empleado, se reemplaza el archivo original
if (found == 0)
{
    cout << "\n\t\t\tEmpleado no encontrado..." << endl;
    remove("Record.txt"); // Eliminar archivo temporal si no hubo coincidencias
}
else
{
    remove("Empleados.bin");         // Borrar archivo original
    rename("Record.txt", "Empleados.bin"); // Renombrar archivo temporal como definitivo
}

// Genera un código de aplicación para la bitácora.
    string codigoAplicacion = bitacoraempleado.generarCodigoAplicacion();
    // Inserta un registro en la bitácora indicando la modificación de un empleado.
    bitacoraempleado.insertar(usuarioRegistrante, codigoAplicacion, "Mod");

}
// Busca un empleado por su nombre.
void Empleados::buscarEmpleado(const std::string& usuarioRegistrante) {
    // Limpia la pantalla de la consola.
    system("cls");
    // Declara un objeto fstream para trabajar con archivos.
    fstream file;
    // Declara una variable string para almacenar el nombre del empleado a buscar.
    string nombreBuscar;
    // Muestra el encabezado para la búsqueda de empleados.
    cout << "\n==================== BUSCAR EMPLEADO ====================" << endl;
    // Solicita al usuario que ingrese el nombre del empleado a buscar.
    cout << "Ingrese el nombre del empleado: ";
    // Limpia el búfer de entrada antes de leer el nombre.
    cin.ignore();
    // Lee el nombre completo del empleado a buscar, permitiendo espacios.
    getline(cin, nombreBuscar);
    // Abre el archivo "Empleados.bin" en modo input (lectura).
    file.open("Empleados.bin", ios::in);
    // Verifica si el archivo se abrió correctamente.
    if (!file.is_open()) {
        // Muestra un mensaje si no hay empleados registrados o el archivo no existe.
        cout << "\nNo hay empleados registrados o el archivo no existe.\n";
        // Sale de la función.
        return;
    }
    // Declara una variable string para almacenar cada línea leída del archivo.
    string linea;
    // Declara una variable booleana para indicar si se encontró al empleado.
    bool encontrado = false;
    // Lee el archivo línea por línea.
    while (getline(file, linea)) {
        // Busca la posición del primer delimitador "|" en la línea actual.
        size_t pos1 = linea.find("|");
        // Busca la posición del segundo delimitador "|" después del primero.
        size_t pos2 = linea.find("|", pos1 + 1);
        // Verifica si se encontraron ambos delimitadores en la línea.
        if (pos1 != string::npos && pos2 != string::npos) {
            // Extrae el nombre del empleado de la línea actual.
            string Nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            // Extrae y convierte el sueldo del empleado a tipo double.
            double sueldo = stof(linea.substr(pos2 + 1));
            // Compara el nombre del empleado extraído con el nombre buscado.
            if (Nombre == nombreBuscar) {
                // Muestra un mensaje indicando que se encontró al empleado.
                cout << "\nEmpleado encontrado:\n";
                // Muestra el nombre del empleado encontrado.
                cout << "Nombre: " << Nombre << endl;
                // Muestra el sueldo del empleado encontrado con formato de dos decimales.
                cout << "Sueldo: Q" << fixed << setprecision(2) << sueldo << endl;
                // Asigna el sueldo encontrado a la variable salarioBruto.
                salarioBruto=sueldo;
                // Asigna el sueldo encontrado a la variable salarioNeto (inicialmente igual al bruto).
                salarioNeto=sueldo;
                // Declara una variable entera para la opción de la nómina.
                int nomina;
                // Pregunta al usuario si desea mostrar la nómina anual o mensual.
                cout<<"Desea mostrar: "<<endl;
                // Muestra la opción para la nómina anual.
                cout<<"1. Nomina anual de a o anterior"<<endl;
                // Muestra la opción para la nómina mensual.
                cout<<"2. Nomina mensual del a o actual"<<endl;
                // Lee la opción de la nómina ingresada por el usuario.
                cin>>nomina;
                // Inicia una estructura switch para ejecutar diferentes acciones según la opción de la nómina.
                switch (nomina)
                {
                    // Caso 1: Calcular y mostrar la nómina anual.
                    case 1:
                        // Llama a la función calcularNominaAnual del objeto empleados.
                        calcularNominaAnual();
                    // Sale del caso.
                    break;
                    // Caso 2: Calcular y mostrar la nómina mensual.
                    case 2:
                        // Llama a la función calcularNominaMensual del objeto empleados.
                        calcularNominaMensual();
                    // Sale del caso.
                    break;
                }
                // Establece la variable encontrado en true para indicar que se encontró al empleado.
                encontrado = true;
                // Sale del bucle while ya que se encontró al empleado.
                break;
            }
        }
    }
    // Verifica si no se encontró al empleado.
    if (!encontrado) {
        // Muestra un mensaje indicando que el empleado no fue encontrado.
        cout << "\nEmpleado no encontrado.\n";
    } else {
        // Muestra una línea en blanco (puede ser para formateo).
        cout<<""<<endl;
    }
    // Cierra el archivo.
    file.close();

    // Registra la búsqueda en la bitácora
    string codigoAplicacion = bitacoraempleado.generarCodigoAplicacion();
    bitacoraempleado.insertar(usuarioRegistrante, codigoAplicacion, "Bus");
}
//Realizado por XANDER REYES
void Empleados::calcularNominaMensual() {
    // Declaración de variable para almacenar el mes ingresado por el usuario
    int mesActual;

    // Solicita al usuario que ingrese el número del mes (del 1 al 12)
    cout << "Ingrese el numero del mes (1-12): ";
    cin >> mesActual;

    // Verifica si el mes ingresado está dentro del rango válido
    if (mesActual < 1 || mesActual > 12) {
        // Muestra un mensaje de error si el mes no es válido
        cout << "Mes invalido. Debe estar entre 1 y 12." << endl;
        return; // Sale de la función sin hacer más cálculos
    }

    // Calcula el descuento por ISR (Impuesto Sobre la Renta)
    salarioSinISR = salarioBruto * ISR;

    // Calcula el descuento por IRTRA (Instituto de Recreación de los Trabajadores)
    salarioSinIRTRA = salarioBruto * IRTRA;

    // Calcula el descuento por IGSS (Instituto Guatemalteco de Seguridad Social)
    salarioSinIGSS = salarioBruto * IGSS;

    // Si el mes es junio (6), se asigna el Bono 14 igual al salario bruto, si no, se asigna 0
    bono14 = (mesActual == 6) ? salarioBruto : 0.0;

    // Si el mes es diciembre (12), se asigna el Aguinaldo igual al salario bruto, si no, se asigna 0
    aguinaldo = (mesActual == 12) ? salarioBruto : 0.0;

    // Calcula el salario neto: salario bruto menos descuentos, más bono incentivo y posibles bonos adicionales
    salarioNeto = salarioBruto - salarioSinISR - salarioSinIRTRA - salarioSinIGSS + bonoIncentivo + bono14 + aguinaldo;

    // Arreglo con los nombres de los meses del año
    const string meses[12] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    // Muestra el nombre del mes correspondiente
    cout << "Nomina mes de " << meses[mesActual - 1] << endl;

    // Muestra el monto descontado por IGSS
    cout << "Descuento del IGSS: Q" << salarioSinIGSS << endl;

    // Muestra el monto descontado por IRTRA
    cout << "Descuento del IRTRA: Q" << salarioSinIRTRA << endl;

    // Muestra el monto descontado por ISR
    cout << "Descuento del ISR: Q" << salarioSinISR << endl;

    // Muestra el bono incentivo sumado al salario
    cout << "Bono incentivo: +Q" << bonoIncentivo << endl;

    // Si se aplica Bono 14, lo muestra en pantalla
    if (bono14 > 0) cout << "Bono 14: +Q" << bono14 << endl;

    // Si se aplica Aguinaldo, lo muestra en pantalla
    if (aguinaldo > 0) cout << "Aguinaldo: +Q" << aguinaldo << endl;

    // Muestra el salario neto final que recibirá el empleado
    cout << "Salario neto a recibir: Q" << salarioNeto << endl;
}
// Calcula la nómina anual de un empleado (función vacía).
void Empleados::calcularNominaAnual()
{

}
