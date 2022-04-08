# include <iostream>
# include <fstream>
# include <cstring> 
using namespace std;

struct Ticket {
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};

struct punteroTicket{
    Ticket punteroT;
    string nombre = "";
    bool valido = true;
};

struct Servicios{
    string nombre;
    int limDiarios, limMensuales,diarios = 0, mensuales =  0;
    char horaInicio[5],horaFin[5];
};


void merge(punteroTicket *arreglo,int inicio, int mitad, int final,int opcion){
    int i,j,k;
    int elementosIzq = mitad - inicio + 1;
    int elementosDer = final - mitad;

    punteroTicket izquierda[elementosIzq];
    punteroTicket derecha[elementosDer];

    for(int i = 0; i < elementosIzq; i++){
        izquierda[i] = arreglo[inicio + i];
    }
    for(int j = 0; j < elementosDer; j++){
        derecha[j] = arreglo[mitad + 1 + j];
    }

    i = 0;
    j = 0;
    k = inicio;

    while(i < elementosIzq && j < elementosDer){
        switch(opcion){ // si se busca el rut, pueden ser 3 casos, faltan implementar los otros 
                       
            case 1: // opcion = 1 comparan rut
                if(strcmp(izquierda[i].punteroT.rut_funcionario,derecha[j].punteroT.rut_funcionario) <= 0 ){
                arreglo[k] = izquierda[i];
                i++;
                }else{
                    arreglo[k] = derecha[j];
                    j++;
                }
                k++;
                break;
            
            case 2: // opcion = 2 comparan dias
                if(izquierda[i].punteroT.day_of_month <= derecha[j].punteroT.day_of_month){
                arreglo[k] = izquierda[i];
                i++;
                }else{
                    arreglo[k] = derecha[j];
                    j++;
                }
                k++;
                break;

            case 3: // opcion = 3 comparan fechas
                if(strcmp(izquierda[i].punteroT.time,derecha[j].punteroT.time) <= 0 ){
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

void mergeSort(punteroTicket *arreglo,int inicio, int final, int opcion){
    if(inicio < final){
        int mitad = inicio + (final - inicio)/2;
        mergeSort(arreglo,inicio,mitad,opcion);
        mergeSort(arreglo,mitad+1,final,opcion);
        merge(arreglo,inicio,mitad,final,opcion);
    }
}

void orden(punteroTicket *ticket, int NTicket,int opcion){
    char rutActual[10];
    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);

    // ordenamos despues de por rut por hora o por dia
    int inicio = 0;
    for(int i = 0; i<NTicket; i++){
        if(strcmp(ticket[i].punteroT.rut_funcionario,rutActual) != 0){
            strcpy(rutActual,ticket[i].punteroT.rut_funcionario);
            mergeSort(ticket,inicio,i-1,opcion);

            inicio = i;
        }
    }
    mergeSort(ticket,inicio,NTicket-1,opcion);
}

void validar(punteroTicket *ticket, int NTicket,Servicios *servicio, int Nservicios){
    char rutActual[10];
    int posServ,posServActual;
    int mensual = 0;
    bool opcion = true;
    
    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);

    //Funcion que considera invalidos los que no cumplen con ningun servicio y los que superan la cantidad mensual.
    for(int i = 0; i<NTicket;i++){
        if(strcmp(ticket[i].punteroT.rut_funcionario,rutActual) != 0){
            strcpy(rutActual,ticket[i].punteroT.rut_funcionario);
        }
        for(int j = 0; j<Nservicios;j++){ //si la hora cumple con 1 servicio es true si no es false
            if(strcmp(servicio[j].horaFin, servicio[j].horaInicio)<= 0){
                if(strcmp(ticket[i].punteroT.time,servicio[j].horaInicio)>= 0 || strcmp(ticket[i].punteroT.time,servicio[j].horaFin)<=0){
                    opcion =  true;
                    posServ = j;
                    break;
                }else{
                    opcion = false;
                }
            }else{
                if(strcmp(ticket[i].punteroT.time,servicio[j].horaInicio)>= 0 && strcmp(ticket[i].punteroT.time,servicio[j].horaFin)<=0){
                    opcion = true;
                    posServ = j;
                    break;
                }
                else{
                    opcion = false;
                }
            }
        }
        if(opcion  == false){
            ticket[i].valido = false; //si no cumple con ningun servicio el ticket es falso
            mensual = 0;

        }else{
            //si cumple con un servicio, pero el servicio que le sigue no es el mismo
            if(posServActual == posServ){
                if(mensual >= servicio[posServ].limMensuales){
                    ticket[i].valido = false;
                
                }else{
                    mensual++; 
                }    
            }else{
                posServActual = posServ;
                mensual = 0;
            }
            
            
        }

        ticket[i].nombre = servicio[posServ].nombre;
    } //PD: como estan ordenados por rut y hora, entonces cuando llega a una hora que deja de cumplir
    // o a un servicio distinto que posServ significa que ya dejo todos los ticket de ese servicio atras,
        // y como estan ordenados por horas se entienden que son los mensuales, no sabemos si diarios ya que pueden ser distintos dias


    //ordenamoos ahora por dias
    orden(ticket,NTicket,2);

    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);
    int diaActual = ticket[0].punteroT.day_of_month;

    for(int i = 0; i<NTicket; i++){
        if(strcmp(ticket[i].punteroT.rut_funcionario,rutActual) != 0){
            strcpy(rutActual,ticket[i].punteroT.rut_funcionario);
            for(int j = 0 ; j<Nservicios; j++){ //reiniciamos los diarios
                servicio[j].diarios = 0;
            }
            diaActual = ticket[0].punteroT.day_of_month;
            
        }else{
            if(diaActual != ticket[i].punteroT.day_of_month){
                for(int j = 0 ; j<Nservicios; j++){ //reiniciamos los diarios
                    servicio[j].diarios = 0;
                }
                diaActual = ticket[i].punteroT.day_of_month;

            }else{
                for(int j = 0; j<Nservicios;j++){
                    if(ticket[i].valido && servicio[j].nombre == ticket[i].nombre){ // si el ticket es valido y tiene el mismo nombre de servicio
                        if(servicio[j].diarios >= servicio[j].limDiarios){ //en caso que supere el lim diario el ticket es falso;
                            ticket[i].valido = false;
                        }else{
                            servicio[j].diarios++;
                        }
                        break;                    
                    }
                }
            }
        }
    }    
}

void imprimirYmaxMT(punteroTicket *ticket,int NTicket, Servicios *servicio,int Nservicios){
        // ordenamos de acuerdo a las horas 
    orden(ticket,NTicket,3);
    char rutActual[10];

    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);
    int valido = 0,total = 0;
    for(int i = 0; i<NTicket; i++){
        if(strcmp(ticket[i].punteroT.rut_funcionario,rutActual) != 0){
            cout << rutActual << " " << valido << "/" << total << endl; 
            strcpy(rutActual,ticket[i].punteroT.rut_funcionario);
            total = 1;
            valido = 0;
            if(ticket[i].valido){
                valido++;
            }

        }else{
            if(ticket[i].valido && total <= 100){
                valido++;
            }
            total++;
        }
    }
    cout << rutActual <<" "<< valido << "/" << total<< endl; 
}


int main(){
    int NTicket,Nservicios;

    ifstream fp;

    fp.open("servicios.txt");
    fp >> Nservicios;

    Servicios servicio[Nservicios];

    for(int s = 0; s < Nservicios; s++){
        fp >> servicio[s].nombre;
        fp >> servicio[s].limDiarios;
        fp >> servicio[s].limMensuales;
        fp >> servicio[s].horaInicio;
        fp >> servicio[s].horaFin;
    }

    fp.close();

    fp.open("tickets.dat", ios::binary);
    if (!fp.is_open () ) {
        cerr << " no se pudo abrir el archivo " << endl ;
        exit (1);
    }
    fp.seekg(0);
    fp.read((char*)&NTicket, sizeof(int));

    Ticket *readt = new Ticket[NTicket];
    punteroTicket ticket[NTicket];
    for(int i = 0; i < NTicket; i++){
        fp.read((char*)&readt[i], sizeof(Ticket));
        ticket[i].punteroT = readt[i];
    }

    mergeSort(ticket,0,NTicket-1,1);
    validar(ticket,NTicket,servicio,Nservicios);
    imprimirYmaxMT(ticket,NTicket,servicio,Nservicios);
    
    delete[] readt;
    fp.close();
    return 0;
}


