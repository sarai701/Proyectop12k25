#include "pago.h"
#include "bitacora.h"
#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

extern usuarios usuariosrRegistrado;

pago::pago()
{
    //ctor
}
void pago::menuPagos(){
    int opcion;
    char x;
    do{
        system ("cls");
        cout << "\n\n\t\tMenu de pagos" << endl;
        cout << "\t\t------------------------" << endl;
        cout << "\t\t1. Cuentas por Pagar" << endl;
        cout << "\t\t2. Registrar Pago" << endl;
        cout << "\t\t3. Historial de Pagos" << endl;
        cout << "\t\t4. Busqueda por Factura" << endl;
        cout << "\t\t5. Mostrar Pagos por Acreedor/Proveedor" << endl;
        cout << "\t\t6. Volver al menu Principal" << endl;
        cout << "\n\t\tIngrese una opción: ";
        cin >> opcion;

        switch (opcion){
        case 1:
            mostrarCuentasPorPagar();
            break;
        case 2:
            do {
                registrarPago();
                cout<<"\n\t\t Registrar otro pago(Y/N): ";
                cin>>x;
            } while(x=='y'||x=='Y');
            break;
        case 3:
            listarHistorialPagos();
            break;
        case 4:
            do {
                buscarPagosPorFacura();
                cout<<"\n\t\t Desea realizar otra busqueda(Y/N): ";
                cin>>x;
            } while(x=='y'||x=='Y');
            break;
        case 5:
            do {
                listarPagosPorProveedor();
                cout<<"\n\t\t Desea realizar otra consulta (Y/N): ";
                cin>>x;
            } while(x=='y'||x=='Y');
            break;
        case 6:
            break;
        default :
            cout << "\t\t Opccion invalida..." << endl;
            system("pause");
        }
    } while (opcion != 6);

}

