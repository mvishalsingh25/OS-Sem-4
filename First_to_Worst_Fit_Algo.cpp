#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void printAllocations(vector<pair<int,int>>allocations){
    for(int i=0;i<allocations.size();i++){
   cout<<"P"<<allocations[i].second<<"------> Block"<<allocations[i].first<<endl;
    }
}

void printFragmentations(vector<pair<int,int>>block,int sum){
    cout<<"Total internal fragmentation: "<<sum<<endl;
    sum=0;
    for(int i=0;i<block.size();i++){
        sum+=block[i].first;
    }
    cout<<"Total external fragmentation: "<<sum<<endl;

}

void firstfit(vector<pair<int,int>>block ,int memory[],int m){
    cout<<"FIRST FIT: "<<endl;
vector<pair<int,int>>allocations;
int sum=0;
for(int i=0;i<m;i++){
    for(int j=0;j<block.size();j++){
      if(memory[i]<=block[j].first){
        allocations.push_back({j+1,i+1});
        sum+=block[j].first-memory[i];
        block[j].first=0;
        break;
      }
    }
}
printAllocations(allocations);
printFragmentations(block,sum);
cout<<endl;
}

void nextfit(vector<pair<int,int>>& block, int memory[], int m) {
    cout << "NEXT FIT: " << endl;
    vector<pair<int,int>> allocations;
    int sum = 0;
    int j = 0; 
    for(int i = 0; i < m; i++) {
        int initialJ = j;  
        while(true) {
            if(memory[i] <= block[j].first && block[j].first != 0) {
                allocations.push_back({block[j].second, i+1});
                sum += block[j].first - memory[i];
                block[j].first = 0;
                break;
            }
            j = (j + 1) % block.size(); 
            if(j == initialJ) {
                break;
            }
        }
    }
    printAllocations(allocations);
    printFragmentations(block, sum);
    cout << endl;
}


void bestfit(vector<pair<int,int>>block,int memory[],int m){
    cout<<"BEST FIT: "<<endl;
    sort(block.begin(),block.end());
    vector<pair<int,int>>allocations;
   int sum=0;
   for(int i=0;i<m;i++){
    for(int j=0;j<block.size();j++){
        if(memory[i]<=block[j].first){
            allocations.push_back({block[j].second,i+1});
            sum+=block[j].first-memory[i];
            block[j].first=0;
            break;
        }
    }
   }
   printAllocations(allocations);
   printFragmentations(block,sum);
   cout<<endl;
}

void worstfit(vector<pair<int,int>>block,int memory[],int m){
    cout<<"WORST FIT: "<<endl;
    sort(block.begin(),block.end());
    vector<pair<int,int>>allocations;
    int sum=0;
    for(int i=0;i<m;i++){
        for(int j=block.size()-1;j>=0;j--){
            if(memory[i]<=block[j].first){
                allocations.push_back({block[j].second,i+1});
                sum+=block[j].first-memory[i];
                block[j].first=0;
                break;
            }
        }
    }
    printAllocations(allocations);
    printFragmentations(block,sum);

}
int main(){
int n;
cout<<"Enter number of blocks: ";
cin>>n;
int m;
cout<<"Enter number of processes: ";
cin>>m;

if(n<=0 ||m<=0){
    cout<<"Invalid input.Number of blocks and processes should be positive"<<endl;
    return 1; 
}
cout<<endl;
vector<pair<int,int>>block;
int memory[m];
for(int i=0;i<n;i++){
    int temp;
    cout<<"Enter size of block "<<i+1<<": ";
    cin>>temp;
    if(temp<=0){
        cout<<"Invalid block size.Please enter a positive number"<<endl;
        return 1;
    }
    block.push_back({temp,i+1});
}

cout<<endl;
for(int i=0;i<m;i++){
    cout<<"Enter size of process "<<i+1<<": ";
    cin>>memory[i];
    if(memory[i]<=0){
        cout<<"Invalid memory size.Please enter a positive number"<<endl;
        return 1;
    }
}
cout<<endl;
while(1){
int option;
cout<<"1.First Fit"<<endl;
cout<<"2.Next Fit"<<endl;
cout<<"3.Best Fit"<<endl;
cout<<"4.Worst Fit"<<endl;
cout<<"5.Exit"<<endl;
cout<<endl;
cout<<"Enter your option: ";
cin>>option;
if(option==5){
    cout<<"Exiting of program"<<endl;
    break;
}
switch (option)
{
case 1:
    firstfit(block,memory,m);
    break;
case 2:
    nextfit(block,memory,m);
    break;
case 3:
    bestfit(block,memory,m);
    break;
case 4:
worstfit(block,memory,m);
    break;

default:
cout<<"Invalid choice"<<endl;
break;
}
}
return 0;
}