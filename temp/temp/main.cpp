#include <iostream>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;
const int MAX =52;


int n,l,r;
int mymap[MAX][MAX];
bool visited[MAX][MAX];
int unionMap[MAX][MAX];
vector<int> unionSum;  //sum /
vector<int> unionNum;
int unionNumber=1;
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
bool finish=false;

bool range(int x,int y){
    return 0<= x  && x<n && 0<= y && y<n;
}

bool BFS(int x,int y){
    queue <pair<int,int>> q;
    q.push({x,y});
    visited[x][y]=true;
    bool BFSflag=false;
    while(!q.empty()){
        pair<int,int> current=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            pair<int,int> next={current.first+dx[i],current.second+dy[i]};
            if(range(next.first,next.second) && !visited[next.first][next.second]){
                int personDiff=abs(mymap[current.first][current.second]-mymap[next.first][next.second]);
                if( l<= personDiff && personDiff<=r){
                    BFSflag=true;
                    finish = true;
                    if(unionNum[unionNumber]==0){
                        unionSum[unionNumber]+=mymap[current.first][current.second];
                        unionNum[unionNumber]++;
                        unionMap[current.first][current.second]=unionNumber;
                    }
                    visited[next.first][next.second]=true;
                    unionSum[unionNumber]+=mymap[next.first][next.second];
                    unionNum[unionNumber]++;
                    unionMap[next.first][next.second]=unionNumber;
                    q.push(next);
                }
            }
        }
    }
    return BFSflag;
}

void update(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(unionMap[i][j]==0)
                continue;
            mymap[i][j]=unionSum[unionMap[i][j]]/unionNum[unionMap[i][j]];
        }
    }
}
void init(){
    memset(visited,false,sizeof(visited));
    memset(unionMap,0,sizeof(unionMap));
    unionSum
    unionNumber=1;
    finish=false;
}

int solution(int idx){
    init();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!visited[i][j]){
                if(BFS(i,j))
                    unionNumber++;
            }
        }
    }
    if(!finish)
        return idx;
    update();
    return solution(idx+1);
}


int main(){
    
    cin>>n>>l>>r;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cin>>mymap[i][j];
    }
    cout<<solution(0);
}
