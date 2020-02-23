#include <iostream>
#include <vector>
using namespace std;
#define MAX 52

class robot{
public:
    int x;
    int y;
    int dir;
    robot(int x,int y,int dir): x(x),y(y),dir(dir){};
};

int n,m;
bool mymap[MAX][MAX];
int dx[4]={-1,0,1,0}; // 0:상 1:우 2:하 3:좌
int dy[4]={0,1,0,-1};
int changedir[4]={3,0,1,2};
int backdir[4]={2,3,0,1};
bool visited[MAX][MAX]={false,};
robot myrobot(0,0,0);

bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<m;
}

int  DFS(int cnt){
    visited[myrobot.x][myrobot.y]=true;
    cout<<cnt<<":"<<myrobot.x<<","<<myrobot.y<<"\n";
    for(int i=0;i<4;i++){
        myrobot.dir=changedir[myrobot.dir];
        int x=myrobot.x+dx[myrobot.dir];
        int y=myrobot.y+dy[myrobot.dir];
        if(range(x,y) && !mymap[x][y] && !visited[x][y]){
            myrobot.x+=dx[myrobot.dir];
            myrobot.y+=dy[myrobot.dir];
            return DFS(cnt+1);
        }
    }
    myrobot.dir=backdir[myrobot.dir];
    myrobot.x+=dx[myrobot.dir];
    myrobot.y+=dy[myrobot.dir];
    if(range(myrobot.x,myrobot.y) && !mymap[myrobot.x][myrobot.y]){
        myrobot.dir=backdir[myrobot.dir];
        //cout<<cnt<<":"<<myrobot.x<<","<<myrobot.y<<"\n";
        return DFS(cnt);
    }
    else{
        return cnt;
    }
    return -1;
}
int main(){
    cin>>n>>m;
    cin>>myrobot.x>>myrobot.y>>myrobot.dir;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cin>>mymap[i][j];
    }
    cout<<DFS(1);
}
