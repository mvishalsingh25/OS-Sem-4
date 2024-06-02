#include<iostream>
#include<climits>
#include<queue>
using namespace std;

struct process{
  int processId;
  int arrivalTime;
  int burstTime;
  int completionTime;
  int TurnAroundTime;
  int WaitingTime;
  int ResponseTime=INT_MAX;
  int remainingArrivalTime;
  int remainingBurstTime;
  int priority;
  int remainingpriority;
};

void print(process proc[],int n);
int checkFCFS(process proc [], int n);
bool checkSJF(process proc [], int n);
bool checkPriority(process proc[],int n);

void FCFS(process proc[],int n){
    cout<<"**********************************************************************************"<<endl;
    cout<<endl;
    cout<<"FCFS Scheduling Algorithmn: "<<endl<<endl;
    cout<<"GANT CHART (order showing which process completed first): "<<endl;
   int currentTime=0;
   while(1){
    int minIndex=-1,minValue=INT_MAX;
    for(int i=0;i<n;i++){
        if(proc[i].arrivalTime<=currentTime){
            if(proc[i].remainingArrivalTime<minValue){
                   minValue=proc[i].remainingArrivalTime;
                   minIndex=i;
            }
        }
    }
    if(minIndex!=-1){
        proc[minIndex].ResponseTime=currentTime-proc[minIndex].arrivalTime;
        proc[minIndex].completionTime=proc[minIndex].burstTime+currentTime;
        currentTime+=proc[minIndex].burstTime;
        proc[minIndex].remainingArrivalTime=INT_MAX;
        cout<<"P"<<proc[minIndex].processId<<"--->";
    }
    else{
        currentTime++;
        if(checkFCFS(proc,n)) {
            cout<<endl;
        for(int i=0;i<n;i++){
                proc[i].TurnAroundTime=proc[i].completionTime-proc[i].arrivalTime;
                proc[i].WaitingTime=proc[i].TurnAroundTime-proc[i].burstTime;
            }
            break;
        }
    }

   }
    print(proc,n);
    cout<<"**********************************************************************************"<<endl;
}

void SJF(process proc[],int n){
    cout<<endl;
    cout<<"**********************************************************************************"<<endl;
    cout<<"SJF Scheduling Algorithmn: "<<endl<<endl;
   int currentTime=0;
   cout<<"GANT CHART (order showing which process completed first): "<<endl;
   while(1){
    int minIndex=-1,minValue=INT_MAX;
    for(int i=0;i<n;i++){
        if(proc[i].arrivalTime <= currentTime){
            if(proc[i].remainingBurstTime<minValue){
                   minValue=proc[i].remainingBurstTime;
                   minIndex=i;
            }
        }
    }
    if(minIndex!=-1){
        proc[minIndex].completionTime=currentTime+proc[minIndex].burstTime;
        proc[minIndex].ResponseTime=currentTime-proc[minIndex].arrivalTime;
        currentTime+=proc[minIndex].burstTime;
        proc[minIndex].remainingBurstTime=INT_MAX;
        cout<<"P"<<proc[minIndex].processId<<"--->";
    }
    else{
        currentTime++;
        if(checkSJF(proc,n)) {
        for(int i=0;i<n;i++){
                proc[i].TurnAroundTime=proc[i].completionTime-proc[i].arrivalTime;
                proc[i].WaitingTime=proc[i].TurnAroundTime-proc[i].burstTime;
            }
            break;
        }
    }
   }
    print(proc,n);
    cout<<"**********************************************************************************"<<endl;
}

void SRTF(process proc[],int n){
cout<<endl;
    cout<<"**********************************************************************************"<<endl;
    cout<<"SRTF Scheduling Algorithmn: "<<endl<<endl;
    int currentTime=0;
    cout<<"GANT CHART (order showing which process completed first): "<<endl;
    while(1){
        int minIndex=-1,minValue=INT_MAX;
        for(int i=0;i<n;i++){
            if(proc[i].arrivalTime<=currentTime){
                if(proc[i].remainingBurstTime<minValue){
                    minValue=proc[i].remainingBurstTime;
                    minIndex=i;
                }
            }
        }
        if(minIndex!=-1){
            currentTime++;
            proc[minIndex].remainingBurstTime--;
            if(proc[minIndex].ResponseTime==INT_MAX){
                proc[minIndex].ResponseTime=currentTime-proc[minIndex].arrivalTime-1;
            }
            if(proc[minIndex].remainingBurstTime==0){
                proc[minIndex].completionTime=currentTime;
                proc[minIndex].remainingBurstTime=INT_MAX;
                cout<<"P"<<proc[minIndex].processId<<"--->";
            }
        }
        else{
            currentTime++;
            if(checkSJF(proc,n)){
                cout<<endl;
                for(int i=0;i<n;i++){
                    proc[i].TurnAroundTime=proc[i].completionTime-proc[i].arrivalTime;
                    proc[i].WaitingTime=proc[i].TurnAroundTime-proc[i].burstTime;
                }
                break;
            }
        }
    }
   print(proc,n);
   cout<<"*********************************************************************"<<endl;
}