void pago::registrarPago(){
    bitacora auditoria;
    //Archivos
    fstream fileFacturas, filePagos, fileTemporal;

    //Variables de factura
    string lineaFactura;
    string idFactura, nombre, cuenta, montoStr, fecha, hora, tipo, clasificacion, estado/*, saldoStr*/;
    float montoTotal, saldoPendiente;
    string idFacturaRegistrada;

    //Variables de control
    bool facturaExiste= false;
    char confirmar;

    system ("cls");
    cout << "\n------------- Registrar Nuevo Pago -------------\n";
    cout << "\n\t Ingrese el ID de la factura: "; //Ingreso del id de la factura a pagar
    cin >> idFacturaRegistrada;

    fileFacturas.open("facturas.bin", ios::in |ios::binary);
    fileTemporal.open("facturas_temporal.bin", ios::app | ios::out |ios::binary);

    if (!fileFacturas){
        cout << "No se encontro informacion..." << endl;
        system ("pause");
        return;
    }

    //Lectura del archivo factura line por linea y la guarda en lineaFactura
    while (getline(fileFacturas, lineaFactura)){
        stringstream ss(lineaFactura);//Ayuda a extrar cada campo de forma individual
        //Extrae el flujo ss hasta la primera coma
        getline(ss, idFactura, ',');
        getline(ss, nombre, ',');
        getline(ss, cuenta, ',');
        getline(ss, montoStr, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, tipo, ',');
        getline(ss, clasificacion, ',');
        getline(ss, estado);
        /*getline(ss, saldoStr, ',');*/

        //Convercion de monto y de saldo pendiente
        montoTotal = stof(montoStr);
        /*saldoPendiente=montoTotal;
        /*saldoPendiente = stof(saldoStr);*/

        if (idFactura == idFacturaRegistrada && (tipo == "Proveedor" || tipo == "Acreedor")&&
            clasificacion == "Por pagar" && (estado=="Pendiente" || estado == "pagada_parcial")){

            facturaExiste = true;

            cout << "\nFactura encontrada Saldo pendiente: Q" << fixed << setprecision(2) << saldoPendiente << endl;
            cout << "\n------------------------------------------------\n";
            cout << "Ingrese ID del pago    : "; cin >> idPago;
            cout << "Ingrese fecha del pago : "; cin >> fechaPago;
            cout << "Ingrese monto pagado   : Q "; cin >> montoPago;
            cout << "Ingrese metodo de pago : "; cin >> metodoPago;

            nitEntidad = cuenta;
            tipoEntidad = tipo;

            system ("cls");
            cout << "\n--------- Resumen de la informacion ingresada ---------\n";
            cout << "ID Pago         :" << idPago << endl;
            cout << "Fecha del pago  :" << fechaPago << endl;
            cout << "Metodo del pago :" << metodoPago << endl;
            cout << "Monto a Pagar   : Q " << fixed << setprecision(2) << montoPago << endl;
            cout << "Saldo Actual    : Q " << saldoPendiente << endl;
            cout << "Nit entidad      :" << nitEntidad << endl;
            cout << "Tipo Entidad    :" << tipoEntidad << endl;

            cout << "\n Esta seguro de guardar esta informacion? (S/N): ";
            cin >> confirmar;

            if (confirmar == 's' || confirmar == 'S') {
                if (montoPago > saldoPendiente) {
                    cout << "El monto ingresado excede al valor del saldo (Q" << saldoPendiente << ")\n";
                    estadoPago = "rechazado";
                    montoPago =0;
                } else if (montoPago < 0) {
                    cout << "El monto no puede ser menor a cero" << endl;
                    estadoPago = "rechazado";
                    montoPago = 0;
                } else {
                    saldoPendiente -=montoPago;

                    if (saldoPendiente == 0) {
                        estado = "solvente";
                        estadoPago = "ejecutado";
                    } else {
                        estado = "pagada_parcial";
                        estadoPago = "ejecutado";
                    }
                    //Registro en bitacora si se actualiza el saldo pendiente
                    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "UPDF"); //Actualizacion de facturas
                }
            } else {
                estadoPago ="rechazado";
                montoPago=0;
            }
            // Guardar factura actualizada
            fileTemporal << idFactura << "," << nombre << "," << cuenta << "," << fixed << setprecision(2)
            << montoTotal << "," << fecha << "," << hora << "," << tipo << "," << clasificacion << ","
            << estado << "," << fixed << setprecision(2) << saldoPendiente << "\n";


        } else {
            //Copia de la factura sin cambios
            fileTemporal << lineaFactura << endl;
        }
    }

    fileFacturas.close();
    fileTemporal.close();

    if (!facturaExiste) {
        cout << "\nFactura no valida, ya solvente o no corresponde a un proveedor/acreedor.\n";
        remove("facturas_temporal.bin");
        system("pause");
        return;
    }
    // Reemplazar archivo original
    remove("facturas.bin");
    rename("facturas_temporal.bin", "facturas.bin");

    filePagos.open("pagos.bin", ios::app | ios::out | ios::binary);
    if (!filePagos){
        cout << "No se encontro informacion..." << endl;
        system("pause");
        return;
    }

    filePagos << idPago << left << setw(15) << idFactura << left << setw(15) << fechaPago << left
        << setw(15) << fixed << setprecision(2) << montoPago << left << setw(15) << metodoPago
        << left << setw(15) << nitEntidad << left << setw(15) << tipoEntidad << left << setw(15) << estadoPago << endl;

    filePagos.close();

    if (estadoPago == "rechazado") {
        cout << "\nEl pago fue rechazado y registrado como tal\n";
    } else {
        cout << "\nPago registrado exitosamente\n";
    }
    system("pause");

    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "AddP"); //Registrar pagos
}

