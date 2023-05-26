#include <iostream>
#include <queue>

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

bool searchInQueue(int searchValue, queue<int> q) {
    bool found = false;
    int queueSize = q.size();
    for (int i = 0; i < queueSize; i++) {
        if (q.front() == searchValue) {
            found = true;
            break;
        }
        q.push(q.front());
        q.pop();
    }
    return found;
}

void printQueue(queue<int> q) {
    queue<int> tmp = q;
    cout << "Queue: ";
    while (!tmp.empty()) {
        cout << tmp.front() << "\t";
        tmp.pop();
    }
    cout << endl;
}

int UpdateReadyQueue(Process ProcessArray[], int numberOfProcesses, float Now, queue<int> &Ready_Queue, int lastIndex) {

    int EnteredProcesses = 0;
    int i;


    for (i = 0; i < numberOfProcesses; i++) {
        if (ProcessArray[i].entrance_Time <= Now) {
            if (ProcessArray[i].Burst_Time != 0) {

                if (!searchInQueue(i, Ready_Queue) && (lastIndex != i)) {


                    Ready_Queue.push(i);

                }
            }
            EnteredProcesses++;
        }
    }


    return EnteredProcesses;


}

int main() {
    float Quantum;
    int numberOfProcesses;
    cout << "\t\t==============> Round Robin <==============" << endl;
    cout << "Enter a number as RR Quantum : ";
    cin >> Quantum;
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
    queue<int> Ready_Queue;
    int indexOfProcess = -1;
    float TimeCounter = 0;
    int entredProcesses = UpdateReadyQueue(ProcessArray, numberOfProcesses, TimeCounter, Ready_Queue, indexOfProcess);
    while (true) {


        if (Ready_Queue.size() != 0) {
            indexOfProcess = Ready_Queue.front();
            Ready_Queue.pop();
        } else if (entredProcesses < numberOfProcesses) {
            TimeCounter++;
            continue;
        } else {
            break;
        }

        cout << "P[" << indexOfProcess + 1 << "] : " << TimeCounter << "\t";

        Process *SelectedProcess = &ProcessArray[indexOfProcess];
        for (int i = 0; i < Quantum; i++) {
            TimeCounter++;
            SelectedProcess->Burst_Time--;

            if (SelectedProcess->Burst_Time == 0) {
                indexOfProcess = -1;
                SelectedProcess->Exit_Time = TimeCounter;
                break;
            }

            if (i + 1 != Quantum)
                entredProcesses = UpdateReadyQueue(ProcessArray, numberOfProcesses, TimeCounter, Ready_Queue,
                                                   indexOfProcess);
        }

        if (indexOfProcess != -1)
            Ready_Queue.push(indexOfProcess);

        entredProcesses = UpdateReadyQueue(ProcessArray, numberOfProcesses, TimeCounter, Ready_Queue, indexOfProcess);
        cout << TimeCounter << "\n";


    }


    cout << "\t\t==============> Round Robin Output <==============" << endl;
    float SumOFWaitingTime = 0;
    float SumOFResponseTime = 0;
    float tempWaitingTime, tempResponseTime;

    for (int i = 0; i < numberOfProcesses; i++) {
        tempResponseTime = ProcessArray[i].Exit_Time - ProcessArray[i].entrance_Time;
        tempWaitingTime = tempResponseTime - ProcessArray[i].IntialBurst_Time;

        cout << "P[" << i << "] : " << "Response Time : " << tempResponseTime << "   Waiting Time : " << tempWaitingTime
             << endl;
        SumOFResponseTime += tempResponseTime;
        SumOFWaitingTime += tempWaitingTime;
    }
    cout << "Ave. Of Response Time : " << SumOFResponseTime / numberOfProcesses << " \nAve. Of Waiting Time : "
         << SumOFWaitingTime / numberOfProcesses;

    return 0;

}