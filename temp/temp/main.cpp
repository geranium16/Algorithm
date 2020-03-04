#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX 9

int n,m;
int mymap[MAX][MAX];
int visited[MAX][MAX]={0,};
int dx[4]={-1,0,1,0}; //상우하좌
int dy[4]={0,1,0,-1};
int finishidx=0;
int ans=987987987;

vector<vector<int>> cctv[6]; // 3차원벡터
vector <pair<int,int>> nodes;

bool range(int x,int y){
    return 0<= x && x<n && 0<=y && y<m;
}

void makevector(){
    cctv[1]={vector<int>({0}),
        vector<int>({1}),
        vector<int>({2}),
        vector<int>({3})};
    cctv[2]={vector<int>({0,2}),
        vector<int>({1,3})};
    cctv[3]={vector<int>({0,1}),
        vector<int>({1,2}),
        vector<int>({2,3}),
        vector<int>({3,0})};
    cctv[4]={vector<int>({0,1,2}),
        vector<int>({1,2,3}),
        vector<int>({2,3,0}),
        vector<int>({3,0,1})};
    cctv[5]={vector<int>({0,1,2,3})};
}

class node{
public:
    int x;
    int y;
    int dir;
};

void cameraRange(int cameraNum,int cameraDir,int x,int y,int flag){ //BFS
    queue <node> q;
    for(int i=0;i<cctv[cameraNum][cameraDir].size();i++){
        q.push({x,y,cctv[cameraNum][cameraDir][i]});
    }
    visited[x][y]+=flag;
    
    while(!q.empty()){
        node current=q.front();
        q.pop();
        current.x+=dx[current.dir];
        current.y+=dy[current.dir];
        if(range(current.x,current.y) && mymap[current.x][current.y]!=6){
            visited[current.x][current.y]+=flag;
            q.push(current);
        }
    }
}

void makeCamera(int idx){ //DFS
    if(finishidx<=idx){
        int sol=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mymap[i][j]!=6 && visited[i][j]==0)
                    sol++;
            }
        }
        ans=min(ans,sol);
        return;
    }
    
    int cameraNum=mymap[nodes[idx].first][nodes[idx].second];
    for(int i=0;i<cctv[cameraNum].size();i++){
        cameraRange(cameraNum,i,nodes[idx].first,nodes[idx].second,1);
        makeCamera(idx+1);
        cameraRange(cameraNum,i,nodes[idx].first,nodes[idx].second,-1);
    }
    
}
int main(){
        
    makevector();
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mymap[i][j];
            if(1<=mymap[i][j] && mymap[i][j]<=5)
                nodes.push_back({i,j});
        }
    }
    finishidx=nodes.size();
    makeCamera(0);
    cout<<ans<<"\n";
    
}
