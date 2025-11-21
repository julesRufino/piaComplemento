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
void RegistroVuelo(FILE*);
void RegistroDestinos(FILE*);
void ListaDeDestinos(FILE*);
void ReportePorFecha(FILE*, FILE*);
void ReporteTotal(FILE*);
void PresionaParaContinuar();
bool ValidarClave(const string&);
bool ValidarDescripcion(const string&);
bool ValidarPrecio(const string&);
bool ValidarViajeRedondo(const string&);
bool ValidarFecha(const string&);
bool ExistenDestinos();
bool DestinoExiste(FILE*, const string&);
string ObtenerPrecioDestino(FILE*, const string&);

 main()
{
    int resultadoEjecucion = 0;
    bool ejecucionExitosa = true;
    
    try {
        char opcion, subopcion;
        bool salir = false;
        
        MenuPrincipal(&opcion);
        
        while(!salir && opcion != 'd')
        {
            LimpiarPantalla();
            
            switch(opcion)
            {
                case 'a':
                {
                    SubMenu(&subopcion);
                    
                    bool salirSubmenu = false;
                    while(!salirSubmenu && subopcion != '3')
                    {
                        LimpiarPantalla();
                        
                        try 
                        {
                            FILE* archivo = NULL;
                            
                            if(subopcion == '1') 
                            {
                                archivo = fopen("viajes.txt", "a");
                                if(archivo == NULL) 
                                {
                                    throw runtime_error("No se pudo abrir el archivo de viajes");
                                }
                                RegistroVuelo(archivo);
                            }
                            else if(subopcion == '2') 
                            {
                                archivo = fopen("destinos.txt", "a");
                                if(archivo == NULL) 
                                {
                                    throw runtime_error("No se pudo abrir el archivo de destinos");
                                }
                                RegistroDestinos(archivo);
                            }
                            
                            if(archivo != NULL) 
                            {
                                fclose(archivo);
                            }
                        }
                        catch (const exception& e) 
                        {
                            cerr << "Error: " << e.what() << endl;
                            PresionaParaContinuar();
                        }
                        
                        SubMenu(&subopcion);
                        if(subopcion == '3') 
                        {
                            salirSubmenu = true;
                        }
                    }
                    LimpiarPantalla();
                    break;
                }
                
                case 'b':
                {
                    try 
                    {
                        FILE* archivo = fopen("destinos.txt", "r");
                        if(archivo == NULL) 
                        {
                            cout << "No hay destinos registrados." << endl;
                        } else 
                        {
                            ListaDeDestinos(archivo);
                            fclose(archivo);
                        }
                        PresionaParaContinuar();
                    }
                    catch (const exception& e) 
                    {
                        cerr << "Error al mostrar destinos: " << e.what() << endl;
                        PresionaParaContinuar();
                    }
                    break;
                }
                
                case 'c':
                {
                    MenuReportes(&subopcion);
                    
                    bool salirReportes = false;
                    while(!salirReportes && subopcion != '3')
                    {
                        LimpiarPantalla();
                        
                        try 
                        {
                            if(subopcion == '1') 
                            {
                                FILE* viajes = fopen("viajes.txt", "r");
                                FILE* destinos = fopen("destinos.txt", "r");
                                
                                if(viajes == NULL) 
                                {
                                    cout << "No hay vuelos registrados." << endl;
                                } 
                                else 
                                {
                                    ReportePorFecha(viajes, destinos);
                                    fclose(viajes);
                                    if(destinos != NULL) 
                                    {
                                        fclose(destinos);
                                    }
                                }
                                PresionaParaContinuar();
                            }
                            else if(subopcion == '2') 
                            {
                                FILE* viajes = fopen("viajes.txt", "r");
                                if(viajes == NULL) 
                                {
                                    cout << "No hay vuelos registrados." << endl;
                                } 
                                else 
                                {
                                    ReporteTotal(viajes);
                                    fclose(viajes);
                                }
                                PresionaParaContinuar();
                            }
                        }
                        catch (const exception& e) 
                        {
                            cerr << "Error en reporte: " << e.what() << endl;
                            PresionaParaContinuar();
                        }
                        
                        MenuReportes(&subopcion);
                        if(subopcion == '3') 
                        {
                            salirReportes = true;
                        }
                    }
                    LimpiarPantalla();
                    break;
                }
            }
            
            if(opcion == 'd') 
            {
                salir = true;
            }
            else 
            {
                MenuPrincipal(&opcion);
            }
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error global del programa: " << e.what() << endl;
        PresionaParaContinuar();
        ejecucionExitosa = false;
        resultadoEjecucion = 1;
    }
    
    if (ejecucionExitosa) 
    {
        resultadoEjecucion = 0;
    }
    
    return resultadoEjecucion;
}

void LimpiarPantalla()
{
    system("cls");
}

void MenuPrincipal(char *opcion)
{
    bool opcionValida = false;
    while(!opcionValida) 
    {
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
        {
            cout << "ERROR: OPCION NO VALIDA (A, B, C o D)!" << endl << endl;
        } 
        else 
        {
            opcionValida = true;
        }
    }
}

void SubMenu(char *subopcion)
{
    bool opcionValida = false;
    while(!opcionValida) 
    {
        cout << "========== REGISTRO DE VUELOS ==========" << endl;
        cout << "1- REGISTRAR VUELO." << endl;
        cout << "2- DAR ALTA DESTINOS." << endl;
        cout << "3- SALIR." << endl;
        cout << "SELECCIONA UNA OPCION: ";
        cin >> *subopcion;
        cin.ignore();
        
        if(*subopcion != '1' && *subopcion != '2' && *subopcion != '3') 
        {
            cout << "ERROR: SOLO SE PERMITE 1, 2 o 3!" << endl << endl;
        } 
        else 
        {
            opcionValida = true;
        }
    }
}

void MenuReportes(char *subopcion)
{
    bool opcionValida = false;
    while(!opcionValida) 
    {
        cout << "========== LISTADO DE VUELOS ==========" << endl;
        cout << "1- REPORTE POR FECHA." << endl;
        cout << "2- REPORTE TOTAL." << endl;
        cout << "3- SALIR." << endl;
        cout << "SELECCIONA UNA OPCION: ";
        cin >> *subopcion;
        cin.ignore();
        
        if(*subopcion != '1' && *subopcion != '2' && *subopcion != '3') 
        {
            cout << "ERROR: SOLO SE PERMITE 1, 2 o 3!" << endl << endl;
        } 
        else 
        {
            opcionValida = true;
        }
    }
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
    bool existenDestinos = false;
    
    try 
    {
        FILE* destinos = fopen("destinos.txt", "r");
        
        if(destinos == NULL) 
        {
            existenDestinos = false;
        } 
        else 
        {
            fseek(destinos, 0, SEEK_END);
            long size = ftell(destinos);
            fclose(destinos);
            
            existenDestinos = (size > 0);
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error al verificar existencia de destinos: " << e.what() << endl;
        existenDestinos = false;
    }
    
    return existenDestinos;
}

bool DestinoExiste(FILE* archivo, const string& destino)
{
    bool destinoExiste = false;
    
    try 
    {
        char clave[50], descripcion[50], precio[50];
        
        if(archivo == NULL) 
        {
            destinoExiste = false;
        } else 
        {
            rewind(archivo);
            while(fscanf(archivo, "%49[^,],%49[^,],%49[^\n]\n", clave, descripcion, precio) == 3 && !destinoExiste) 
            {
                if(string(descripcion) == destino) 
                {
                    destinoExiste = true;
                }
            }
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error al verificar destino: " << e.what() << endl;
        destinoExiste = false;
    }
    
    return destinoExiste;
}

string ObtenerPrecioDestino(FILE* archivo, const string& destino) 
{
    string precio_str = "";
    
    try 
    {
        char clave[50], descripcion[50], precio[50];
        bool encontrado = false;
        
        if(archivo == NULL)
        {
            throw runtime_error("No se pudo abrir el archivo de destinos");
        }
        
        rewind(archivo);
        while(fscanf(archivo, "%49[^,],%49[^,],%49[^\n]\n", clave, descripcion, precio) == 3 && !encontrado)
        {
            if(string(descripcion) == destino)
            {
                precio_str = string(precio);
                encontrado = true;
            }
        }
        
        if(!encontrado) 
        {
            throw runtime_error("El destino '" + destino + "' no existe");
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error al obtener precio: " << e.what() << endl;
        precio_str = "";
    }
    
    return precio_str;
}

void RegistroDestinos(FILE* destinos) 
{
    try 
    {
        string clave, descripcion, precio;
        bool claveValida = false, descripcionValida = false, precioValido = false;
        
        if(destinos == NULL)
        {
            throw runtime_error("Archivo de destinos no disponible");
        }
        
        while(!claveValida)
        {
            cout << "INGRESA LA CLAVE (Formato: A_1234): ";
            getline(cin, clave);
            
            if(!ValidarClave(clave))  
                cout << "Error: Formato de clave invalido.(Ejemplo: A_1234)"<< endl;
            else
                claveValida = true;
        }
        
        while(!descripcionValida)
        {
            cout << "INGRESA LA DESCRIPCION: ";
            getline(cin, descripcion);
            
            if(!ValidarDescripcion(descripcion))  
                cout << "Error: Formato de descripcion invalido. Debe comenzar con letra mayuscula" << endl;
            else
                descripcionValida = true;
        }
        
        while(!precioValido)
        {
            cout << "INGRESA EL PRECIO (Formato: 1234.56): ";
            getline(cin, precio);
            
            if(!ValidarPrecio(precio)) 
                cout << "Error: Formato de precio invalido.(Ejemplo: 1234.56)" << endl;
            else
                precioValido = true;
        }
        
        fprintf(destinos, "%s,%s,%s\n", clave.c_str(), descripcion.c_str(), precio.c_str());
        
        cout << "Destino registrado exitosamente!" << endl;
    }
    catch (const exception& e)
    {
        cerr << "Error en registro de destinos: " << e.what() << endl;
    }
}

void RegistroVuelo(FILE* viajes) 
{
    try 
    {
        string destino, viaje_redondo, fecha_ida, fecha_regreso;
        bool destinoValido = false, viajeValido = false, fechaIdaValida = false, fechaRegresoValida = false;
        bool puedeContinuar = true;
        
        if(!ExistenDestinos())
        {
            cout << "No hay destinos registrados. Debe registrar destinos primero." << endl;
            puedeContinuar = false;
        }
        
        if(viajes == NULL) 
        {
            throw runtime_error("Archivo de viajes no disponible");
        }
        
        if (puedeContinuar) 
        {
            FILE* destinos = fopen("destinos.txt", "r");
            if(destinos == NULL) 
            {
                throw runtime_error("No se puede acceder a los destinos registrados");
            }
            
            while(!destinoValido && puedeContinuar)
            {
                cout << "INGRESA EL DESTINO: ";
                getline(cin, destino);
                
                if(!ValidarDescripcion(destino)) 
                {
                    cout << "Error: Formato de descripcion invalido. Debe comenzar con letra mayuscula" << endl;
                }
                else if(!DestinoExiste(destinos, destino)) 
                {
                    cout << "Error: El destino no existe en el archivo de destinos" << endl;
                }
                else
                {
                    destinoValido = true;
                }
            }
            
            string precio_str = ObtenerPrecioDestino(destinos, destino);
            fclose(destinos);
            
            if(precio_str.empty())
            {
                puedeContinuar = false;
            }
            
            if (puedeContinuar) 
            {
                double precio = stod(precio_str);
                cout << "Precio del destino: " << precio_str << endl;
                
                while(!viajeValido)
                {
                    cout << "VIAJE REDONDO (si/no): ";
                    getline(cin, viaje_redondo);
                    
                    if(!ValidarViajeRedondo(viaje_redondo)) 
                        cout << "Error: Formato de viaje redondo invalido. Solo se permite 'si' o 'no'" << endl;
                    else
                        viajeValido = true;
                }
                
                if(viaje_redondo == "si") 
                    cout << "Precio total (redondo): " << (precio * 2) << endl;
                
                while(!fechaIdaValida)
                {
                    cout << "FECHA DE IDA (DD-MM-AAAA): ";
                    getline(cin, fecha_ida);
                    
                    if(!ValidarFecha(fecha_ida)) 
                        cout << "Error: Formato de fecha invalido. Debe ser DD-MM-AAAA" << endl;
                    else
                        fechaIdaValida = true;
                }
                
                if(viaje_redondo == "si") 
                {
                    while(!fechaRegresoValida)
                    {
                        cout << "FECHA DE REGRESO (DD-MM-AAAA): ";
                        getline(cin, fecha_regreso);
                        
                        if(!ValidarFecha(fecha_regreso))  
                            cout << "Error: Formato de fecha invalido. Debe ser DD-MM-AAAA" << endl;
                        else
                            fechaRegresoValida = true;
                    }
                } 
                else 
                {
                    fecha_regreso = "N/A";
                }
                
                fprintf(viajes, "%s,%s,%s,%s\n", destino.c_str(), viaje_redondo.c_str(), 
                        fecha_ida.c_str(), fecha_regreso.c_str());
                
                cout << "Vuelo registrado exitosamente!" << endl;
            }
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error en registro de vuelo: " << e.what() << endl;
    }
}

void ListaDeDestinos(FILE* destinos)
{
    try 
    {
        char clave[50], descripcion[50], precio[50];
        
        if(destinos == NULL)
        {
            cout << "No hay destinos registrados." << endl;
        } 
        else 
        {
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
            
            rewind(destinos);
            while(fscanf(destinos, "%49[^,],%49[^,],%49[^\n]\n", clave, descripcion, precio) == 3) 
            {
                cout << left << setw(15) << clave;  
                cout << left << setw(35) << descripcion;
                cout << left << setw(15) << precio << endl;
            }
            
            cout << setfill('=') << setw(80) << "" << endl;
            cout << setfill(' ');
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error al mostrar lista de destinos: " << e.what() << endl;
    }
}

void ReportePorFecha(FILE* viajes, FILE* destinos)
{
    try 
    {
        string fecha;
        char destino[50], viaje_redondo[10], fecha_ida[20], fecha_regreso[20];
        char cl[50], desc[50], prec[50];
        bool hayVuelos = false;
        bool fechaValida = false;
        
        while(!fechaValida)
        {
            cout << "INGRESA LA FECHA (DD-MM-AAAA): ";
            getline(cin, fecha);
            
            if(!ValidarFecha(fecha))  
                cout << "Error: Formato de fecha invalido. Debe ser DD-MM-AAAA" << endl;
            else
                fechaValida = true;
        }
        
        if(viajes == NULL)
        {
            cout << "No hay vuelos registrados." << endl;
        } 
        else 
        {
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
            
            rewind(viajes);
            while(fscanf(viajes, "%49[^,],%9[^,],%19[^,],%19[^\n]\n", 
                  destino, viaje_redondo, fecha_ida, fecha_regreso) == 4)
            {
                if(string(fecha_ida) == fecha && 
                   destinosMostrados.find(string(destino)) == destinosMostrados.end()) 
                {
                    string precio = "";
                    if(destinos != NULL) 
                    {
                        precio = ObtenerPrecioDestino(destinos, string(destino));
                    }
                    
                    if(!precio.empty())
                    {
                        string clave = "";
                        
                        if(destinos != NULL)
                        {
                            rewind(destinos);
                            while(fscanf(destinos, "%49[^,],%49[^,],%49[^\n]\n", cl, desc, prec) == 3 && clave.empty()) 
                            {
                                if(string(desc) == string(destino))
                                {
                                    clave = string(cl);
                                }
                            }
                        }
                        
                        cout << left << setw(15) << clave;  
                        cout << left << setw(35) << destino;
                        cout << left << setw(15) << precio << endl;
                        
                        destinosMostrados.insert(string(destino));
                        hayVuelos = true;
                    }
                }
            }
            
            if(!hayVuelos) 
                cout << "No hay vuelos para la fecha especificada." << endl;
            
            cout << setfill('=') << setw(80) << "" << endl;
            cout << setfill(' ');
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error en reporte por fecha: " << e.what() << endl;
    }
}

void ReporteTotal(FILE* viajes)
{
    try 
    {
        char destino[50], viaje_redondo[10], fecha_ida[20], fecha_regreso[20];
        bool hayVuelos = false;
        
        if(viajes == NULL)
        {
            cout << "No hay vuelos registrados." << endl;
        } 
        else 
        {
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
            
            rewind(viajes);
            while(fscanf(viajes, "%49[^,],%9[^,],%19[^,],%19[^\n]\n", 
                  destino, viaje_redondo, fecha_ida, fecha_regreso) == 4) 
            {
                string vueloKey = string(destino) + string(viaje_redondo) + 
                                 string(fecha_ida) + string(fecha_regreso);
                
                if(vuelosMostrados.find(vueloKey) == vuelosMostrados.end()) 
                {
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
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error en reporte total: " << e.what() << endl;
    }
}

void PresionaParaContinuar()
{
    cout << endl;
    cout << "Presiona ENTER para continuar...";
    cin.get();
    LimpiarPantalla();
}