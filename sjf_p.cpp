#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int id, arrival_time, burst_time, remaining_time, completion_time, waiting_time, turnaround_time;
};

void sjfPreemptive(vector<Process> &processes) {
    int n = processes.size();
    int completed = 0, current_time = 0, min_index;
    int min_remaining_time;
    
    while (completed != n) {
        min_index = -1;
        min_remaining_time = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                min_index = i;
            }
        }
        
        if (min_index == -1) {
            current_time++;
            continue;
        }
        
        processes[min_index].remaining_time--;
        current_time++;
        
        if (processes[min_index].remaining_time == 0) {
            completed++;
            processes[min_index].completion_time = current_time;
            processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
            processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
        }
    }
    
    cout << "Process\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" << processes[i].arrival_time << "\t" << processes[i].burst_time << "\t"
             << processes[i].completion_time << "\t" << processes[i].turnaround_time << "\t" << processes[i].waiting_time << endl;
    }
}

int main() {
    vector<Process> processes = {{1, 0, 7, 7, 0, 0, 0}, {2, 2, 4, 4, 0, 0, 0}, {3, 4, 1, 1, 0, 0, 0}, {4, 5, 4, 4, 0, 0, 0}};
    sjfPreemptive(processes);
    return 0;
}