void pago::listarPagosPorProveedor(){
    system("cls");
    fstream filePagos;

    string idIngresado;
    int total=0;

    cout << "\n--------- Lista de pagos a proveedor o acreedor ---------\n" << endl;
    cout << "Ingrese Nit del proveedor o acreedor: ";
    cin >> idIngresado;

    filePagos.open("pagos.bin", ios::in | ios::binary);
    if (!filePagos) {
        cout << "No se encontro informacion..." << endl;
        system("pause");
        return;
    }

    cout << "\nPagos registrados para el ID: " << idIngresado << endl;
    cout << "----------------------------------------------------------------------------------\n";
    cout << left << setw(10) << "ID Pago|" << left << setw(10) << "Factura|" << left << setw(10) << "Fecha|"
         << left << setw(10) << "Monto|" << left << setw(10) << "Metodo|" << left << setw(10) << "Nit Entidad|"
         << left << setw(10) << "Tipo Entidad|" << left << setw(10) << "Estado" << endl;
    cout << "----------------------------------------------------------------------------------\n";

    while (filePagos >> idPago >> idFactura >> fechaPago >> montoPago >> metodoPago >> nitEntidad >> tipoEntidad >> estadoPago) {
        if (nitEntidad == idIngresado) {
            total++;
            cout << left << setw(10) << idPago << "|" << left << setw(10) << idFactura << "|" << left << setw(10) << fechaPago << "|"
                 << left << setw(10) << fixed << setprecision(2) << montoPago << "|" << left << setw(10) << metodoPago << "|"
                 << left << setw(10) << nitEntidad << "|" << left << setw(10) << tipoEntidad << "|"  << left << setw(10) << estadoPago << "|" << endl;
        }
    }

    if (total == 0) {
        cout << "\nEl ID Ingresado no cuenta con pagos\n";
    }else{
        cout << "El ID " << idIngresado << "tiene un total de " << total << "pagos." << endl;

    }
    filePagos.close();
    system("pause");
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "SeaPE"); //Mostrar pagos por entidad

}

void pago::listarHistorialPagos(){
    system("cls");
    fstream filePagos;

    filePagos.open("pagos.bin", ios::in | ios::binary);
    if (!filePagos) {
        cout << "No se encontro informacion..." << endl;
        system("pause");
        return;
    }

    cout << "\n------------- Historial de pagos -------------\n" << endl;
    cout << left << setw(15) << "ID Pago" << left << setw(15) << "ID Factura"
         << left << setw(15) << "Fecha" << left << setw(15) << "Monto" << left << setw(15) << "Metodo"
         << left << setw(15) << "Nit Entidad" << left << setw(15) << "Tipo Entidad" << left << setw(15) << "Estado" << endl;
    cout << "----------------------------------------------------------------------------------\n";

    while (filePagos >> idPago >> idFactura >> fechaPago >> montoPago >> metodoPago >> nitEntidad >> tipoEntidad >> estadoPago){
        cout << left << setw(15) << idPago<< left << setw(15) << idFactura<< left << setw(15) << fechaPago
             << left << setw(15) << fixed << setprecision(2) << montoPago << left << setw(15) << metodoPago
             << left << setw(15) << nitEntidad << left << setw(15) << tipoEntidad << left << setw(15) << estadoPago << endl;
    }
    filePagos.close();
    system("pause");
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "HP"); //Historial Pagos
}

