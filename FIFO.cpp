#include <iostream>
#include <algorithm>
using namespace std;


class Process {
   public:
    int name,entrance_time, burst_time, exit_time ;

 Process(int name, int  entranceTime, int ProcessTime) {
        this->name = name;
        this->burst_time= ProcessTime;
        this->entrance_time = entranceTime;
    }

  Process() {

    }

};
void fifo(Process processes[],int numberOfProcesses){


int i,j;
int waiting_time=0;
long int average_waiting_time=0;
int response_time=0;
int average_response_time=0;
cout<<"Waiting Time Of" ;
//print wtime for each process
for ( i = 1; i < numberOfProcesses; i++)
{
waiting_time=processes[i].exit_time-processes[i].burst_time;
cout<<"process ["<<i<<"] = "<<waiting_time;
average_waiting_time+=waiting_time;


}
//print avwtime for  processes
cout<<'Average Waiting Time = '<<average_waiting_time/numberOfProcesses;



//print wtime for each process
for (  j = 0; j < numberOfProcesses; j++)
{
response_time=waiting_time+processes[i].burst_time;
cout<<"process ["<<i<<"] = "<<response_time;
average_response_time+=response_time;

}

//print avrtime for  processes

cout<<'Average Waiting Time = '<<(int)average_waiting_time/numberOfProcesses;


}




int main(){

  int NProcess;
    cout << "\t\t==============> FIFO <==============" << endl;
    cout << "Number of Process : ";
    cin >> NProcess;
    Process *ProcessArray = new Process[NProcess];

    for (int i = 0; i < NProcess; i++) {
        ProcessArray[i].name = i;
        cout << "Entrance Time : ";
        cin >> ProcessArray[i].entrance_time;
        cout << "Process Time : ";
        cin >> ProcessArray[i].burst_time;
    }

fifo(ProcessArray,NProcess);

return 0 ;

}