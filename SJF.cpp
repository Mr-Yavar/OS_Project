#include <iostream>

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

int findMinProcess(Process ProcessArray[], int NumberOfProcess, float Now) {
    int ShortestBurstTime = INT32_MAX;
    int indexOfProcess = -1; // Flag
    int EnteredProcesses =0;
    int i;
    for (i = 0; i < NumberOfProcess; i++) {
        if (ProcessArray[i].entrance_Time <= Now) {
            if (ShortestBurstTime > ProcessArray[i].Burst_Time &&
                ProcessArray[i].Burst_Time != 0) {
                indexOfProcess = i;
                ShortestBurstTime = ProcessArray[i].Burst_Time;
            }
            EnteredProcesses++;
        }
    }
    if (EnteredProcesses < NumberOfProcess )
        return -2;

    return indexOfProcess;


}

int main() {
    int NumberOfProcess;
    cout << "\t\t==============> SJF|SPN <==============" << endl;
    cout << "Number of Process : ";
    cin >> NumberOfProcess;
    Process *ProcessArray = new Process[NumberOfProcess];

    for (int i = 0; i < NumberOfProcess; i++) {
        ProcessArray[i].name = i;
        cout << "Entrance Time : ";
        cin >> ProcessArray[i].entrance_Time;
        cout << "Burst Time : ";
        cin >> ProcessArray[i].Burst_Time;
        ProcessArray[i].IntialBurst_Time = ProcessArray[i].Burst_Time;
    }

    int indexOfProcess;
    float TimeCounter = 0;
    while (true) {
        indexOfProcess = findMinProcess(ProcessArray, NumberOfProcess, TimeCounter);
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



    cout << "\t\t==============> SJF/SPN Output <=============="<<endl;
    float SumOFWaitingTime=0;
    float SumOFResponseTime=0;
    float tempWaitingTime,tempResponseTime;

    for (int i = 0; i < NumberOfProcess; i++) {
       tempResponseTime=ProcessArray[i].Exit_Time-ProcessArray[i].entrance_Time;
       tempWaitingTime=tempResponseTime-ProcessArray[i].IntialBurst_Time;

       cout << "P[" << i << "] : "<< "Response Time : " << tempResponseTime << "   Waiting Time : "<<tempWaitingTime << endl;
       SumOFResponseTime+=tempResponseTime;
       SumOFWaitingTime+=tempWaitingTime;
    }
    cout << "Ave. Of Response Time : "<<SumOFResponseTime/NumberOfProcess << " \nAve. Of Waiting Time : "<<SumOFWaitingTime/NumberOfProcess;


    return 0;
}

