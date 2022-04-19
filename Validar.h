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
* void
*****/

void validar(punteroTicket *ticket, int NTicket,Servicios *servicio, int Nservicios){
    char rutActual[10];
    int posServ,posServActual;
    int mensual = 0;
    bool opcion = true;
    
    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);

    //Considera invalidos los que no cumplen con ningun servicio y los que superan la cantidad mensual.
    for(int i = 0; i<NTicket;i++){
        //si el rut del ticket que sigue es distinto al actual
        if(strcmp(ticket[i].punteroT.rut_funcionario,rutActual) != 0){
            strcpy(rutActual,ticket[i].punteroT.rut_funcionario);
        }
        for(int j = 0; j<Nservicios;j++){ //si la hora cumple con 1 servicio es true si no es false
            if(strcmp(servicio[j].horaFin, servicio[j].horaInicio)<= 0){ //if que compara si la hora final es menor o igual a la incial para tener en cuenta que empieza en un dia y termina en otro
                if(strcmp(ticket[i].punteroT.time,servicio[j].horaInicio)>= 0 || strcmp(ticket[i].punteroT.time,servicio[j].horaFin)<=0){
                    opcion =  true;
                    posServ = j; //si la hora cumple cuarda la posicion del servicio que cumplió
                    break;
                }else{
                    opcion = false;
                }
            }else{
                if(strcmp(ticket[i].punteroT.time,servicio[j].horaInicio)>= 0 && strcmp(ticket[i].punteroT.time,servicio[j].horaFin)<=0){
                    opcion = true;
                    posServ = j; //si la hora cumple cuarda la posicion del servicio que cumplió
                    break;
                }
                else{
                    opcion = false;
                }
            }
        }
        if(opcion  == false){ //si la opcion es falsa significa que no cumplió con ninguna hora
            ticket[i].valido = false; //si no cumple con ningun servicio el ticket es falso
            mensual = 0;

        }else{
            /*revisa si la posicion del servicio actual es igual a la guardada en posServ.
            En caso de que lo sea significa que seguimos en el mismo servicio*/
            if(posServActual == posServ){
                if(mensual >= servicio[posServ].limMensuales){ //si el ticket supera a los limites mensuales lo marca falso
                    ticket[i].valido = false;
                
                }else{
                    mensual++; 
                }    
            }else{ // en caso que no sean iguales, se toma el nuevo servicio y se reinicia la variable mensual
                posServActual = posServ;
                mensual = 0;
            }
            
            
        }

        ticket[i].nombre = servicio[posServ].nombre;
    }   /*PD: como estan ordenados por rut y hora, entonces cuando llega a una hora que deja de cumplir
        o a un servicio distinto que posServ significa que ya dejo todos los ticket de ese servicio atras,
        y como estan ordenados por horas se entienden que son los mensuales.*/


    //ordenamoos ahora por dias
    orden(ticket,NTicket,2);

    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);
    int diaActual = ticket[0].punteroT.day_of_month;

    //Condsidera invalidos los que superen el limite diarios de ticket en x dia
    for(int i = 0; i<NTicket; i++){
        //si el rut del ticket que sigue es distinto al actual
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
                for(int j = 0; j<Nservicios;j++){//recorre el Nservicios buscando en cual hora es igual
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


/*****
 * void imprimirYmaxMT
******
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
* void
*****/
void imprimirYmaxMT(punteroTicket *ticket,int NTicket, Servicios *servicio,int Nservicios){
    // ordenamos de acuerdo a las horas 
    orden(ticket,NTicket,3);
    char rutActual[10];

    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);
    int valido = 0,total = 0;
    for(int i = 0; i<NTicket; i++){
        //si el rut del ticket que sigue es distinto al actual
        if(strcmp(ticket[i].punteroT.rut_funcionario,rutActual) != 0){
            //si es distinto al actual entonces significa que ese rut no volvera a salir por lo tanto le imprime en pantalla los datos correspondientes
            cout << rutActual << " " << valido << "/" << total << endl; 
            strcpy(rutActual,ticket[i].punteroT.rut_funcionario);
            total = 1;
            valido = 0; //reinicia contador de total y validos
            //si el nuevo ticket es valido lo contabiliza
            if(ticket[i].valido){
                valido++;
            }

        }else{ 
            /*compara si el ticket es valido y total es menor a 100, si eso ocurre entonces contabiliza otro valido
            en caso contrario simplemente no lo contabiliza y sigue contando los totales */
            if(ticket[i].valido && total < 100){
                valido++;
            }
            total++;
        }
    }
    //imprime el ultimo rut que faltaba
    cout << rutActual <<" "<< valido << "/" << total<< endl; 
}