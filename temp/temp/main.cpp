


/*
 1. 모든 섬찾기 -> 재귀를 이용한 dfs
 다리를 놓을 수 있는 모든 경우를 체크함
 섬을 Graph의 Vertex로, 다리를 놓는 경우를 Edge로 모델링함
 그래프에 대한 최소 스패닝 트리를 구한다.
 MST의 길이를 리턴, MST를 구할 수 없는 경우 01를 리턴
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX=13;

class Edge{
public:
    int node[2];
    int distance;
    Edge(int a,int b,int distance){
        this->node[0]=a;
        this->node[1]=b;
        this->distance=distance;
    }
    bool operator <(const Edge &edge) const{
        return this-> distance <edge.distance;
    }
};



int mymap[MAX][MAX];
int n,m;
int island_cnt=0;
vector <Edge> edges;
vector <pair<int,int>> nodes[7];
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
int dsu[7];
int sol=0;
bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<m;
}
void find_island(int x,int y, int island_cnt){
    queue <pair<int,int>> q;
    q.push({x,y});
    mymap[x][y]=island_cnt;
    
    while(!q.empty()){
        pair<int,int> current=q.front();
        q.pop();
        bool water=false;
        for(int i=0;i<4;i++){
            pair<int,int> next={current.first+dx[i],current.second+dy[i]};
            if(range(next.first,next.second) && mymap[next.first][next.second]==-1){
                q.push(next);
                mymap[next.first][next.second]=island_cnt;
            }
            if(mymap[next.first][next.second]==0)
                water=true;
        }
        if(water)
            nodes[mymap[current.first][current.second]].push_back(current);
    }
}

void makeEdge(int island_idx,int x,int y,int dir,int cnt){
    
    pair<int,int> next= {x+dx[dir],y+dy[dir]};
    if(range(next.first,next.second)){
        if(mymap[next.first][next.second]==0)
            makeEdge(island_idx,next.first,next.second,dir,cnt+1);
        else if(mymap[next.first][next.second] > island_idx && cnt>1)
            edges.push_back(Edge(island_idx,mymap[next.first][next.second],cnt));
    }
    
}
int getParent(int x){
    if(dsu[x]==x) return x;
    return getParent(dsu[x]);
}
void unionParent(Edge temp){
    int a=getParent(temp.node[0]);
    int b=getParent(temp.node[1]);
    if(a!=b){
        if(a<b) dsu[b]=a;
        else dsu[a]=b;
        sol+=temp.distance;
    }
    
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mymap[i][j];
            if(mymap[i][j]==1) mymap[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mymap[i][j]==-1){
                find_island(i,j,++island_cnt);
            }
        }
    }
    for(int i=1;i<island_cnt;i++){
        for(int j=0;j<nodes[i].size();j++){
            for(int k=0;k<4;k++){
                makeEdge(i,nodes[i][j].first,nodes[i][j].second,k,0);
            }
        }
    }


    sort(edges.begin(),edges.end());
    
    for(int i=1;i<=island_cnt;i++)
        dsu[i]=i;
    for(int i=0;i<edges.size();i++)
        unionParent(edges[i]);
 
    int dsu_first=getParent(1);
    for(int i=2;i<=island_cnt;i++){
        if(dsu_first!=getParent(i)){
            sol=-1;
            break;
        }
    }
    cout<<sol;
}