void pago::mostrarCuentasPorPagar(){
    fstream fileFacturas;
    //Variables de factura
    string lineaFactura;
    string idFactura, nombre, cuenta, montoStr, fecha, hora, tipo, clasificacion, estado/*, saldoStr*/;
    float montoTotal/*, saldoPendiente*/;
    bool facturasPendientes=false;

    system("cls");
    cout << "\n------------- Facturas Pendientes de Pago -------------\n" << endl;
    cout << left << setw(15) << "ID Factura" << left << setw(15) << "Nombre" << left << setw(15) << "Cuenta"
         << left << setw(15) << "Monto Total" << left << setw(15) << "Fecha"  << left << setw(15) << "Tipo"
         << left << setw(15) << "Clasificacion" << left << setw(15) << "Estado" << left << setw(15) << "Saldo Pendiente" << endl;
    cout << "----------------------------------------------------------------------------------\n";

    fileFacturas.open("facturas.bin", ios::in | ios::binary);
    if (!fileFacturas) {
        cout << "No se encontro informacion..." << endl;
        system("pause");
        return;
    }

    //Lectura del archivo factura line por linea y la guarda en lineaFactura
    while (getline(fileFacturas, lineaFactura)){
        stringstream ss(lineaFactura);//Ayuda a extrar cada campo de forma individual
        //Extrae el flujo ss hasta la primera coma
        getline(ss, idFactura, ',');
        getline(ss, nombre, ',');
        getline(ss, cuenta, ',');
        getline(ss, montoStr, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, tipo, ',');
        getline(ss, clasificacion, ',');
        getline(ss, estado, ',');
        /*getline(ss, saldoStr, ',');*/

        //Convercion de monto y de saldo
        montoTotal = stof(montoStr);
        /*saldoPendiente = stof(saldoStr);*/

        if (estado == "Pendiente" || estado == "pagada_parcial"){
            facturasPendientes = true;
            cout << left << setw(15) << idFactura << left << setw(15) << nombre << left << setw(15) << cuenta
                 << left << setw(15) << "Q. " << montoStr << left << setw(15) << fecha << left << setw(15) << tipo
                 << left << setw(15) << clasificacion << left << setw(15) << estado/* << left << setw(15) << "Q " << saldoStr */<< endl;
        }
    }

    fileFacturas.close();
    if (!facturasPendientes){
        cout << "\n No ahi facturas pendientes de pago..." << endl;
    }
    system("pause");
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "ViCP"); //Mostrar Cuentas por pagar
}

void pago::buscarPagosPorFacura(){
    fstream fileFacturas, filePagos;

    //Variables de factura
    string lineaFactura;
    string idFactura, nombre, cuenta, montoStr, fecha, hora, tipo, clasificacion, estado/*, saldoStr*/;
    float montoTotal/*, saldoPendiente*/;

    string idFacturaBuscada;
    bool facturaExiste= false;
    int total = 0;

    system("cls");
    cout << "\n------------- Buscar Pagos por Factura -------------\n" << endl;
    cout << "Ingrese el ID de la factura que desea buscar: ";
    cin >> idFacturaBuscada;

    fileFacturas.open("facturas.bin", ios::in | ios::binary);
    if (!fileFacturas) {
        cout << "No se encontro informacion..." << endl;
        system("pause");
        return;
    }

    //Lectura del archivo factura line por linea y la guarda en lineaFactura
    while (getline(fileFacturas, lineaFactura)){
        stringstream ss(lineaFactura);//Ayuda a extrar cada campo de forma individual
        //Extrae el flujo ss hasta la primera coma
        getline(ss, idFactura, ',');
        getline(ss, nombre, ',');
        getline(ss, cuenta, ',');
        getline(ss, montoStr, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, tipo, ',');
        getline(ss, clasificacion, ',');
        getline(ss, estado, ',');
        /*getline(ss, saldoStr, ',');*/

        //Convercion de monto y de saldo
        montoTotal = stof(montoStr);
        /*saldoPendiente = stof(saldoStr);*/

        if (idFactura == idFacturaBuscada){
            facturaExiste=true;

            cout << "\n--- Datos de la Factura ---\n";
            cout << "ID Factura     : " << idFactura << endl;
            cout << "Entidad        : " << nombre << " (" << tipo << ")" << endl;
            cout << "Cuenta        : " << cuenta << endl;
            cout << "Monto total    : Q" << fixed << setprecision(2) << montoTotal << endl;
            /*cout << "Saldo pendiente: Q" << saldoPendiente << endl;*/
            cout << "Estado actual  : " << estado << endl;
            break;
        }
    }
    fileFacturas.close();

    if (!facturaExiste){
        cout << "\nFactura no encontrada...\n";
        system("pause");
        return;
    }

    filePagos.open("pagos.bin", ios::in | ios::binary);
    if (!filePagos) {
        cout << "No se encontro informacion..." << endl;
        system("pause");
        return;
    }

    cout << "\n--- Pagos Asociados a la Factura ---\n";
    while (filePagos >> idPago >> idFactura >> fechaPago >> montoPago >> metodoPago >> nitEntidad >> tipoEntidad >> estadoPago){
        if (idFactura==idFacturaBuscada){
            total++;
            cout << "\nID Pago       : " << idPago;
            cout << "\nNit Entidad   :" << nitEntidad;
            cout << "\nFecha         : " << fechaPago;
            cout << "\nMonto pagado  : Q" << fixed << setprecision(2) << montoPago;
            cout << "\nMetodo de pago: " << metodoPago;
            cout << "\nEstado        : " << estadoPago << endl;
            cout << "-------------------------------------\n";
        }
    }

    filePagos.close();

     if (total == 0) {
        cout << "\n\nNo se encontraron pagos asociados a la factura con ID: " << idFacturaBuscada << endl;
    }else{
        cout << "\n\nEl total de pagos registrados para la factura " << idFacturaBuscada << "es de: " << total << endl;
    }

    system("pause");
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "SeaPF"); //Buscar pagos por factura
}

