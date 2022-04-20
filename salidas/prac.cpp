
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

struct TicketStr {
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};

class Ticket{
    public:
        char rut_funcionario[10];
        int day_of_month;
        char time[6];

    public:

        Ticket() {;};
        ~Ticket() {;};

        void setRut(){
            std::cout<<"Rut:"<<"\n";
            std::cin>>rut_funcionario;
        };

        void setDay(){
            std::cout<<"Day:"<<"\n";
            std::cin>>day_of_month;
        };

        void setTime(){
            std::cout<<"Time:"<<"\n";
            std::cin>>time;
        };
};

int main(){
    std::ofstream out;

    int Nticket;
    std::cout<<"Cantidad de tickets\n";
    std::cin>>Nticket;

    Ticket CreateTicket[Nticket];

    for(int i = 0; i < Nticket; i++){
        CreateTicket[i].setRut();
        CreateTicket[i].setDay();
        CreateTicket[i].setTime();
    };

    out.open("tickets.dat", std::ios::binary);

    if (!out.is_open () ) {
        std::cerr<<" Error el abrir el archivo ";
        return 1; // error
    }

    out.write((char*)&Nticket, sizeof(int));

    for(int i = 0; i < Nticket; i++){
        TicketStr Add;

        strcpy(CreateTicket[i].rut_funcionario, Add.rut_funcionario);
        strcpy(CreateTicket[i].time, Add.time);
        Add.day_of_month = CreateTicket[i].day_of_month;

        out.write((char*)&Add, sizeof(TicketStr));
    }
    
    out.close();

    return 0;

}