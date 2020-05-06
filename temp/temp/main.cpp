
/*
 14:10 03:06
 n*m
 세울 수 있는 벽: 3개, 꼭 세워야한다.
 0 빈칸, 1 벽, 2바이러스
 얻을 수 있는 안전 지역 크기의 최대값
 
 브루트 포스
 1. 바이러스 3개 위치 선택 60C3
 -> 콤비네이션
 
 2. 선택을 토대로 바이러스 확산 DFS
 */

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
const int MAX=10;


int mymap[MAX][MAX];
int n,m;
int safetyArea=-3;
int sol=0;
vector <pair<int,int>> birus;
bool visited[MAX][MAX];
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

bool range(int x,int y){
    return 0<= x && x<n && 0<=y && y<m;
}
int BFS(int x,int y){
    visited[x][y]=true;
    queue <pair<int,int>> q;
    q.push({x,y});
    int num=0;
    while(!q.empty()){
        pair<int,int> current=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            pair<int,int> next = {current.first+dx[i],current.second+dy[i]};
            if(range(next.first,next.second) && mymap[next.first][next.second]==0 && !visited[next.first][next.second]){
                visited[next.first][next.second]=true;
                num++;
                q.push(next);
            }
        }
    }
    return num;
}
void selection(int cnt,int x,int y){
    if(cnt>=3){
        int ans=safetyArea;
        memset(visited,false,sizeof(visited));
        for(int i=0;i<birus.size();i++)
            ans-=BFS(birus[i].first,birus[i].second);
        sol = ans> sol ? ans : sol;
        return;
    }
    if(y>=m){
        if(x>=n)
            return;
        y=0; x++;
    }
    for(int j=y;j<m;j++){
        if(mymap[x][j]==0){
            mymap[x][j]=1;
            selection(cnt+1,x,j+1);
            mymap[x][j]=0;
        }
    }
    for(int i=x+1;i<n;i++){
        for(int j=0;j<m;j++){
            if(mymap[i][j]==0){
                mymap[i][j]=1;
                selection(cnt+1,i,j+1);
                mymap[i][j]=0;
            }
        }
    }
    
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mymap[i][j];
            if(mymap[i][j]==0)
                safetyArea++;
            else if(mymap[i][j]==2)
                birus.push_back({i,j});
        }
    }
    //cout<<safetyArea;
    selection(0,0,0);
    cout<<sol;
}