void RoundRobin(process proc[],int n,int time_quantum){
    cout<<endl;
    cout<<"GANT CHART (order showing which process completed first): "<<endl;
    int current_time=0;
    queue<process *>q1;  //  struct  pointer concept
    while(1){
    if(!q1.empty()){
     process *temp=q1.front();
     q1.pop();
    
    //find response time
     if(temp->ResponseTime==INT_MAX){
        temp->ResponseTime=current_time-temp->arrivalTime;
     }
 ///3 cases
     if(temp->remainingBurstTime > time_quantum){
     temp->remainingBurstTime-=time_quantum;
     for(int i=current_time+1;i<=current_time+time_quantum;i++){
        for(int j=0;j<n;j++){
            if(proc[j].arrivalTime==i){
                q1.push(&proc[j]);
            }
        }

     }
     current_time+=time_quantum;
        q1.push(temp);
     }
     else if(temp->remainingBurstTime == time_quantum){
      temp->completionTime=current_time+time_quantum;
      for(int i=current_time+1;i<=current_time+time_quantum;i++){
        for(int j=0;j<n;j++){
            if(proc[j].arrivalTime==i){
                q1.push(&proc[j]);
            }
        }
      }
       current_time+=time_quantum;
        temp->remainingBurstTime=INT_MAX;
        cout<<"P"<<temp->processId<<"--->";
     }
     else{
      temp->completionTime=current_time+temp->remainingBurstTime;
      for(int i=current_time+1;i<=current_time+temp->remainingBurstTime;i++){
        for(int j=0;j<n;j++){
            if(proc[j].arrivalTime==i){
                q1.push(&proc[j]);
            }
        }
        
      }
      current_time+=temp->remainingBurstTime;
        temp->remainingBurstTime=INT_MAX;
        cout<<"P"<<temp->processId<<"--->";
     }
    }
    else 
    { if(checkSJF(proc,n)){
        cout<<endl;
      for(int i=0;i<n;i++){
        proc[i].TurnAroundTime=proc[i].completionTime-proc[i].arrivalTime;
        proc[i].WaitingTime=proc[i].TurnAroundTime-proc[i].burstTime;
      }
        
       break;
    }
  //////////////////
    for(int i=0;i<n;i++){
        if(proc[i].arrivalTime==current_time){
            q1.push(&proc[i]);
        }
    }
      if (q1.empty()){
        current_time++;
    }
    }
    }
    print(proc,n);
}

void priority(process proc[],int n){
int currenttime=0;
    cout<<"GANT CHART (order showing which process completed first): "<<endl;

while(1){
    int minindex=-1,minvalue=INT_MAX;
    for(int i=0;i<n;i++){
        if(proc[i].arrivalTime<=currenttime){
            if(proc[i].remainingpriority<minvalue){
                minvalue=proc[i].remainingpriority;
                minindex=i;
            }
        }
    }

    if(minindex!=-1){
        proc[minindex].ResponseTime=currenttime-proc[minindex].arrivalTime;
        proc[minindex].completionTime=currenttime+proc[minindex].burstTime;
        currenttime+=proc[minindex].remainingBurstTime;
        proc[minindex].remainingpriority=INT_MAX;
        cout<<"P"<<proc[minindex].processId<<"--->";

    }
    else{
        currenttime++;
        if(checkPriority(proc,n)){
            cout<<endl;
            for(int i=0;i<n;i++){
        proc[i].TurnAroundTime=proc[i].completionTime-proc[i].arrivalTime;
        proc[i].WaitingTime=proc[i].TurnAroundTime-proc[i].burstTime;
      }
      break;
        }
    }
}
print(proc,n);
}

