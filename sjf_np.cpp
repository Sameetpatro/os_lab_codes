#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main(){
    int n;
    cout<<"Enter no of process: "<<endl;
    cin>>n;
    vector<int> process(n);
    for(int i  = 0; i < n; i++){
        process[i] = i+1;
    } 

    vector<int> arrival(n);
    for(int i = 0; i < n; i++){
        cout<<"enter arrival time of p"<<(i+1)<<endl;
        cin>>arrival[i];
    }

    vector<int> burst(n);
    for(int i = 0; i < n; i++){
        cout<<"enter burst time of p"<<(i+1)<<endl;
        cin>>burst[i];
    }
    vector<bool> completed(n, false);
    vector<int> completion(n);
    int co = 0, time = 0;
    while(co < n){
        int j = -1;
        int minBT = INT_MAX;

        for(int i = 0; i < n; i++){
            if(!completed[i] && arrival[i] <= time && burst[i] < minBT){
                minBT = burst[i];
                j = i;
            }
        }
        if(j == -1){
            time++;
            continue;
        }
        completed[j] = true;
        completion[j] = time + burst[j];
        time = completion[j];
        co++;
        
    }
    vector<int> tat(n);
    for(int i = 0; i < n; i++){
        tat[i] = completion[i] - arrival[i];
    }
    vector<int> waiting(n),response(n);
    for(int i = 0; i < n; i++){
        response[i] = tat[i] - burst[i];
        waiting[i] = response[i];
    }
    cout<<"PID  AT  BT  CT  TAT  WT  RT\n";
    for(int i = 0; i < n; i++){
        cout<<"P"<<process[i]<<" : "<<arrival[i]<<"   "<<burst[i]<<"   "<<completion[i]<<"   "<<tat[i]<<"   "<<waiting[i]<<"   "<<response[i]<<endl;
    }
     
     
    return 0;
}