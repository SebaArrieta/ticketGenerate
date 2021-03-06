# include <iostream>
# include <fstream>
# include <cstring> 
# include <stdlib.h>
# include "SortAlgoritmo.h"
# include "Validar.h"
using namespace std;

/*****
 * int main
******
* Función encargada de abrir archivo tanto binario como de texto, ambos archivos los recorre extrayendo sus datos
  y pasandolos a un arreglo. Luego llama a otras funciones para poder lograr el objetivo
******
* Input:
* .......
******
* Returns:
* int
*****/
int main(){
    int NTicket,Nservicios;

    ifstream fp;

    //abre el archivo servicios.txt
    fp.open("servicios.txt");
    if (!fp.is_open () ) {
        cout << " no se pudo abrir el archivo " << endl ;
        exit(1);
    }
    fp >> Nservicios;

    Servicios servicio[Nservicios];

    //recorre el archivo servicios.txt guardando los datos
    for(int s = 0; s < Nservicios; s++){
        fp >> servicio[s].nombre;
        fp >> servicio[s].limDiarios;
        fp >> servicio[s].limMensuales;
        fp >> servicio[s].horaInicio;
        fp >> servicio[s].horaFin;
        servicio[s].diarios = 0;
        servicio[s].mensuales = 0;
    }

    fp.close();

    //abre el archivo tickets.dat
    fp.open("tickets.dat", ios::binary);
    if (!fp.is_open () ) {
        cout << " no se pudo abrir el archivo " << endl ;
        exit(1);
    }

    fp.seekg(0); //pone el puntero en la primera posicion del archivo
    fp.read((char*)&NTicket, sizeof(int)); //lee sizeof(int) bytes y los guarda en NTicket

    punteroTicket ticket[NTicket];

    for(int i = 0; i < NTicket; i++){
        fp.read((char*)&ticket[i].punteroT, sizeof(Ticket)); // lee sizeof(Ticket) bytes y los guarda en cada posicion correspondiente del arreglo readt
        ticket[i].valido = true; //establece todos los ticket como validos
    }

    //llama a la funcion encargada de ordenarlos por rut, de menor a mayor
    mergeSort(ticket,0,NTicket-1,1);
    //llama a la funcion encargada de marcar los ticket que no cumplen como invalidos
    validar(ticket,NTicket,servicio,Nservicios);
    //llama a la funcion encargada de hacer la ultima validacion sobre los ticket totales mensuales y luego mostrar datos en pantalla
    imprimirYmaxMT(ticket,NTicket,servicio,Nservicios);
    
    fp.close();
    return 0;
}


