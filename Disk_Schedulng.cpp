#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

void FCFS(vector<int>arr,int head,int range){
    int sum=0;
    cout<<"Disc will be called in order of "<<endl;
    for(int i=0;i<arr.size();i++){
        sum+=abs(head-arr[i]);
        head=arr[i];
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"Total head movement"<<": "<<sum<<endl;
}
void SSTF(vector<int>arr,int head,int range){
    int sum=0;
    cout<<"Disc will be called in order of "<<endl;
    for(int i=0;i<arr.size();i++){
        int min=INT_MAX,k=0,temp=0;
        for(int j=0;j<arr.size();j++){
            temp=abs(head-arr[j]);
            if(temp<min){
                min=temp;
                k=j;
            }
        }
        cout<<arr[k]<<" ";
        sum+=min;
        head=arr[k];
        arr[k]=INT_MAX;
    }
    cout<<endl;
    cout<<"Total head movement: "<<sum<<endl;
}
int main(){
int n;
cout<<"enter number of requests: ";
cin>>n;
int head;
int range;
cout<<"enter the number of tracks: ";
cin>>range;
range--;
cout<<"enter the head position: ";
cin>>head;
vector<int>arr;
cout<<"enter the requests: ";
for(int i=0;i<n;i++){
    int temp;
    cin>>temp;
  arr.push_back(temp);
}
int opt;
cout<<"1. FCFS"<<endl;
cout<<"2.SSTF"<<endl;
cout<<"enter your option: ";
cin>>opt;
if(opt==1){
    FCFS(arr,head,range);
}
else if(opt==2){
    SSTF(arr,head,range);
}
return 0;
}