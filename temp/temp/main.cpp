#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 18
int n;
int mymap[MAX][MAX];
bool visited[10];
int sol=987987;
int cal(vector <int>& team){
    int ans=0;
    for(int i=0;i<n/2;i++){
        for(int j=0;j<n/2;j++)
            ans+=mymap[team[i]][team[j]];
        
    }
    return ans;
}
void combination(){
    vector <int> a;
    vector <int> b;
    for(int i=0;i<n;i++){
        
        if(visited[i])
            a.push_back(i);
        else
            b.push_back(i);
    }
    int result=abs(cal(a)-cal(b));
    if(sol>result)
        sol=result;
    
}
void DFS(int idx,int cnt){
    
    if(cnt>=n/2){
        combination();
        return;
    }
    for(int i=idx;i<n;i++){
        visited[i]=true;
        DFS(i+1,cnt+1);
        visited[i]=false;
    }
}
int main(){
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        sol=987987987;
        cin>>n;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cin>>mymap[i][j];
        }
        DFS(0,0);
        cout<<"#"<<t<<" "<<sol<<"\n";
    }

}
