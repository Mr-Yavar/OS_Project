#include <iostream>

using namespace std;

class Process {
public:
    int name;
    int entranceTime, ProcessTime, exit, IntialProcessTime;

    Process(int name, int entranceTime, int ProcessTime) {
        this->name = name;
        this->ProcessTime = ProcessTime;
        this->IntialProcessTime = ProcessTime;
        this->entranceTime = entranceTime;
    }

    Process() {

    }
};

int findMinProcess(Process ProcessArray[], int NumberOfProcess, int Now) {
    int ShortestProcessTime = INT32_MAX;
    int indexOfProcess = -1; // Flag
    int EnteredProcesses =0;
    int i;
    for (i = 0; i < NumberOfProcess; i++) {
        if (ProcessArray[i].entranceTime <= Now) {
            if (ShortestProcessTime > ProcessArray[i].ProcessTime &&
                ProcessArray[i].ProcessTime != 0) {
                indexOfProcess = i;
                ShortestProcessTime = ProcessArray[i].ProcessTime;
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
    cout << "\t\t=========> SJF|SPN <=========" << endl;
    cout << "Number of Process : ";
    cin >> NumberOfProcess;
    Process *ProcessArray = new Process[NumberOfProcess];

    for (int i = 0; i < NumberOfProcess; i++) {
        ProcessArray[i].name = i;
        cout << "Entrance Time : ";
        cin >> ProcessArray[i].entranceTime;
        cout << "Process Time : ";
        cin >> ProcessArray[i].ProcessTime;
    }

    int indexOfProcess;
    int TimeCounter = 0;
    while (true) {
        indexOfProcess = findMinProcess(ProcessArray, NumberOfProcess, TimeCounter);
        if (indexOfProcess == -1)
            break;
        else if (indexOfProcess == -2) {
            TimeCounter++;
            continue;
        }

        Process *SelectedProcess = &ProcessArray[indexOfProcess];

        TimeCounter += SelectedProcess->ProcessTime;
        SelectedProcess->ProcessTime = 0;
        SelectedProcess->exit = TimeCounter;


    }
    cout << TimeCounter;

    for (int i = 0; i < NumberOfProcess; i++) {
        ProcessArray[i].name = i;
        cout << "Entrance Time : ";
        cin >> ProcessArray[i].entranceTime;
        cout << "Process Time : ";
        cin >> ProcessArray[i].ProcessTime;
    }


    return 0;
}

