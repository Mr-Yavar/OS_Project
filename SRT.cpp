#include <iostream>

using namespace std;

class Process {
public:
    int name;
    float entrance_Time, Burst_Time,Exit_Time, IntialBurst_Time;

    Process(int name, float entrance_Time, float Burst_Time) {
        this->name = name;
        this->Burst_Time = Burst_Time;
        this->IntialBurst_Time = Burst_Time;
        this->entrance_Time = entrance_Time;
    }

    Process() {

    }
};

int findMinProcess(Process ProcessArray[], int numberOfProcesses, float Now) {
    int ShortestProcessTime = INT32_MAX;
    int indexOfProcess = -1; // Flag
    int EnteredProcesses =0;
    int i;
    for (i = 0; i < numberOfProcesses; i++) {
        if (ProcessArray[i].entrance_Time <= Now) {
            if (ShortestProcessTime > ProcessArray[i].Burst_Time && ProcessArray[i].Burst_Time != 0) {
                indexOfProcess = i;
                ShortestProcessTime = ProcessArray[i].Burst_Time;
            }
            EnteredProcesses++;
        }
    }
    if (EnteredProcesses < numberOfProcesses && indexOfProcess==-1)
        return -2;

    return indexOfProcess;


}

int main() {
    int numberOfProcesses;
    cout << "\t\t==============> SRT <==============" << endl;
    cout << "Number of Process : ";
    cin >> numberOfProcesses;
    Process *ProcessArray = new Process[numberOfProcesses];

    for (int i = 0; i < numberOfProcesses; i++) {
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
        indexOfProcess = findMinProcess(ProcessArray, numberOfProcesses, TimeCounter);
        if (indexOfProcess == -1)
            break;
        else if (indexOfProcess == -2) {
            TimeCounter++;
            continue;
        }


        Process *SelectedProcess = &ProcessArray[indexOfProcess];
        bool NewSelection=false;
        for(int i=0;i<SelectedProcess->Burst_Time;i++) {
            TimeCounter += 1;
            SelectedProcess->Burst_Time--;
            if(SelectedProcess->Burst_Time==0){
                NewSelection=true;
                SelectedProcess->Exit_Time=TimeCounter;
                break;
            }

            if (findMinProcess(ProcessArray, numberOfProcesses, TimeCounter) != indexOfProcess) {
                NewSelection = true;
                break;
            }
        }

        if(NewSelection) {
            continue;
        }





    }



    cout << "\t\t==============> SRT Output <=============="<<endl;
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

