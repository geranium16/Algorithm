#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
const int MAX=302;

int n,m;
int mymap[MAX][MAX]={0,};
int mymap2[MAX][MAX]={0,};
bool visited[MAX][MAX]={false,};
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<m;
}

void BFS(int x,int y){
    queue <pair<int,int>> q;
    q.push({x,y});
    visited[x][y]=true;
    while(!q.empty()){
        pair<int,int> current = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            pair<int,int> next={current.first+dx[i],current.second+dy[i]};
            if(range(next.first,next.second) && mymap[next.first][next.second]!=0 && !visited[next.first][next.second]){
                visited[next.first][next.second]=true;
                q.push(next);
            }
        }
    }
}
int divideCheck(){
    bool massFlag=false; //두덩어리이상체크  True: 두덩어리 이상
    bool noiceFlag=true; //빙하가 모두 녹았을 경우 체크 True: 다녹음
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mymap[i][j]!=0 && !visited[i][j]){
                noiceFlag=false;
                if(massFlag)
                    return 1;
                massFlag=true;
                BFS(i,j);
            }
        }
        
    }
    if(noiceFlag)
        return 2;
    else
        return 0;
}
void iceCheck(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mymap[i][j]!=0){
                int num=0;
                for(int k=0;k<4;k++){
                    if(mymap[i+dx[k]][j+dy[k]]==0)
                        num++;
                }
                if(mymap[i][j]>=num)
                    mymap2[i][j]=mymap[i][j]-num;
                else
                    mymap2[i][j]=0;
            }
        }
    }
}

int solution(int idx){
    
    memset(visited,false,sizeof(visited));
    memset(mymap2,0,sizeof(mymap2));
    int result = divideCheck();
    
    if(result==1)
        return idx;
    else if(result==2)
        return 0;
    
    iceCheck();
    memcpy(mymap,mymap2,sizeof(mymap2));
    return solution(idx+1);
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cin>>mymap[i][j];
    }
    
    cout<<solution(0);
}
