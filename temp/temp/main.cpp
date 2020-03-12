#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int MAX=13;
const int INF=987987987;

int n;
int people[MAX];
int visited[MAX]={0,};
int myteam[MAX]={0,};
int sol=987987987;
vector <int> mymap[MAX];

int BFS(int team,int node){
    
    queue <int> q;
    q.push(node);
    visited[node]=team;
    int num=people[node];
    while(!q.empty()){
        int current=q.front();
        q.pop();
        for(int i=0;i<mymap[current].size();i++){
            int next=mymap[current][i];
            if(visited[next]==0 && myteam[next]==team){
                visited[next]=team;
                num+=people[next];
                q.push(next);
            }
        }
    }
    return num;
}

void solution(int idx){
    if(idx>n){
        int num1=0;
        bool flag1=false;
        int num2=0;
        bool flag2=false;
        for(int i=1;i<=n;i++){
            if(flag1 && flag2)
                break;
            if(!flag1 && myteam[i]==1){
                num1=BFS(1,i);
                flag1=true;
            }
            else if(!flag2 && myteam[i]==2){
                num2=BFS(2,i);
                flag2=true;
            }
        }
      
        if(flag1 && flag2){
            bool flag3=false;
            for(int i=1;i<=n;i++){
                if(visited[i]==0)
                    flag3=true;
            }
            if(!flag3){
                int ans=abs(num1-num2);
                if(sol>ans)
                    sol=ans;
            }
        }
        memset(visited,0,sizeof(visited));
        return;
    }
    
    for(int i=1;i<=2;i++){
        myteam[idx]=i;
        solution(idx+1);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>people[i];
    
    for(int i=1;i<=n;i++){
        int temp;
        cin>>temp;
        for(int j=0;j<temp;j++){
            int temp2;
            cin>>temp2;
            mymap[i].push_back(temp2);
        }
    }
    solution(1);
    cout << (sol == INF ? -1 : sol);
}
