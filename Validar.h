/*****
 * void validar
******
* Funcion encargada de validar los ticket, con cada requerimiento que pide: si cumple dentro de una hora, si cumple con el lim diario,
  si cumple con el limMensual, si cumple con los limMensualTotal, los que no coumplan los marca como invalidos.
******
* Input:
* punteroTicket *arreglo: puntero al arreglo de Tickets,
  int inicio: valor inicial de la cadena a ordenar, 
  int mitad: valor que particiona la zona de la cadena evaluada
  int final: entero que marca el fin de la seccion del arreglo solicitado
  int opcion: opcion que indica si se quiere ordenar mediante, rut, horas o dia
* .......
******
* Returns:
* Void
*****/

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


/******
*Funcion encargada de mostrar en pantalla el rut, los ticket validos y ticket totales.Tambien verifica si cumple con el limTotalMensual
******
* Input:
* punteroTicket *arreglo: puntero al arreglo de Tickets,
  int inicio: valor inicial de la cadena a ordenar, 
  int mitad: valor que particiona la zona de la cadena evaluada
  int final: entero que marca el fin de la seccion del arreglo solicitado
  int opcion: opcion que indica si se quiere ordenar mediante, rut, horas o dia
* .......
******
* Returns:
* Void
*****/

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