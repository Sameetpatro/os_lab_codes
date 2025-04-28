#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, bt, prio, wt = 0, tat = 0, remaining_bt;
};

bool cmp(const Process &a, const Process &b) { return a.prio < b.prio; }

void nonPreemptive(vector<Process>& p) {
    sort(p.begin(), p.end(), cmp);
    for (int i = 1; i < p.size(); ++i)
        p[i].wt = p[i-1].wt + p[i-1].bt;
    for (auto &i : p) i.tat = i.wt + i.bt;
}

void preemptive(vector<Process>& p) {
    int complete = 0, time = 0, n = p.size();
    while (complete < n) {
        int idx = -1, minPrio = 1e9;
        for (int i = 0; i < n; ++i)
            if (p[i].remaining_bt > 0 && p[i].prio < minPrio) minPrio = p[i].prio, idx = i;
        if (idx == -1) { time++; continue; }
        p[idx].remaining_bt--;
        if (p[idx].remaining_bt == 0) {
            complete++;
            p[idx].tat = time + 1;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
        time++;
    }
}

void print(vector<Process>& p) {
    double total_wt = 0, total_tat = 0;
    cout << "\nPID | BT | PRIO | WT | TAT\n";
    for (auto &i : p) {
        cout << i.pid << "   | " << i.bt << "  | " << i.prio << "    | " << i.wt << "  | " << i.tat << endl;
        total_wt += i.wt; total_tat += i.tat;
    }
    cout << "\nAvg WT: " << total_wt / p.size() << "\nAvg TAT: " << total_tat / p.size() << endl;
}

int main() {
    int n, mode;
    cout << "Enter number of processes: "; cin >> n;
    cout << "0 = Non-Preemptive, 1 = Preemptive Priority Scheduling: "; cin >> mode;
    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter Burst Time and Priority for Process " << i+1 << ": ";
        cin >> p[i].bt >> p[i].prio;
        p[i].pid = i+1; p[i].remaining_bt = p[i].bt;
    }
    (mode == 0) ? nonPreemptive(p) : preemptive(p);
    print(p);
}