void pago::reportePagos(){
    system("cls");
    fstream file, reportefile;
    int found = 0;

    cout<<"\n----------------------------- Reporte de Pagos -----------------------------\n"<<endl;
    file.open("pagos.bin", ios::in | ios::binary);
    reportefile.open("reporte_Pagos.txt", ios::app | ios::out);

    if(!file){
        cout << "\n\tNo hay informacion de pagos...\n";
        reportefile << "No hay informacion en pagos.txt \n\n";
    } else{
        cout << left << setw(15) << "ID Pago" << setw(15) << "ID Factura" << setw(15) << "Fecha Pago"
             << setw(15) << "Monto" << setw(15) << "Metodo Pago" << setw(15) << "ID Entidad"
             << setw(15) << "Tipo" << setw(15) << "Estado" << endl;
        cout << "----------------------------------------------------------------------------------\n";

        reportefile << "----------------------------- REPORTE DE PAGOS -----------------------------\n";
        reportefile << left << setw(15) << "ID Pago" << setw(15) << "ID Factura" << setw(15) << "Fecha Pago"
             << setw(15) << "Monto" << setw(15) << "Metodo Pago" << setw(15) << "ID Entidad"
             << setw(15) << "Tipo" << setw(15) << "Estado" << endl;
        reportefile << "----------------------------------------------------------------------------------\n";

        file >> idPago >> idFactura >> fechaPago >> montoPago >> metodoPago >> nitEntidad >> tipoEntidad >> estadoPago;

        while (!file.eof()){
            found++;

            cout << left << setw(15) << idPago << setw(15) << idFactura << setw(15) << fechaPago
                 << setw(15) << fixed << setprecision(2) << montoPago << setw(15) << metodoPago
                 << setw(15) << nitEntidad << setw(15) << tipoEntidad << setw(15) << estadoPago << endl;

            reportefile << left << setw(15) << idPago << setw(15) << idFactura << setw(15) << fechaPago
                 << setw(15) << fixed << setprecision(2) << montoPago << setw(15) << metodoPago
                 << setw(15) << nitEntidad << setw(15) << tipoEntidad << setw(15) << estadoPago << endl;

            file >> idPago >> idFactura >> fechaPago >> montoPago >> metodoPago >> nitEntidad >> tipoEntidad >> estadoPago;
        }

        reportefile << "----------------------------------------------------------------------------------\n\n";

        if (found == 0){
            cout << "\n\tNo hay pagos registrados...\n";
            reportefile << "No hay pagos registrados...\n\n";
        }
    }
    file.close();
    reportefile.close();

    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "ReP"); //Reporte pagos
}

