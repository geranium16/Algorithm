#include <iostream>
#include <queue>
using namespace std;
const int MAX=10;
const int INF=987987987;

bool mymap[MAX][MAX];
bool visited[MAX][MAX];
int paper[5]={0,};
int ans=INF;
bool range(int x,int y){
    return 0<=x && x<MAX  && 0<=y && y<MAX;
}
bool confirm(){
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            if(mymap[i][j]&&!visited[i][j])
                return false;
        }
    }
    return true;
}
int BFS(int x,int y){
    
    for(int i=1;i<5;i++){
        for(int j=0;j<i;j++){ //횟수
            if( !range(x+j,y+i) || visited[x+j][y+i] || !mymap[x+j][y+i] )
                return i-1;
            if( !range(x+i,y+j) || visited[x+i][y+j] ||!mymap[x+i][y+j] )
                return i-1;
        }
        if( !range(x+i,y+i) || visited[x+i][y+i] || !mymap[x+i][y+i] )
            return i-1;
    }
    return 4;
}
void visitecheck(int x,int y, int maxbulk){
    for(int i=0;i<=maxbulk;i++){
        for(int j=0;j<=maxbulk;j++){
            visited[x+i][y+j]=true;
        }
    }
}
void visitecheck2(int x,int y,int maxbulk){
    for(int i=0;i<maxbulk;i++){
        visited[x+maxbulk][y+i]=false;
        visited[x+i][y+maxbulk]=false;
    }
    visited[x+maxbulk][y+maxbulk]=false;
}
void DFS(int x,int y,int sol){
    if(y>=MAX){
        x+=1;
        y=0;
    }
    if(x>=MAX){
        if(confirm())
            ans=min(ans,sol);
        return;
    }
    
    if(mymap[x][y] && !visited[x][y]){
        int maxbulk=BFS(x,y);
        visitecheck(x,y,maxbulk);
        for(int i=maxbulk;i>=0;i--){
            if(paper[i]<5){
                paper[i]++;
                DFS(x,y+i+1,sol+1);
                paper[i]--;
            }
            visitecheck2(x,y,i);
        }
        
    }
    else
        DFS(x,y+1,sol);
    
    
}
int main(){
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++)
            cin>>mymap[i][j];
    }
    DFS(0,0,0);
    if(ans==INF)
        cout<<-1;
    else
        cout<<ans;
}
