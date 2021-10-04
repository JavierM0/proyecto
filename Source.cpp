#include <iostream>
#include <time.h>
#include <stdexcept>
#include <thread>
#include <climits>
#include "Empleados.h"

using namespace std;
int numIntentos=0;
bool admin=false;

time_t tiempo;
struct tm * ptm;

void fecha();
void horario();
void validarAdmin();
void informacionEmpleado();
void cambiarSalario();
void cambiarHorario();
void menu();
void cerrarSesion();

int main ()
{
  system ("color 7C");
  thread hilofecha(fecha);
  hilofecha.join();
  menu();
  return 0;
}


/*  Estas instrucciones aplican la funcion time y gmtime, al igual que la estrucutra tm. @see <time.h>
*   Consigue el tiempo y lo basa en la zona GMT (tiempo medio de Greenwich) e imprime el horario
*   de acuerdo al horario de chihuahua
*/
void fecha(){
    time ( &tiempo );
    ptm = gmtime ( &tiempo );
    cout << "Hora en chihuahua: " << (ptm->tm_hour+17)%24<< ":" << ptm->tm_min << endl;
    cout << "fecha de hoy: " << ptm->tm_mday<< "/" << ptm->tm_mon+1<< "/" << ptm->tm_year+1900 << endl;
}
/* Las instrucciones utilizan el arreglo de empleados que en si guarda variables de estructuras cada una de nombre
*  empleado1 a empleado8, en el array de 0 a 7 e imprime nombres/entrada (hora y minuto)/salida (hora y minuto)
*/
void horario(){
    cout<<endl;
    cout << "Nombre Entrada Salida" << endl;
    for(int i=0; i<8; i++){
        cout << arrayEmpleados[i]->nombre << " "
        << arrayEmpleados[i]->hora_entrada << ":" << arrayEmpleados[i]->min_entrada << " "
        << arrayEmpleados[i]->hora_salida << ":" << arrayEmpleados[i]->min_salida << endl;
    }
    cout<<endl;
}
/*@throws runtime_error si la variable intento es diferente a la variable contraseña
* Las instrucciones aplican el bool pasw_necesaria para mantener el ciclo de while donde se ingresa desde la
* consola la variable intento, y si esta es igual a la variables pasw la variable global admin se convierte
* es verdadera y le permite ingresar a funciones de cambio, de otra manera permanece en el ciclo dentro de 5 intentos
* si estos se acaban el se bloquea el usuario y debe reiniciar el programa para intentarlo de nuevo
*/

