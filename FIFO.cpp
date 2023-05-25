#include <iostream>
#include <algorithm>

using namespace std;


class Process {
public:
    int name;
    float entrance_Time, Burst_Time, Exit_Time, IntialBurst_Time;

    Process(int name, float entrance_Time, float Burst_Time) {
        this->name = name;
        this->Burst_Time = Burst_Time;
        this->IntialBurst_Time = Burst_Time;
        this->entrance_Time = entrance_Time;
    }

    Process() {

    }
};

int findOldestProcess(Process ProcessArray[], int numberOfProcesses, float Now) {
    int indexOfProcess = -1; // Flag
    int EnteredProcesses = 0;
    int i;
    int EntranceTimeOfProcesses = Now;
    for (i = 0; i < numberOfProcesses; i++) {
        if (ProcessArray[i].entrance_Time <= Now) {
            if(ProcessArray[i].Burst_Time != 0) {
                if (EntranceTimeOfProcesses > ProcessArray[i].entrance_Time) {
                    indexOfProcess = i;
                    EntranceTimeOfProcesses = ProcessArray[i].entrance_Time;
                } else if (EntranceTimeOfProcesses == ProcessArray[i].entrance_Time) {
                    if(indexOfProcess > i || indexOfProcess == -1){
                        indexOfProcess = i;
                    }
                }
            }
            EnteredProcesses++;
        }
    }
    if (EnteredProcesses < numberOfProcesses && indexOfProcess == -1)
        return -2;

    return indexOfProcess;


}


int main() {

    int numberOfProcesses;
    cout << "\t\t==============> FIFO <==============" << endl;
    cout << "Number of Process : ";
    cin >> numberOfProcesses;
    Process *ProcessArray = new Process[numberOfProcesses];

    for (int i = 0; i < numberOfProcesses; i++) {
        ProcessArray[i].name = i;
        cout << "Entrance Time : ";
        cin >> ProcessArray[i].entrance_Time;
        cout << "Process Time : ";
        cin >> ProcessArray[i].Burst_Time;
        ProcessArray[i].IntialBurst_Time = ProcessArray[i].Burst_Time;
    }

    int indexOfProcess;
    float TimeCounter = 0;
    while (true) {
        indexOfProcess = findOldestProcess(ProcessArray, numberOfProcesses, TimeCounter);
        if (indexOfProcess == -1)
            break;
        else if (indexOfProcess == -2) {
            TimeCounter++;
            continue;
        }


        Process *SelectedProcess = &ProcessArray[indexOfProcess];
        TimeCounter += SelectedProcess->Burst_Time;
        SelectedProcess->Burst_Time = 0;
        SelectedProcess->Exit_Time = TimeCounter;


    }



    cout << "\t\t==============> FIFO Output <=============="<<endl;
    float SumOFWaitingTime=0;
    float SumOFResponseTime=0;
    float tempWaitingTime,tempResponseTime;

    for (int i = 0; i < numberOfProcesses; i++) {
        tempResponseTime=ProcessArray[i].Exit_Time-ProcessArray[i].entrance_Time;
        tempWaitingTime=tempResponseTime-ProcessArray[i].IntialBurst_Time;

        cout << "P[" << i << "] : "<< "Response Time : " << tempResponseTime << "   Waiting Time : "<<tempWaitingTime << endl;
        SumOFResponseTime+=tempResponseTime;
        SumOFWaitingTime+=tempWaitingTime;
    }
    cout << "Ave. Of Response Time : "<<SumOFResponseTime/numberOfProcesses << " \nAve. Of Waiting Time : "<<SumOFWaitingTime/numberOfProcesses;

    return 0;

}