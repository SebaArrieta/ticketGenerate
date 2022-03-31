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

    Ticket readt;

    ifstream fp;
    fp.open("Tickets.dat", ios::binary);
    if (!fp.is_open () ) {
        cerr << " no se pudo abrir el archivo " << endl ;
        exit (1);
    }

    fp.seekg(0);
    fp.read((char*)&NTicket, sizeof(int));

    for(int i = 0; i < NTicket; i++){
        fp.seekg(sizeof(int) + sizeof(Ticket)*i);
        fp.read((char*)&readt, sizeof(Ticket));
        cout<<readt.day_of_month<<endl;
    }

    fp.close();
    return 0;
}