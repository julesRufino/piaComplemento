/*
Integrantes: 

Julio Antonio Blanco Rufino 2003632
Adrian Martinez Alvarado 2132997
William Rincon Perez 1823198
*/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cctype>
#include<cstdio>
#include<iomanip>
#include<regex>
#include<set>
#include<stdexcept>

using namespace std;

void LimpiarPantalla();
void MenuPrincipal(char *);
void SubMenu(char *);
void MenuReportes(char *);
void RegistroVuelo();
void RegistroDestinos();
void ListaDeDestinos();
void ReportePorFecha();
void ReporteTotal();
void PresionaParaContinuar();
bool ValidarClave(const string&);
bool ValidarDescripcion(const string&);
bool ValidarPrecio(const string&);
bool ValidarViajeRedondo(const string&);
bool ValidarFecha(const string&);
bool ExistenDestinos();
bool DestinoExiste(const string&);
string ObtenerPrecioDestino(const string&);

int main()
{
    try {
        char opcion, subopcion;
        
        MenuPrincipal(&opcion);
        
        while(opcion != 'd')
        {
            LimpiarPantalla();
            
            switch(opcion)
            {
                case 'a':
                {
                    SubMenu(&subopcion);
                    
                    while(subopcion != '3')
                    {
                        LimpiarPantalla();
                        switch(subopcion)
                        {
                            case '1':
                                RegistroVuelo();
                                break;
                            case '2':
                                RegistroDestinos();
                                break;
                        }
                        SubMenu(&subopcion);
                    }
                    LimpiarPantalla();
                    break;
                }
                
                case 'b':
                    ListaDeDestinos();
                    break;
                
                case 'c':
                {
                    MenuReportes(&subopcion);
                    
                    while(subopcion != '3')
                    {
                        LimpiarPantalla();
                        switch(subopcion)
                        {
                            case '1':
                                ReportePorFecha();
                                break;
                            case '2':
                                ReporteTotal();
                                break;
                        }
                        
                        MenuReportes(&subopcion);
                        
                    }
                    LimpiarPantalla();
                    break;
                }
            }
            
            MenuPrincipal(&opcion);
        }
    }
    catch (const exception& e) {
        cerr << "Error global del programa: " << e.what() << endl;
        PresionaParaContinuar();
        return 1;
    }
    catch (...) {
        cerr << "Error desconocido en el programa!" << endl;
        PresionaParaContinuar();
        return 1;
    }
    
    return 0;
}

void LimpiarPantalla()
{
    system("cls");
}

void MenuPrincipal(char *opcion)
{
    do {
        cout << "===============MENU PRINCIPAL==================" << endl;
        cout << "A. REGISTRO DE VUELOS." << endl;
        cout << "B. LISTADO DE DESTINOS." << endl;
        cout << "C. LISTADO DE VUELOS." << endl;
        cout << "D. SALIR." << endl;
        
        cout << "SELECCIONA UNA OPCION: ";
        cin >> *opcion;
        cin.ignore();
        
        *opcion = tolower(*opcion);
        
        if(*opcion < 'a' || *opcion > 'd') 
            cout << "ERROR: OPCION NO VALIDA (A, B, C o D)!" << endl << endl;
            
    } while(*opcion < 'a' || *opcion > 'd');
}

void SubMenu(char *subopcion)
{
    do {
        cout << "========== REGISTRO DE VUELOS ==========" << endl;
        cout << "1- REGISTRAR VUELO." << endl;
        cout << "2- DAR ALTA DESTINOS." << endl;
        cout << "3- SALIR." << endl;
        cout << "SELECCIONA UNA OPCION: ";
        cin >> *subopcion;
        cin.ignore();
        
        if(*subopcion != '1' && *subopcion != '2' && *subopcion != '3') 
            cout << "ERROR: SOLO SE PERMITE 1, 2 o 3!" << endl << endl;
        
    } while(*subopcion != '1' && *subopcion != '2' && *subopcion != '3');
}

void MenuReportes(char *subopcion)
{
    do {
        cout << "========== LISTADO DE VUELOS ==========" << endl;
        cout << "1- REPORTE POR FECHA." << endl;
        cout << "2- REPORTE TOTAL." << endl;
        cout << "3- SALIR." << endl;
        cout << "SELECCIONA UNA OPCION: ";
        cin >> *subopcion;
        cin.ignore();
        
        if(*subopcion != '1' && *subopcion != '2' && *subopcion != '3') {
            cout << "ERROR: SOLO SE PERMITE 1, 2 o 3!" << endl << endl;
        }
        
    } while(*subopcion != '1' && *subopcion != '2' && *subopcion != '3');
}


