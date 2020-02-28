#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;

#define MAX2 13
#define MAX1 16

int n,w,h;
int ans=0;
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

bool range(int x,int y){
    return 0<=x && x<h && 0<=y && y<w;
}
void BFS(int col,int& sol,int tempmap[][MAX2]){
    int row=h;
    for(int i=0;i<h;i++){
        if(tempmap[i][col]!=0){
            row=i;
            break;
        }
    }
    if(row==h)
        return;
    
    queue <pair<int,int>> q;
    bool visited[MAX1][MAX2]={false,};
    visited[row][col]=true;
    q.push({row,col});
    while(!q.empty()){
        pair<int,int> current=q.front();
        int power=tempmap[current.first][current.second];
        tempmap[current.first][current.second]=0;
        sol--;
        q.pop();
        for(int i=0;i<4;i++){
            pair<int,int> next=current;
            for(int j=0;j<power-1;j++){
                next.first+=dx[i];
                next.second+=dy[i];
                if(range(next.first,next.second) && !visited[next.first][next.second] && tempmap[next.first][next.second]!=0){
                    q.push(next);
                    visited[next.first][next.second]=true;
                }
            }
        }
    }
}
void moving(int tempmap[][MAX2]){
    vector <int> v[MAX2];
    int tempmap2[MAX1][MAX2]={0,};
    memcpy(tempmap2,tempmap,sizeof(tempmap2));
    memset(tempmap, 0, sizeof(tempmap2));
    
    for(int i=0;i<w;i++){
        int k=h-1;
        for(int j=h-1 ; j>=0 ; j--){
            if(tempmap2[j][i]==0)
                continue;
            tempmap[k--][i]=tempmap2[j][i];
            
        }
    }
    
}
void DFS(int idx,int sol,int mymap[][MAX2]){
    if(idx>=n){
        ans=min(ans,sol);
        return;
    }
    
    for(int i=0;i<w;i++){
        int tempmap[MAX1][MAX2]={0,};
        int tempsol=sol;
        memcpy(tempmap,mymap, sizeof(tempmap));
        BFS(i,tempsol,tempmap);
        moving(tempmap);
        DFS(idx+1,tempsol,tempmap);
    }
}

int main(){
    
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        cin>>n>>w>>h;
        int mymap[MAX1][MAX2]={0,};
        int sol=0;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                cin>>mymap[i][j];
                if(mymap[i][j]!=0)
                    sol++;
            }
        }
        ans=sol;
        DFS(0,sol,mymap);
        cout<<"#"<<t<<" "<<ans<<"\n";
    }
}