void pago::reporteCuentasPorPagar(){
    system("cls");
    fstream file, reportefile;
    int found = 0;

    //Variables de factura
    string lineaFactura;
    string idFactura, nombre, cuenta, montoStr, fecha, hora, tipo, clasificacion, estado/*, saldoStr*/;
    float montoTotal/*, saldoPendiente*/;

    cout<<"\n---------------------- Reporte de cuentas por pagar ----------------------\n"<<endl;

    file.open("facturas.bin", ios::in | ios::binary);
    reportefile.open("reporte_PorPagar.txt", ios::app | ios::out);

    if(!file){
        cout << "\n\tNo hay informacion de pagos...\n";
        reportefile << "No hay informacion en pagos.txt \n\n";
    } else{
        cout << left << setw(15) << "ID Factura" << setw(15) << "Nombre" << setw(15) << "Cuenta"
             << setw(15) << "Monto Total" << setw(15) << "Fecha" << setw(15) << "Hora" << setw(15) << "Tipo"
             << setw(15) << "Clasificacion" << setw(15) << "Estado" << setw(15) << "Saldo Pendiente" << endl;
        cout << "----------------------------------------------------------------------------------\n";

        reportefile << "-------------------------- REPORTE DE CUENTAS POR PAGAR --------------------------\n";
        reportefile << left << setw(15) << "ID Factura" << setw(15) << "Nombre" << setw(15) << "Cuenta"
                    << setw(15) << "Monto Total" << setw(15) << "Fecha" << setw(15) << "Hora" << setw(15) << "Tipo"
                    << setw(15) << "Clasificacion" << setw(15) << "Estado" << setw(15) << "Saldo Pendiente" << endl;
        reportefile << "----------------------------------------------------------------------------------------\n";


        //Lectura del archivo factura line por linea y la guarda en lineaFactura
    while (getline(file, lineaFactura)){
        stringstream ss(lineaFactura);//Ayuda a extrar cada campo de forma individual
        //Extrae el flujo ss hasta la primera coma
        getline(ss, idFactura, ',');
        getline(ss, nombre, ',');
        getline(ss, cuenta, ',');
        getline(ss, montoStr, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, tipo, ',');
        getline(ss, clasificacion, ',');
        getline(ss, estado, ',');
        /*getline(ss, saldoStr, ',');*/

            //Convercion de monto y de saldo
            montoTotal = stof(montoStr);
            /*saldoPendiente = stof(saldoStr);*/

            if ((tipo== "Proveedor" || tipo == "Acreedor") && (estado=="Pendiente" || estado == "pagada_parcial")){
                found++;

                cout << left << setw(15) << idFactura << setw(15) << nombre << setw(15) << cuenta << setw (15) << montoTotal
                     << setw(15) << fecha << setw(15) << hora << setw(15) << tipo << setw(15) << clasificacion << setw(15) << estado
                     /*<< setw(15) << saldoPendiente */<< endl;

                reportefile << left << setw(15) << idFactura << setw(15) << nombre << setw(15) << cuenta << setw (15) << montoTotal
                            << setw(15) << fecha << setw(15) << hora << setw(15) << tipo << setw(15) << clasificacion << setw(15) << estado
                            /*<< setw(15) << saldoPendiente */<< endl;
            }
        }
        reportefile << "----------------------------------------------------------------------------------------\n";

        if (found == 0){
            cout << "\n\tNo hay pagos registrados...\n";
            reportefile << "No hay pagos registrados...\n\n";
        }
    }

    file.close();
    reportefile.close();

    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(),"8200", "ReCP"); //Reporte cuentas por pagar

}