bool ValidarClave(const string& clave)
{
    regex patron("[A-Z]_[0-9]{4}");
    return regex_match(clave, patron);
}

bool ValidarDescripcion(const string& descripcion)
{
    regex patron("[A-Z][a-zA-Z ]*");
    return regex_match(descripcion, patron);
}

bool ValidarPrecio(const string& precio)
{
    regex patron("[0-9]{3,5}\\.[0-9]{2}");
    return regex_match(precio, patron);
}

bool ValidarViajeRedondo(const string& viaje)
{
    regex patron("si|no");
    return regex_match(viaje, patron);
}

bool ValidarFecha(const string& fecha)
{
    regex patron("[0-9]{2}-[0-9]{2}-[0-9]{4}");
    return regex_match(fecha, patron);
}

bool ExistenDestinos()
{
    try {
        FILE* destinos = fopen("destinos.txt", "r");
        
        if(destinos == NULL)
            return false;
        
        fseek(destinos, 0, SEEK_END);
        long size = ftell(destinos);
        fclose(destinos);
        
        return size > 0;
    }
    catch (const exception& e) {
        cerr << "Error al verificar existencia de destinos: " << e.what() << endl;
        return false;
    }
}

bool DestinoExiste(const string& destino)
{
    try {
        char clave[50], descripcion[50], precio[50];
        bool existe = false;
        
        FILE* archivo = fopen("destinos.txt", "r");
        
        if(archivo == NULL)
            return false;
        
        while(fscanf(archivo, "%49[^,],%49[^,],%49[^\n]\n", clave, descripcion, precio) == 3) 
        {
            if(string(descripcion) == destino) 
            {
                existe = true;
                break;
            }
        }
        
        fclose(archivo);
        return existe;
    }
    catch (const exception& e) {
        cerr << "Error al verificar destino: " << e.what() << endl;
        return false;
    }
}

string ObtenerPrecioDestino(const string& destino) 
{
    try {
        char clave[50], descripcion[50], precio[50];
        string precio_str = "";
        
        FILE* archivo = fopen("destinos.txt", "r");
        
        if(archivo == NULL)
        {
            throw runtime_error("No se pudo abrir el archivo de destinos");
        }
        
        while(fscanf(archivo, "%49[^,],%49[^,],%49[^\n]\n", clave, descripcion, precio) == 3)
        {
            if(string(descripcion) == destino)
            {
                precio_str = string(precio);
                break;
            }
        }
        
        fclose(archivo);
        
        if(precio_str.empty())
            throw runtime_error("El destino '" + destino + "' no existe");
        
        return precio_str;
    }
    catch (const exception& e) {
        cerr << "Error al obtener precio: " << e.what() << endl;
        return "";
    }
}

void RegistroDestinos() 
{
    try {
        string clave, descripcion, precio;
        
        FILE* destinos = fopen("destinos.txt", "a");
        
        if(destinos == NULL)
        {
            throw runtime_error("No se pudo abrir el archivo de destinos para escritura");
        }
        
        do
        {
            cout << "INGRESA LA CLAVE (Formato: A_1234): ";
            getline(cin, clave);
            
            if(!ValidarClave(clave))  
                cout << "Error: Formato de clave invalido.(Ejemplo: A_1234)"<< endl;
                 
        } while(!ValidarClave(clave));  
        
        
        do
        {
            cout << "INGRESA LA DESCRIPCION: ";
            getline(cin, descripcion);
            
            if(!ValidarDescripcion(descripcion))  
                cout << "Error: Formato de descripcion invalido. Debe comenzar con letra mayuscula" << endl;
                
        } while(!ValidarDescripcion(descripcion));  
        
        
        do
        {
            cout << "INGRESA EL PRECIO (Formato: 1234.56): ";
            getline(cin, precio);
            
            if(!ValidarPrecio(precio)) 
                cout << "Error: Formato de precio invalido.(Ejemplo: 1234.56)" << endl;
                
        } while(!ValidarPrecio(precio));  
        
        fprintf(destinos, "%s,%s,%s\n", clave.c_str(), descripcion.c_str(), precio.c_str());
        fclose(destinos);
        
        cout << "Destino registrado exitosamente!" << endl;
        PresionaParaContinuar();
    }
    catch (const exception& e) {
        cerr << "Error en registro de destinos: " << e.what() << endl;
        PresionaParaContinuar();
    }
}