void validarAdmin(){
    bool pasw_necesaria=true;
    string pasw="1234";
    string intento;

    try{
    if(admin==true){throw admin;}
    }
    catch(bool admin){
        cout << "Usted ya ingreso" <<endl;
        return;
    }
    while(pasw_necesaria==true){
    if(numIntentos>4){ cout<<"Opcion bloqueada, regresando a menu"<<endl; return;}
    cout<<endl;
    cout <<"Ingrese contrasena numerica (ingrese 8 para regresar al menu)"<<endl;
    cin >> intento;
    try{
    if(intento=="8"){return;}
    if(intento==pasw){ admin=true;}
    if(intento!=pasw){ numIntentos++; throw runtime_error("contrasena incorrecta");}
    }
    catch(runtime_error &error){
        cerr << error.what() <<endl;
        cout << "Ingrese 8 para regresar al menu, o intente de nuevo (intentos disponibles:" << 5-numIntentos << ")" << endl;
        intento="";
        system("pause");
        system ("cls");
		continue;
    }
    pasw_necesaria=false;
    admin=true;
    }
}
/*@throw runtime_error si la variable x (de opciones) es diferente al rango de 0 a 8
*@throw invalid_argument si se ingreso un diferente caracter a integro en la variable x @see climits
* Las instrucciones verifican que el usuario se encuentre en modo de administrador, sino regresa al menu
* pide un numero de 0 a 8 con la variable x si este ingresa un caracter diferente a integro, pasa a la excepcion
* donde se quita la bandera de error en cin, e ignora el caracter ingresado y se vuelve a llamar la funcion,
* si se sobrepasa el rango sale la excepcion y se vuelve a llamar la funcion, de manera si se ingresa 8 regresa al menu
* y de 0 a 7 imprime la informacion de un empleado usando un apuntador a la base nombre (primer miembro de la
* de la estructura) y el ciclo for hasta salario y se vuelve a llamar la funcion
*/
void informacionEmpleado(){
    if(admin==false){cout << "Necesita ser administrador para realizar esta accion" << endl; return;}
    int x;
    cout<<endl;
    cout << "Elija empleado a observar (nombre/salario/entrada/salida) de 0 a 7 o ingrese 8 para regresar " << endl;
    try{
    cin >> x;
    if(cin.fail()){ throw invalid_argument("Seleccion Invalida");}
    if(x==8){return;}
    if(x<0 || x>8){ throw runtime_error("Seleccion invalida");}
    string* base = (string*)(&arrayEmpleados[x]->nombre);
        for (int i=0; i<6; i++){
        cout << base[i] << "  "; }
        cout<<endl;
        system("pause");
        system("cls");
        informacionEmpleado();
    }
    catch(runtime_error &error){
        cerr << error.what() << endl;
        system("pause");
        system("cls");
        informacionEmpleado();
    }
    catch(invalid_argument &error){
        cerr << error.what() << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
        system("cls");
        informacionEmpleado();
    }
}
/*@throw runtime_error si la variable x pasa del rango 0 a 8
*@throw int error si se pasa el rango de 0 a 8 en la variable x @see climits
*@throw invalid_argument si el string no puede ser convertido a flotante
* Valida si es administrador, desde consola toma el numero de empleado a modificar, muestra el salario actual y pide
* ingresar un salario nuevo del array empleados y se llama de nuevo la funcion hasta ingresar 8 y hacer return al menu, * en caso de error remueve la bandera de error en cin y ignora lo
* ingresado y se vuelve a llamar la funcion
*/
void cambiarSalario(){
    if(admin==false){cout << "Necesita ser administrador para realizar esta accion" << endl; return;}
    bool nuevo_salario=true, empleado = false;
    int x;
    string y;
	while(empleado == false){
	    try{
	    cout << "Ingrese de 0 a 7 para cambiar el horario de un empleado particular, o 8 para regresar al menu" << endl;
	    cin >> x;
	    if(x==8){empleado = true;return;}
	    if(x<0 || x>8){ throw runtime_error("Error al ingresar el numero de empleado");}else empleado = true;
	    }
	    catch(runtime_error &error){
	        cerr << error.what() << endl;
	        cin.clear();
	        cin.ignore(INT_MAX, '\n');
	        system("pause");
	        system("cls");
	    }
	}
    if(x>=0 || x<8){
        while (nuevo_salario==true){
        cout << "Emplead@: "
        << arrayEmpleados[x]->nombre
        << " salario actual:" << arrayEmpleados[x]->salario << endl;
            try{
        cout << "Ingrese nuevo salario" << endl;
        cin >> y;
        if(stof(y)<0 || stof(y)>SCHAR_MAX){throw 32;}
        (arrayEmpleados[x]->salario)=y;
        nuevo_salario=false;
            }
            catch(int &error){
            cerr<<"Salario Invalido"<< endl;
            system("pause");
            system("cls");
            continue;
            }
            catch(invalid_argument &error){
            cerr << "Salario invalido" <<error.what() << endl;
            cin.clear();
            cin.ignore(SCHAR_MAX, '\n');
            system("pause");
            system("cls");
            continue;
            }
        }
    }
}
/*@throw runtime_error si la variable x pasa del rango 0 a 8
*@throw int error si se pasa el rango de 0 a 8 en la variable x
*@throw invalid_argument si el string no puede ser convertido a flotante @see climits
* Valida si es administrador, desde consola toma el numero de empleado a modificar, muestra el horario actual y pide
* ingresar un horario nuevo del array empleados (entrada hora,min y salida hora,min) y se llama de nuevo la funcion hasta ingresar 8 y hacer return al menu, * en caso de error remueve la bandera de error en cin y ignora lo
* ingresado y se vuelve a llamar la funcion
*/

