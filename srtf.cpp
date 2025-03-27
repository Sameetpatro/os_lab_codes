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
    int id, arrival, burst, remaining, completion, tat, waiting, response;
};

bool compareArrival(Process a, Process b) {
    return a.arrival < b.arrival; 
}

void srtf(vector<Process> &processes, int n) {
    int time = 0, completed = 0, shortest = -1, min_burst = 1e9;
    vector<int> completion(n), tat(n), waiting(n), response(n, -1);
    
    while (completed < n) {
        shortest = -1;
        min_burst = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0 && processes[i].remaining < min_burst) {
                min_burst = processes[i].remaining;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            time++;
            continue;
        }
        
        if (response[shortest] == -1) response[shortest] = time - processes[shortest].arrival;
        processes[shortest].remaining--;
        time++;
        
        if (processes[shortest].remaining == 0) {
            processes[shortest].completion = time;
            completed++;
        }
    }
    
    int avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = processes[i].completion - processes[i].arrival;
        waiting[i] = tat[i] - processes[i].burst;
        response[i] = response[i];
        completion[i] = processes[i].completion;
        
        avgTAT += tat[i];
        avgWT += waiting[i];
    }
    
    cout << "\nSRTF Scheduling:";
    cout << "\nAverage Turnaround Time: " << (avgTAT / n) << endl;
    cout << "Average Waiting Time: " << (avgWT / n) << endl;
    cout << "Completion time: "; show(completion);
    cout << "TAT time: "; show(tat);
    cout << "Waiting time: "; show(waiting);
    cout << "Response time: "; show(response);
}



int main() {
    int n;
    cout << "Enter number of processes: " << endl;
    cin >> n;
    
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time of P" << (i + 1) << ": " << endl;
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
    }
    
    sort(processes.begin(), processes.end(), compareArrival);
    
    srtf(processes, n);
    return 0;
}