void RegistroVuelo() 
{
    try {
        string destino, viaje_redondo, fecha_ida, fecha_regreso;
        
        if(!ExistenDestinos())
        {
            cout << "No hay destinos registrados. Debe registrar destinos primero." << endl;
            PresionaParaContinuar();
            return;
        }
        
        FILE* viajes = fopen("viajes.txt", "a");
        
        if(viajes == NULL) 
        {
            throw runtime_error("No se pudo abrir el archivo de viajes para escritura");
        }
        
        do 
        {
            cout << "INGRESA EL DESTINO: ";
            getline(cin, destino);
            
            if(!ValidarDescripcion(destino)) 
            {
                cout << "Error: Formato de descripcion invalido. Debe comenzar con letra mayuscula" << endl;
                continue;
            }
            
            if(!DestinoExiste(destino)) 
            {
                cout << "Error: El destino no existe en el archivo de destinos" << endl;
                continue;
            }
            break;
            
        } while(true);
        
        string precio_str = ObtenerPrecioDestino(destino);
        
        if(precio_str.empty())
        {
            fclose(viajes);
            PresionaParaContinuar();
            return;
        }
        
        double precio = stod(precio_str);
        cout << "Precio del destino: " << precio_str << endl;
        
        do
        {
            cout << "VIAJE REDONDO (si/no): ";
            getline(cin, viaje_redondo);
            
            if(!ValidarViajeRedondo(viaje_redondo)) 
                cout << "Error: Formato de viaje redondo invalido. Solo se permite 'si' o 'no'" << endl;
            
        } while(!ValidarViajeRedondo(viaje_redondo)); 
        
        
        if(viaje_redondo == "si") 
            cout << "Precio total (redondo): " << (precio * 2) << endl;
        
        
        do
        {
            cout << "FECHA DE IDA (DD-MM-AAAA): ";
            getline(cin, fecha_ida);
            
            if(!ValidarFecha(fecha_ida)) 
                cout << "Error: Formato de fecha invalido. Debe ser DD-MM-AAAA" << endl;
            
        } while(!ValidarFecha(fecha_ida));  
        
        
        if(viaje_redondo == "si") 
        {
            do
            {
                cout << "FECHA DE REGRESO (DD-MM-AAAA): ";
                getline(cin, fecha_regreso);
                
                if(!ValidarFecha(fecha_regreso))  
                    cout << "Error: Formato de fecha invalido. Debe ser DD-MM-AAAA" << endl;
                    
            } while(!ValidarFecha(fecha_regreso));  
        } 
        else 
            fecha_regreso = "N/A";
        
        fprintf(viajes, "%s,%s,%s,%s\n", destino.c_str(), viaje_redondo.c_str(), 
                fecha_ida.c_str(), fecha_regreso.c_str());
        fclose(viajes);
        
        cout << "Vuelo registrado exitosamente!" << endl;
        PresionaParaContinuar();
    }
    catch (const exception& e) {
        cerr << "Error en registro de vuelo: " << e.what() << endl;
        PresionaParaContinuar();
    }
}

void ListaDeDestinos()
{
    try {
        char clave[50], descripcion[50], precio[50];
        
        FILE* destinos = fopen("destinos.txt", "r");
        
        if(destinos == NULL)
        {
            cout << "No hay destinos registrados." << endl;
            PresionaParaContinuar();
            return;
        }
        
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        cout << setw(50) << "LISTA DE DESTINOS" << endl;
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        cout << left << setw(15) << "CLAVE";  
        cout << left << setw(35) << "DESCRIPCION";
        cout << left << setw(15) << "PRECIO" << endl;
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        
        while(fscanf(destinos, "%49[^,],%49[^,],%49[^\n]\n", clave, descripcion, precio) == 3) {
            cout << left << setw(15) << clave;  
            cout << left << setw(35) << descripcion;
            cout << left << setw(15) << precio << endl;
        }
        
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        
        fclose(destinos);
        PresionaParaContinuar();
    }
    catch (const exception& e) {
        cerr << "Error al mostrar lista de destinos: " << e.what() << endl;
        PresionaParaContinuar();
    }
}

