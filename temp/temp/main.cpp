#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
#define MAX 30

int n,k;
int arr[MAX];
int rotnum=0;
vector <int> sol;
void rotation(){
    int temp=arr[n-1];
    for(int i=n-1;i>0;i--)
        arr[i]=arr[i-1];
    arr[0]=temp;
}

bool asc(int a,int b){
    return a>b;
}
void cal(){
    for(int i=0;i<4;i++){
        int temp=0;
        for(int j=0;j<rotnum;j++){
            temp=temp+arr[i*rotnum+j]*pow(16,rotnum-j-1);
        }
        if(find(sol.begin(),sol.end(),temp)==sol.end())
            sol.push_back(temp);
    }
}
void DFS(int idx){
    if(idx>=rotnum){
        sort(sol.begin(),sol.end(),asc);
        return;
    }
    cal();
    rotation();
    DFS(idx+1);
}


int main(){
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        cin>>n>>k;
        rotnum=n/4;
        sol.clear();
        for(int i=0;i<n;i++){
            char a;
            cin>>a;
            if('0'<=a && a <= '9')
                arr[i]=a-'0';
            else
                arr[i]=10+a-'A';
        }
        DFS(0);
        //    for(int i=0;i<sol.size();i++){
        //        cout<<sol[i]<<" ";
        //    }
        cout<<"#"<<t<<" "<<sol[k-1]<<"\n";
    }
}
