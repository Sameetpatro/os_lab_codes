#include <bits/stdc++.h>
using namespace std;

void show(vector<int> vect) {
    for (int i : vect) {
        cout << i << " ";
    }
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> process(n), arrival(n), burst(n);
    for (int i = 0; i < n; i++) {
        process[i] = i + 1;
        cout << "Enter arrival time of P" << i + 1 << ": ";
        cin >> arrival[i];
        cout << "Enter burst time of P" << i + 1 << ": ";
        cin >> burst[i];
    }
    
    int tq;
    cout << "Enter time quantum: ";
    cin >> tq;
    
    queue<int> q;
    vector<int> completion(n, 0), tat(n, 0), waiting(n, 0), response(n, -1);
    vector<int> remaining_bt = burst;
    int time = 0;
    vector<bool> inQueue(n, false);
    
    int completed = 0;
    
    while (completed < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining_bt[i] > 0 && !inQueue[i]) {
                q.push(i);
                inQueue[i] = true;
                found = true;
            }
        }
        
        if (!q.empty()) {
            int i = q.front();
            q.pop();
            inQueue[i] = false;
            
            if (response[i] == -1) {
                response[i] = time - arrival[i];
            }
            
            int exec_time = min(tq, remaining_bt[i]);
            time += exec_time;
            remaining_bt[i] -= exec_time;
            
            if (remaining_bt[i] > 0) {
                q.push(i);
                inQueue[i] = true;
            } else {
                completion[i] = time;
                tat[i] = completion[i] - arrival[i];
                waiting[i] = tat[i] - burst[i];
                completed++;
            }
        } else {
            time++;
        }
    }
    
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << process[i] << "\t" << arrival[i] << "\t" << burst[i] << "\t"
             << completion[i] << "\t" << tat[i] << "\t" << waiting[i] << "\t" << response[i] << "\n";
    }
    
    return 0;
}