void ReportePorFecha()
{
    try {
        string fecha;
        char destino[50], viaje_redondo[10], fecha_ida[20], fecha_regreso[20];
        char cl[50], desc[50], prec[50];
        bool hayVuelos = false;
        
        
        do
        {
            cout << "INGRESA LA FECHA (DD-MM-AAAA): ";
            getline(cin, fecha);
            
            if(!ValidarFecha(fecha))  
                cout << "Error: Formato de fecha invalido. Debe ser DD-MM-AAAA" << endl;
                
        } while(!ValidarFecha(fecha));  
        
        FILE* viajes = fopen("viajes.txt", "r");
        
        if(viajes == NULL)
        {
            cout << "No hay vuelos registrados." << endl;
            PresionaParaContinuar();
            return;
        }
        
        set<string> destinosMostrados;
        
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        cout << setw(50) << "VUELOS PARA LA FECHA: " + fecha << endl;
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        cout << left << setw(15) << "CLAVE";  
        cout << left << setw(35) << "DESTINO";
        cout << left << setw(15) << "PRECIO" << endl;
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        
        while(fscanf(viajes, "%49[^,],%9[^,],%19[^,],%19[^\n]\n", 
              destino, viaje_redondo, fecha_ida, fecha_regreso) == 4)
        {
            
            if(string(fecha_ida) == fecha && 
               destinosMostrados.find(string(destino)) == destinosMostrados.end()) 
            {
                
                string precio = ObtenerPrecioDestino(string(destino));
                
                if(precio.empty())
                    continue;
                
                string clave = "";
                
                FILE* destinos = fopen("destinos.txt", "r");
                if(destinos != NULL)
                {
                    while(fscanf(destinos, "%49[^,],%49[^,],%49[^\n]\n", cl, desc, prec) == 3) 
                    {
                        if(string(desc) == string(destino))
                        {
                            clave = string(cl);
                            break;
                        }
                    }
                    fclose(destinos);
                }
                
                cout << left << setw(15) << clave;  
                cout << left << setw(35) << destino;
                cout << left << setw(15) << precio << endl;
                
                destinosMostrados.insert(string(destino));
                hayVuelos = true;
            }
        }
        
        if(!hayVuelos) 
            cout << "No hay vuelos para la fecha especificada." << endl;
        
        
        cout << setfill('=') << setw(80) << "" << endl;
        cout << setfill(' ');
        
        fclose(viajes);
        PresionaParaContinuar();
    }
    catch (const exception& e) {
        cerr << "Error en reporte por fecha: " << e.what() << endl;
        PresionaParaContinuar();
    }
}

void ReporteTotal()
{
    try {
        char destino[50], viaje_redondo[10], fecha_ida[20], fecha_regreso[20];
        bool hayVuelos = false;
        
        FILE* viajes = fopen("viajes.txt", "r");
        
        if(viajes == NULL)
        {
            cout << "No hay vuelos registrados." << endl;
            PresionaParaContinuar();
            return;
        }
        
        set<string> vuelosMostrados;
        
        cout << setfill('=') << setw(100) << "" << endl;
        cout << setfill(' ');
        cout << setw(50) << "TODOS LOS VUELOS REGISTRADOS" << endl;
        cout << setfill('=') << setw(100) << "" << endl;
        cout << setfill(' ');
        cout << left << setw(25) << "DESTINO";  
        cout << left << setw(15) << "REDONDO";
        cout << left << setw(15) << "FECHA IDA";
        cout << left << setw(15) << "FECHA REGRESO" << endl;
        cout << setfill('=') << setw(100) << "" << endl;
        cout << setfill(' ');
        
        while(fscanf(viajes, "%49[^,],%9[^,],%19[^,],%19[^\n]\n", 
              destino, viaje_redondo, fecha_ida, fecha_regreso) == 4) {
            
            string vueloKey = string(destino) + string(viaje_redondo) + 
                             string(fecha_ida) + string(fecha_regreso);
            
            if(vuelosMostrados.find(vueloKey) == vuelosMostrados.end()) {
                cout << left << setw(25) << destino;  
                cout << left << setw(15) << viaje_redondo;
                cout << left << setw(15) << fecha_ida;
                cout << left << setw(15) << fecha_regreso << endl;
                
                vuelosMostrados.insert(vueloKey);
                hayVuelos = true;
            }
        }
        
        if(!hayVuelos) 
            cout << "No hay vuelos registrados." << endl;
        
        cout << setfill('=') << setw(100) << "" << endl;
        cout << setfill(' ');
        
        fclose(viajes);
        PresionaParaContinuar();
    }
    catch (const exception& e) {
        cerr << "Error en reporte total: " << e.what() << endl;
        PresionaParaContinuar();
    }
}

void PresionaParaContinuar()
{
    cout << endl;
    cout << "Presiona ENTER para continuar...";
    cin.get();
    LimpiarPantalla();
}
