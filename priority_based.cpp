#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void show(vector<int> vect){
    for(int i = 0; i < vect.size(); i++){
        cout << vect[i] << " ";
    }
    cout << "\n";
}

struct Process {
    int id, arrival, burst, priority, completion, tat, waiting, response;
};

bool compare(Process a, Process b) {
    if (a.priority == b.priority) {
        return a.arrival < b.arrival;
    }
    return a.priority > b.priority;
}

int main() {
    int n;
    cout << "Enter number of processes: " << endl;
    cin >> n;
    
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority of P" << (i + 1) << ": " << endl;
        cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
    }
    
    sort(processes.begin(), processes.end(), compare);
    
    processes[0].completion = processes[0].arrival + processes[0].burst;
    for (int i = 1; i < n; i++) {
        processes[i].completion = max(processes[i].arrival, processes[i - 1].completion) + processes[i].burst;
    }
    
    vector<int> tat(n), waiting(n), response(n), completion(n);
    int avgTAT = 0, avgWT = 0;
    
    for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].tat - processes[i].burst;
        processes[i].response = processes[i].waiting;
        
        completion[i] = processes[i].completion;
        tat[i] = processes[i].tat;
        waiting[i] = processes[i].waiting;
        response[i] = processes[i].response;
        
        avgTAT += tat[i];
        avgWT += waiting[i];
    }
    
    cout << "\nAverage Turnaround Time: " << (avgTAT / n) << endl;
    cout << "Average Waiting Time: " << (avgWT / n) << endl;
    
    cout << "Completion time: ";
    show(completion);
    cout << "TAT time: ";
    show(tat);
    cout << "Waiting time: ";
    show(waiting);
    cout << "Response time: ";
    show(response);
    
    return 0;
}