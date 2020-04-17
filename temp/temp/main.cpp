#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX=22;
const int INF=987987;

int n;
int mymap[MAX][MAX];
int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};
pair<int,int> shark;

bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<n;
}
int BFS(int bulk,int bulk2,int time){
    queue <pair<int,int>> q;
    queue <int> t;
    q.push(shark);
    t.push(0);
    bool visited[MAX][MAX]={false,};
    visited[shark.first][shark.second]=true;
    
    bool flag=false;
    pair<int,int> sol={INF,INF};
    int dis=INF;
    while(!q.empty()){
        pair<int,int> current = q.front();
        int current_t=t.front();
        q.pop();
        t.pop();
        if(current_t>=dis)
            continue;
        for(int i=0;i<4;i++){
            pair<int,int>next={current.first+dx[i],current.second+dy[i]};
            if(range(next.first,next.second)){
                if((mymap[next.first][next.second]==0|| mymap[next.first][next.second]==bulk) && !visited[next.first][next.second]){
                    visited[next.first][next.second]=true;
                    q.push(next);
                    t.push(current_t+1);
                }
                else if(0<mymap[next.first][next.second] && mymap[next.first][next.second]<bulk){
                    dis=current_t+1;
                    flag=true;
                    if(sol.first==INF)
                        sol=next;
                    else if(sol.first>next.first)
                        sol=next;
                    else if(sol.first==next.first && sol.second>next.second)
                        sol=next;
                }
            }
        }
    }
    if(flag){
        shark=sol;
        mymap[shark.first][shark.second]=0;
        bulk2++;
        if(bulk==bulk2){
            bulk++;
            bulk2=0;
        }
        return BFS(bulk,bulk2,time+dis);
    }
    return time;
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>mymap[i][j];
            if(mymap[i][j]==9){
                shark={i,j};
                mymap[i][j]=0;
            }
        }
    }
    cout<< BFS(2,0,0);
}
