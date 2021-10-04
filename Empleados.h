#define Empleados_h
using namespace std;


/*
*estructura de nombre empleado cuyos miembros son de tipo string
* @see std::string
*/
struct Empleado{
    string nombre;
    string salario;
    string hora_entrada;
    string min_entrada;
    string hora_salida;
    string min_salida;
};


Empleado empleado1={"Ana", "25.99", "7", "30", "17", "00"};
Empleado empleado2={"Luis", "40.99", "7", "30", "17", "00"};
Empleado empleado3={"Pedro", "25.99", "7", "30", "17", "00"};
Empleado empleado4={"Martin", "22", "8", "00", "17", "00"};
Empleado empleado5={"Luisa", "30.99", "9", "00", "18", "00"};
Empleado empleado6={"Dayana", "70.99", "7", "30", "17", "00"};
Empleado empleado7={"Fernando", "35.99", "9", "00", "18", "00"};
Empleado empleado8={"Guadalupe", "25.99", "7", "30", "17", "00"};

Empleado* arrayEmpleados[8] ={&empleado1, &empleado2, &empleado3,
&empleado4, &empleado5, &empleado6, &empleado7, &empleado8};
