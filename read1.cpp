# include <iostream>
# include <fstream>
# include <cstring> 
# include <string.h> 
using namespace std;

struct Ticket {
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};

struct TicketValido {
    Ticket ticket;
    bool valido;
};

struct Servicios{
    string nombre;
    int limDiarios, limMensuales;
    char horaInicio[5],horaFin[5];
};

void merge(Ticket *arreglo,int inicio, int mitad, int final,int opcion){
    int i,j,k;
    int elementosIzq = mitad - inicio + 1;
    int elementosDer = final - mitad;

    Ticket izquierda[elementosIzq];
    Ticket derecha[elementosDer];

    for(int i = 0; i < elementosIzq; i++){
        izquierda[i] = arreglo[inicio+i];
    }
    for(int j = 0; j < elementosDer; j++){
        derecha[j] = arreglo[mitad + 1 + j];
    }

    i = 0;
    j = 0;
    k = inicio;

    while(i < elementosIzq && j < elementosDer){
        switch(opcion){ // si se busca el rut, pueden ser 3 casos
                       
            case 1: // opcion = 1 comparan rut
                if(strcmp(izquierda[i].rut_funcionario,derecha[j].rut_funcionario) <= 0 ){
                    arreglo[k] = izquierda[i];
                    i++;
                }else{
                    arreglo[k] = derecha[j];
                    j++;
                }
                k++;
                break;
            
            case 2: // opcion = 2 comparan dias
                if(izquierda[i].day_of_month <= derecha[j].day_of_month){
                arreglo[k] = izquierda[i];
                i++;
                }else{
                    arreglo[k] = derecha[j];
                    j++;
                }
                k++;
                break;

            case 3: // opcion = 3 comparan fechas
                if(strcmp(izquierda[i].time,derecha[j].time) <= 0 ){
                arreglo[k] = izquierda[i];
                i++;
                }else{
                    arreglo[k] = derecha[j];
                    j++;
                }
                k++;
                break;
        }  

    }

    while(j < elementosDer){
        arreglo[k] = derecha[j];
        j++;
        k++;
    }

    while(i < elementosIzq){
        arreglo[k] = izquierda[i];
        i++;
        k++;
    }

}

void mergeSort(Ticket *arreglo,int inicio, int final, int opcion){
    if(inicio < final){
        int mitad = inicio + (final - inicio)/2;
        mergeSort(arreglo,inicio,mitad,opcion);
        mergeSort(arreglo,mitad+1,final,opcion);
        merge(arreglo,inicio,mitad,final,opcion);
    }
}

void imprimirArreglo(Ticket *arreglo, int n, int opcion){
    switch (opcion){
        case 1:
            for(int i = 0; i < n; i++){
                cout << arreglo[i].rut_funcionario << " ";
            }
            break;

        case 2: 
            for(int i = 0; i < n; i++){
                cout << arreglo[i].day_of_month << " ";
            }
            break;
        case 3:
            for(int i = 0; i < n; i++){
                cout << arreglo[i].time << " ";
            }
            break;
 
    }
    cout << endl;
}

int main(){
    int NTicket;
    int NServicios;
    int Cantidad_Funcionarios = 1;

    //Guardar Servicios en el arreglo "Servicios"
    ifstream fp;

    fp.open("Servicios.txt");
    fp >> NServicios;

    Servicios servicio[NServicios];

    for(int s = 0; s < NServicios; s++){
        fp >> servicio[s].nombre;
        fp >> servicio[s].limDiarios;
        fp >> servicio[s].limMensuales;
        fp >> servicio[s].horaInicio;
        fp >> servicio[s].horaFin;
    }

    for(int s = 0; s < NServicios; s++){
        cout << servicio[s].limDiarios << endl;
    }

    fp.close();

    //Guardar tickets en el arreglo "readt"
    fp.open("Tickets.dat", ios::binary);
    
    if (!fp.is_open () ) {
        cerr << " no se pudo abrir el archivo " << endl ;
        exit (1);
    }
    
    fp.seekg(0);
    fp.read((char*)&NTicket, sizeof(int));

    Ticket *readt = new Ticket[NTicket];
    TicketValido *READT = new TicketValido[NTicket];

    for(int i = 0; i < NTicket; i++){
        fp.seekg(sizeof(int) + sizeof(Ticket)*i);
        fp.read((char*)&readt[i], sizeof(Ticket));
        fp.read((char*)&READT[i].ticket, sizeof(Ticket));
        TicketValido t = *(READT + i);
        t.valido = true;
    }
    
    //Obtener el numer
    for(int j = 1; j < NTicket; j++){
        bool exist = false;
        for(int r = 0; r < Cantidad_Funcionarios; r++){
            if((strcmp(readt[r].rut_funcionario, readt[j].rut_funcionario) == 0)){
                exist = true;
            }
        }
        if(!exist){
            Cantidad_Funcionarios++;
        }
    }
    fp.close();

    char rutActual[10];
    strcpy(rutActual,readt[0].rut_funcionario);

    int inicio = 0;
    for(int i = 0; i<NTicket; i++){
        if(strcmp(readt[i].rut_funcionario,rutActual) != 0){
            strcpy(rutActual,readt[i].rut_funcionario);
            mergeSort(readt,inicio,i-1,2);
            inicio = i;
        }
    }

    mergeSort(READT,0,NTicket-1,1);

    strcpy(rutActual,READT[0].ticket.rut_funcionario);
    int invalido = 0;

    int limite = 100;
    int contador = 0;
    for(int j = 0; j < NTicket; j++){
        if(strcmp(READT[j].ticket.rut_funcionario, rutActual)){
            contador++;
        }else{
            if(contador > limite){
                invalido++;
            }
            //strcpy(rutActual,readt[j].rut_funcionario);
            break;
        }
    }


    cout << invalido;

    mergeSort(readt,inicio,NTicket-1,2);
    //imprimirArreglo(readt,NTicket,1);
    mergeSort(readt,0,NTicket-1,1);
    //imprimirArreglo(readt,NTicket,1);
    delete[] readt;

    return 0;
}



