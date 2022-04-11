# include <iostream>
# include <fstream>
# include <cstring> 
# include <stdlib.h>
# include "SortAlgoritmo.h"
# include "Validar.h"
using namespace std;


int main(){
    int NTicket,Nservicios;

    ifstream fp;

    fp.open("casoT1/servicios.txt");
    fp >> Nservicios;

    Servicios servicio[Nservicios];

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

    fp.open("casoT1/tickets.dat", ios::binary);
    if (!fp.is_open () ) {
        cout << " no se pudo abrir el archivo " << endl ;
        exit(1);
    }
    fp.seekg(0);
    fp.read((char*)&NTicket, sizeof(int));

    Ticket *readt = new Ticket[NTicket];
    punteroTicket ticket[NTicket];
    for(int i = 0; i < NTicket; i++){
        fp.read((char*)&readt[i], sizeof(Ticket));
        ticket[i].punteroT = readt[i];
        ticket[i].valido = true;
    }

    mergeSort(ticket,0,NTicket-1,1);
    validar(ticket,NTicket,servicio,Nservicios);
    imprimirYmaxMT(ticket,NTicket,servicio,Nservicios);
    
    delete[] readt;
    fp.close();
    return 0;
}


