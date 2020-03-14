#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int MAX=105;
const int INF=987987987;

int n,m;
int mymap[MAX][MAX]={0,};
int mydata[MAX][MAX]={0,};

vector <int> island[7]; //1번부터 시작 아일랜드별 연결된 아일랜드
vector <pair<int,int>> node[7]; //아일랜드별 노드
bool flagisland[7]={false,};
int sol=INF;
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
int numofisland=0;
bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<m;
}

int BFS2(){
    queue <int> q;
    q.push(1);
    int num=1;
    flagisland[1]=true;
    while(!q.empty()){
        int current=q.front();
        q.pop();
        for(int i=0;i<island[current].size();i++){
            int next=island[current][i];
            if(!flagisland[next]){
                flagisland[next]=true;
                num++;
                q.push(next);
            }
        }
    }
    return num;
}
int makebridge(int idx,pair<int,int> current,int dir,int num){ //idx=현재섬번호

    pair<int,int> next={current.first+dx[dir],current.second+dy[dir]};
    if(!range(next.first,next.second)||mydata[next.first][next.second]==idx) //다음 노드가 맵안에 존재하지 않으면 종료 && 다음노드가 현재섬이면 종료
        return 0;
    else if(mymap[next.first][next.second]==0){ //다음노드가 바다이면 다음노드로 들어간다.
        return makebridge(idx,next,dir,num+1);
    }
    else{ // 다음 노드가 다른 나라이면
        
        for(int i=0;i<island[idx].size();i++){
            if(island[idx][i]==mydata[next.first][next.second]) //다음 노드가 다른 나라인데 이미 연결된 나라이면 종료
                return 0;
        }
        if(num<=1)
            return 0;
        // 다음 노드가 다른 나라인데 연결되지 않은 나라
        island[idx].push_back(mydata[next.first][next.second]);
        island[mydata[next.first][next.second]].push_back(idx);
        return num;
    }
}

void solution(int idx,int ans){
    if(idx>=numofisland){
        int flag=BFS2();
        if(flag>=numofisland){
            if(ans<sol)
                sol=ans;
        }
        memset(flagisland,false,sizeof(flagisland));
        return;
    }
    int plus=0;
   
    for(int i=0;i<node[idx].size();i++){
        pair<int,int> current=node[idx][i]; //현재 섬에 대한 시작점

        for(int j=0;j<4;j++){
  
            plus=makebridge(idx,current,j,0);
            if(plus>0){
                solution(idx+1,ans+plus);
                island[island[idx][island[idx].size()-1]].pop_back();
                island[idx].pop_back();
            }
        }
    }
}

void BFS(int x,int y){
    queue <pair<int,int>> q;
    q.push({x,y});
    mydata[x][y]=numofisland;
    node[numofisland].push_back({x,y});
    while(!q.empty()){
        pair<int,int> current=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            pair<int,int> next ={current.first+dx[i],current.second+dy[i]};
            if(range(next.first,next.second) && mymap[next.first][next.second]==1 && mydata[next.first][next.second]==0){
                mydata[next.first][next.second]=numofisland;
                q.push(next);
                node[numofisland].push_back(next);
            }
        }
    }
}

void nIsiland(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mymap[i][j]==1 && mydata[i][j]==0){
                numofisland++;
                BFS(i,j);
                
            }
        }
    }
}
int main(){
    
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cin>>mymap[i][j];
        
    }
    
    nIsiland();
    solution(1,0);
    cout<< (sol==INF ? -1:sol);
    
}
