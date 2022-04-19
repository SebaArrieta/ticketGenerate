# include <iostream>
# include <fstream>
# include <cstring> 
# include <stdlib.h>
using namespace std;

/*****
* void merge
******
* Funcion encargada de ordenar acorde al parametro solicitado del struct Ticket contenido en PunteroTicket, esto se ordena de menor a mayor
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
void merge(punteroTicket *arreglo,int inicio, int mitad, int final,int opcion){
    int i,j,k;
    int elementosIzq = mitad - inicio + 1;
    int elementosDer = final - mitad;

    //crea un arreglo de puntero ticket tanto para los arreglos que se encuentren por la izquierda y para los de la derecha
    punteroTicket izquierda[elementosIzq];
    punteroTicket derecha[elementosDer];

    //añade los elementos correspondientes a ambos arreglos
    for(int i = 0; i < elementosIzq; i++){
        izquierda[i] = arreglo[inicio + i];
    }
    for(int j = 0; j < elementosDer; j++){
        derecha[j] = arreglo[mitad + 1 + j];
    }

    i = 0;
    j = 0;
    k = inicio;

    //while que reccorre y compara los elementos de la izquiera y de la derecha para ordenarlos
    while(i < elementosIzq && j < elementosDer){
        switch(opcion){ // si se busca el rut, pueden ser 3 casos     
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


/*****
* void mergeSort
******
* Función que se llama de manera recursiva hasta quedar separada en arreglos de 1 elemento, luego llama a la función merge para ir ordenando mientras
  vuelve al arreglo original
******
* Input:
* punteroTicket *arreglo: puntero al arreglo de Tickets,
  int inicio: valor inicial de la cadena a ordenar, 
  int final: entero que marca el fin de la seccion del arreglo solicitado
  int opcion: opcion que indica si se quiere ordenar mediante, rut, horas o dia
* .......
******
* Returns:
* void
*****/
void mergeSort(punteroTicket *arreglo,int inicio, int final, int opcion){
    //caso base para que se deje de cumplir la recursividad
    if(inicio < final){
        int mitad = inicio + (final - inicio)/2;
        mergeSort(arreglo,inicio,mitad,opcion);
        mergeSort(arreglo,mitad+1,final,opcion);
        merge(arreglo,inicio,mitad,final,opcion);
    }
}


/*****
* void  orden
******
* Funcion que busca tomar un arreglo ordenado de rut y luego los ordenarlos aparte de por rut por (dia u hora)
******
* Input:
* punteroTicket *arreglo: puntero al arreglo de Tickets,
  int NTicket: Cantidad de elementos en el arreglo PunteroTicket
  int opcion: opcion que indica si se quiere ordenar mediante: rut, horas o dias
* .......
******
* Returns:
* void
*****/
void orden(punteroTicket *ticket, int NTicket,int opcion){
    char rutActual[10];
    strcpy(rutActual,ticket[0].punteroT.rut_funcionario);

    int inicio = 0;
    /*va recorriendo el arreglo, como están ordenados por rut cuando llegue a un rut distinto al actual
    copia el rut que se encontró y luego llama a la función mergeSort para que ordenene el arreglo solo hasta donde se encontraban los rut iguales */
    for(int i = 0; i<NTicket; i++){
        if(strcmp(ticket[i].punteroT.rut_funcionario,rutActual) != 0){
            strcpy(rutActual,ticket[i].punteroT.rut_funcionario);
            mergeSort(ticket,inicio,i-1,opcion);

            inicio = i;
        }
    }
    mergeSort(ticket,inicio,NTicket-1,opcion);
}

