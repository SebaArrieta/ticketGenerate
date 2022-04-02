# include <iostream>
# include <fstream>
# include <cstring> 
using namespace std;

struct Ticket {
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};








// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
/*void merge(int array[], int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
  
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
  
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
  
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}
  
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
// void mergeSort(int array[], int const begin, int const end)
// {
//     if (begin >= end)
//         return; // Returns recursively
  
//     auto mid = begin + (end - begin) / 2;
//     mergeSort(array, begin, mid);
//     mergeSort(array, mid + 1, end);
//     merge(array, begin, mid, end);
// }
  
// // UTILITY FUNCTIONS
// // Function to print an array
// void printArray(int A[], int size)
// {
//     for (auto i = 0; i < size; i++)
//         cout << A[i] << " ";
// }*/
  
// ejemplo de como funcionaria con un codigo bien equisde
/*int main()
    cout << "Given array is \n";
    printArray(arr, arr_size);
  
    mergeSort(arreglo de tickets[ticket personal[0]], 0, arr_size - 1);
  
    cout << "\nSorted array is \n";
    printArray(arr, arr_size);
    return 0;
}
  
// This code is contributed by Mayank Tyagi
// This code was revised by Joshua Estes

ss  */ 
 














/*struct ticketsEmitidos{
    int *day_of_month;
    char *time;
    bool Valido;
};

struct Funcionario{
    char *rut;
    int cantidad_tickets = 0;
    
};*/

char *splitRut(int NTicket, Ticket *readt, int Cantidad_Func){

    int Cantidad_Func = 1;

    for(int j = 1; j < NTicket; j++){
        Ticket f2= *(readt + j);
        bool exist = false;
        for(int r = 0; r < Cantidad_Func; r++){
            Ticket f1 = *(readt + r); 
            if((strcmp(f2.rut_funcionario, f1.rut_funcionario) == 0)){
                exist = true;
            }
        }
        
        if(!exist){
            Ticket f2Change = *(readt + Cantidad_Func + 1);
            *(readt + Cantidad_Func) = f2;
            *(readt + j) = f2Change;

            Cantidad_Func++;
        }else{
            exist = false;
        }
    }
}

int main(){
    int NTicket;

    int Cantidad_Funcionarios = 1;

    //Funcionario *dataFuncionario = new Funcionario[Cantidad_Funcionarios];

    ifstream fp;
    fp.open("casoT1/tickets.dat", ios::binary);
    if (!fp.is_open () ) {
        cerr << " no se pudo abrir el archivo " << endl ;
        exit (1);
    }

    fp.seekg(0);
    fp.read((char*)&NTicket, sizeof(int));

    Ticket t;

    Ticket *readt = new Ticket[NTicket];

    
    for(int i = 0; i < NTicket; i++){
        string a = readt[i].rut_funcionario;
        cout << a <<endl;
        fp.seekg(sizeof(int) + sizeof(Ticket)*i);
        fp.read((char*)&t, sizeof(Ticket));
        *(readt+i) = t;
    }


    for(int j = 1; j < NTicket; j++){
        Ticket f2= *(readt + j);
        bool exist = false;
        for(int r = 0; r < Cantidad_Funcionarios; r++){
            Ticket f1 = *(readt + r);
            if((strcmp(f2.rut_funcionario, f1.rut_funcionario) == 0)){
                exist = true;
            }
        }
        
        if(!exist){
            Ticket f2Change = *(readt + Cantidad_Funcionarios + 1);
            *(readt + Cantidad_Funcionarios) = f2;
            *(readt + j) = f2Change;

            Cantidad_Funcionarios++;
        }else{
            exist = false;
        }
    }

    /*int n1 = (Cantidad_Funcionarios + 1);
    int n2 = (NTicket-1) - Cantidad_Funcionarios;

    Ticket LSide[n1];
    Ticket RSide[n2];

    for(int l = 0; l < n1; l++){
        LSide[l] = *(readt+l);
    }

    for(int r = 1; r < n2; r++){
        RSide[r] = *(readt + (n1 + r - 1));
    }

    int r = 0;
    int l = 0;

    for (int i = 0; i < NTicket; i++){
        if(strcmp(LSide[l].rut_funcionario, RSide[r].rut_funcionario){

        }
    }*/


    fp.close();
    return 0;
}