void cambiarHorario(){
    if(admin==false){cout << "Necesita ser administrador para realizar esta accion" << endl; return;}
    bool nuevo_horario=true, empleado = false;
    int x;
    string entrada_hora, entrada_min, salida_hora, salida_min;
	while(empleado == false){
	    try{
	    cout << "Ingrese de 0 a 7 para cambiar el horario de un empleado particular, o 8 para regresar al menu" << endl;
	    cin >> x;
	    if(x==8){empleado = true;return;}
	    if(x<0 || x>8){ throw runtime_error("Error al ingresar el numero de empleado");}else empleado = true;
	    }
	    catch(runtime_error &error){
	        cerr << error.what() << endl;
	        cin.clear();
	        cin.ignore(INT_MAX, '\n');
	        system("pause");
	        system("cls");
	    }
	}
    if(x>=0 || x<8){
        while (nuevo_horario==true){
        cout << "Emplead@: "
        << arrayEmpleados[x]->nombre
        << " Horario actual " << arrayEmpleados[x]->hora_entrada<< ":" << arrayEmpleados[x]->min_entrada
        << " a " << arrayEmpleados[x]->hora_salida<< ":" << arrayEmpleados[x]->min_salida << endl;
            try{
        cout << "Ingrese nueva hora de entrada ()" << endl;
        cin >> entrada_hora;
        if(stoi(entrada_hora)<0 || stoi(entrada_hora)>24){throw 32;}
        cout << "Ingrese nueva minuto de entrada ()" << endl;
        cin >> entrada_min;
        if(stoi(entrada_min)<0 || stoi(entrada_min)>59){throw 32;}
        cout << "Ingrese nueva hora de salida ()" << endl;
        cin >> salida_hora;
        if(stoi(salida_hora)<0 || stoi(salida_hora)>24){throw 32;}
        cout << "Ingrese nueva minuto de salida ()" << endl;
        cin >> salida_min;
        if(stoi(salida_min)<0 || stoi(salida_min)>59){throw 32;}
        (arrayEmpleados[x]->hora_entrada)=entrada_hora;
        (arrayEmpleados[x]->min_entrada)=entrada_min;
        (arrayEmpleados[x]->hora_salida)=salida_hora;
        (arrayEmpleados[x]->min_salida)=salida_min;
        nuevo_horario=false;
            }
            catch(int &error){
            cerr<<"horario Invalido"<< endl;
            system("pause");
            system("cls");
            continue;
            }
            catch(invalid_argument &error){
            cerr << "Horario invalido" <<error.what() << endl;
            cin.clear();
            cin.ignore(SCHAR_MAX, '\n');
            system("pause");
            system("cls");
            continue;
            }
        }
    }
}
/* Instrucciones observa si esta en modo administrado, en caso verdadero lo cierra (false), imprime mensaje y regresa
*  al menu sino esta en modo administrador lo regresa al menu
*/
void cerrarSesion(){
    if(admin==false){cout << "Necesita haber iniciado sesion como administrador para realizar esta accion" << endl; return;}
    admin=false;
    cout<<"Usted a cerrado sesion exitosamente, hasta luego"<<endl;
}
/*@throw int si variable opc esta fuera del rago 1 a 7 @see climits
* Imprime un menu y pide al usuario ingresar una accion deseada, entonces llama la funcion por medio de un
* puntero a estas, en caso de error limpia la bandera e ignora el caracter ingresado.
*/

void menu(){
void(*p1)();
int opc=0;
do{
    cout<<"**********Bienvenido**********"<<endl;
    cout<<"Que desea hacer a continuacion: "<<endl;
    cout<<"1.- Ver horarios "<<endl;
    cout<<"2.- Iniciar sesion como administrador"<<endl;
    cout<<endl;
    cout<<"**********Funciones de administrador********** "<<endl;
    cout<<"3.- Ver la informacion de uno de los empleados"<<endl;
    cout<<"4.- Cambiar Salarios"<<endl;
    cout<<"5.- Cambiar horarios"<<endl;
    cout<<"6.- Cerrar sesion"<<endl;
    cout<<"7.- Salir"<<endl;
    cout<<"Introdusca su opcion aqui: ";
    cin>>opc;
    try{
    if(opc<1||opc>7){
        throw opc;
    }
        switch(opc){
        case 1:
        p1=horario;
        break;
        case 2:
        p1=validarAdmin;
        break;
        case 3:
        p1=informacionEmpleado;
        break;
        case 4:
        p1=cambiarSalario;
        break;
        case 5:
        p1=cambiarHorario;
        break;
        case 6:
        p1=cerrarSesion;
        break;
        }
    p1();
    }
    catch(int opc){
        cout<<"Opcion no valida intente de nuevo"<<endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    system("pause");
	system("cls");
}while(opc!=7);
}
