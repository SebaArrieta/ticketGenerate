# include <iostream>
# include <string>
# include <fstream>
# include <cstdlib>
using namespace std;

struct Ticket {
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};


int main(){
    int NTicket;
    cout << "Numero de tickets" << endl; 
    cin >> NTicket; 

    int NFuncionarios;
    cout << "Numero de Funcionarios" << endl; 
    cin >> NFuncionarios; 

    string *RutId = new string[NFuncionarios];

    Ticket TicketDict[NTicket];

    for(int j = 0; j < NFuncionarios; j++){
        char rut[10];
        for(int i = 0; i < 9; i++){
            rut[i] = '0' + (0 + rand() % 9);
        }
        rut[9] = '\0';
        *(RutId+j) = rut;
    }

    for(int j = 0; j < NTicket; j++){
        string rut = *(RutId + (0 + rand() % NFuncionarios));
        for(int i = 0; i < 10; i++){
            TicketDict[j].rut_funcionario[i] = *(rut.c_str()+ i);
        }

        TicketDict[j].time[0] = '0' + (0 + rand() % 3);
        TicketDict[j].time[1] = '0' + (0 + rand() % 9);
        TicketDict[j].time[2] = ':';
        TicketDict[j].time[3] = '0' + (0 + rand() % 6);
        TicketDict[j].time[4] = '0' + (0 + rand() % 9);
        TicketDict[j].time[5] = '\0';

        TicketDict[j].day_of_month = 0 + rand() % 31;

    }

    delete [] RutId;

    ofstream out;

    out.open("Tickets.dat", ios::binary);
    if (!out.is_open () ) {
        cerr << " no se pudo abrir el archivo " << endl ;
        exit (1);
    }
    out.write((char*)&NTicket, sizeof(int));
    
    out.write((char*)&TicketDict, NTicket*sizeof(Ticket));

    out.close();
    return 0;
}