void priority2(process proc[],int n){
int currenttime=0;
    cout<<"GANT CHART (order showing which process completed first): "<<endl;

while(1){
    int minindex=-1,minvalue=INT_MAX;
    for(int i=0;i<n;i++){
        if(proc[i].arrivalTime<=currenttime){
            if(proc[i].remainingpriority<minvalue){
                minvalue=proc[i].remainingpriority;
                minindex=i;
            }
        }
    }

    if(minindex!=-1){
       currenttime++;
            proc[minindex].remainingBurstTime--;
            if(proc[minindex].ResponseTime==INT_MAX){
                proc[minindex].ResponseTime=currenttime-proc[minindex].arrivalTime-1;
            }
            if(proc[minindex].remainingBurstTime==0){
                proc[minindex].completionTime=currenttime;
                proc[minindex].remainingpriority=INT_MAX;
                cout<<"P"<<proc[minindex].processId<<"--->";
            }
    }
    else{
        currenttime++;
        if(checkPriority(proc,n)){
            cout<<endl;
            for(int i=0;i<n;i++){
        proc[i].TurnAroundTime=proc[i].completionTime-proc[i].arrivalTime;
        proc[i].WaitingTime=proc[i].TurnAroundTime-proc[i].burstTime;
      }
      break;
        }
    }
}
print(proc,n);
}

int checkFCFS(process proc [], int n){
 bool flag=true;
 for(int i=0;i<n;i++){
    if(proc[i].remainingArrivalTime!=INT_MAX){
        flag=false;
    }
 }
 return flag;
}

bool checkSJF(process proc[],int n){
    for(int i=0;i<n;i++){
       if(proc[i].remainingBurstTime==INT_MAX){
        return true;
       }
    }
    return false;
}

bool checkPriority(process proc[],int n){
    for(int i=0;i<n;i++){
       if(proc[i].remainingpriority==INT_MAX){
        return true;
       }
    }
    return false;
}

void print(process proc[],int n){
    cout<<endl;
    cout<<"PID\tArrivalTime\tBurstTime\tCompletionTime\tTurnAroundTime\tWaitingTime\tResponseTime"<<endl;
    for(int i=0;i<n;i++){
        cout<<proc[i].processId<<"\t\t"<<proc[i].arrivalTime<<"\t\t"<<proc[i].burstTime<<"\t\t"<<proc[i].completionTime<<"\t\t"<<proc[i].TurnAroundTime<<"\t\t"<<proc[i].WaitingTime<<"\t\t"<<proc[i].ResponseTime<<endl;;
    }
    cout<<endl;
    float sum=0,average=0;
    for(int i=0;i<n;i++){
     sum+=proc[i].TurnAroundTime;
    }
    average=sum/n;
    cout<<"Average TurnAroundTime: "<<sum<<"/"<<n<<" = "<<average<<endl;

    sum=0,average=0;
     for(int i=0;i<n;i++){
     sum+=proc[i].WaitingTime;
    }
    average=sum/n;
    cout<<"Average TurnAroundTime: "<<sum<<"/"<<n<<" = "<<average<<endl;

    sum=0,average=0;
     for(int i=0;i<n;i++){
     sum+=proc[i].ResponseTime;
    }
    average=sum/n;
    cout<<"Average TurnAroundTime: "<<sum<<"/"<<n<<" = "<<average<<endl;
}
int main(){
    int n;
    cout<<"enter number of processes: ";
    cin>>n;
    process proc[n];
    for(int i=0;i<n;i++){
    cout<<"enter process "<<i+1<<" arrival time and burst time : ";
    cin>>proc[i].arrivalTime>>proc[i].burstTime;;
    proc[i].remainingArrivalTime=proc[i].arrivalTime;
    
    proc[i].remainingBurstTime=proc[i].burstTime;

    proc[i].processId=i+1;
}

cout<<endl;
int option=1;
cout<<"1. FCFS Scheduling Algorithm "<<endl;
cout<<"2. SJF Scheduling Algorithmn "<<endl;
cout<<"3. SRTF Scheduling Algorithmn "<<endl;
cout<<"4. Round Robin Scheduling Algorithmn"<<endl;
cout<<"5. Priority Scheduling (Non Preemptive) Algorithmn"<<endl;
cout<<"6. Priority Scheduling (Preemptive) Algorithmn"<<endl;
cout<<endl;
cout<<"enter your option: ";
cin>>option;
switch (option)
{
case 1:
    FCFS(proc,n);
    break;
case 2:
    SJF(proc,n);
    break;
case 3:
    SRTF(proc,n);
    break;
case 4:
int timeQuantum;
cout<<"enter time quantum: ";
cin>>timeQuantum;
    RoundRobin(proc,n,timeQuantum);
    break;
case 5:
for(int i=0;i<n;i++){
    cout<<"enter priority of process "<<i+1<<": ";
    cin>>proc[i].priority;
    proc[i].remainingpriority=proc[i].priority;
}
    priority(proc,n);
    break;
case 6:
for(int i=0;i<n;i++){
    cout<<"enter priority of process "<<i+1<<": ";
    cin>>proc[i].priority;
    proc[i].remainingpriority=proc[i].priority;
}
    priority2(proc,n);
    break;
default:
cout<<"Invalid option"<<endl;
    break;
}

return 0;
}