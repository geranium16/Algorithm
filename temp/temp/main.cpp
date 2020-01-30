#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX 55

int n,m;
int r,c; // y,x
int l; //소요시간
int sol;

int mymap[MAX][MAX]; //나갈 때, 들어 올때
pair<int,int> dir[4]={{-1,0},{1,0},{0,-1},{0,1}};
int dir2[4]={1,0,3,2};
bool pipe[8][4] = { {0,0,0,0},{1,1,1,1},{1,1,0,0},{0,0,1,1},{1,0,0,1},{0,1,0,1},{0,1,1,0},{1,0,1,0}};

int visited[MAX][MAX];

bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<m;
}
void BFS(){
    queue <pair<int,int>> q;
    q.push({r,c});
    visited[r][c]=1;
    while( !q.empty() && visited[q.front().first][q.front().second]<l ){
        pair<int,int> current=q.front();
        q.pop();
        
        for(int i=0;i<4;i++){
            if(pipe[mymap[current.first][current.second]][i]){
                pair<int,int> next=current;
                next.first+=dir[i].first;
                next.second+=dir[i].second;
                if(range(next.first,next.second) && visited[next.first][next.second]==0){
                    if( pipe[mymap[next.first][next.second]][dir2[i]]){
                        q.push(next);
                        visited[next.first][next.second]=visited[current.first][current.second]+1;
                        sol++;
                    }
                }
            }
        }
    }
}

void init(){
    sol=1;
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            mymap[i][j]=0;
            visited[i][j]=0;
        }
    }
}
int main(){
    int tc;
    cin>>tc;
  
    for(int t=1;t<=tc;t++){
        init();
        cin>>n>>m>>r>>c>>l;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>mymap[i][j];
            }
        }
        BFS();
        cout<<"#"<<t<<" "<<sol<<"\n";
    }
}



