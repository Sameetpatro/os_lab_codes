#include <iostream>
#include <vector>
using namespace std;

void show(vector<int> vect){
    for(int i = 0; i < vect.size(); i++){
        cout<<vect[i]<<" ";
    }
    cout<<"\n";
}

int main(){
    int n;
    cout<<"enter no of process"<<endl;
    cin>>n;
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
    int avgB = 0;
    for(int i = 0; i < n; i++){
        avgB += burst[i];
    }    
    cout<<"average burst time: "<<(avgB / n)<<endl;
    vector<int> process(n);
    for(int i = 0; i < n; i++){
        process[i] = i + 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(arrival[i] > arrival[j]) {
                swap(arrival[i], arrival[j]);
                swap(burst[i], burst[j]);
                swap(process[i], process[j]);
            }
        }
    }
    vector<int> completion(n);
    completion[0] = arrival[0] + burst[0];
    for(int i = 1; i < n; i++){ 
        completion[i] = burst[i] + max(arrival[i], completion[i-1]);
    }
    vector<int> tat(n);
    for(int i = 0; i < n; i++){
        tat[i] = completion[i] - arrival[i];
    }
    int avgT = 0;
    for(int i = 0; i < n; i++){
        avgT += tat[i];
    }
    cout<<"average Turn around time is: "<<(avgT/ n)<<endl;
    vector<int> waiting(n);
    vector<int> response(n);
    for(int i = 0; i < n; i++){
        waiting[i] = tat[i] - burst[i];
        response[i] = waiting[i];
    }
    cout<<"Completion time: ";
    show(completion);
    cout<<"Tat time: ";
    show(tat);
    cout<<"Waiting time: ";
    show(waiting);
    cout<<"Response time: ";
    show(response);
    return 0;
}