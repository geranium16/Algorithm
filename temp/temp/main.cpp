#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAX =14;

class horse{
public:
    int x;
    int y;
    int idx;
    int dir;
};

int n,k;
int mycolor[MAX][MAX];
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
int change_dir[4]={1,0,3,2};
vector <horse> mydata;
vector <horse> mymap[MAX][MAX];
bool range(int x,int y){
    return 1<=x && x<=n && 1<=y && y<=n;
}
int BFS(int cnt){
    if(cnt>1000)
        return -1;
    
    for(int i=0;i<k;i++){
        horse current =mydata[i];
        horse next = {current.x+dx[current.dir],current.y+dy[current.dir],current.idx,current.dir};
        if(!range(next.x,next.y) || mycolor[next.x][next.y]==2){
            next.dir = change_dir[next.dir];
            mydata[i].dir=next.dir;
            next.x=current.x+dx[next.dir];
            next.y=current.y+dy[next.dir];
            if(!range(next.x,next.y) || mycolor[next.x][next.y]==2)
                continue;
        }
        
        int start_idx=0;
        vector <horse> temp;
        bool flag=false;
        for(int j=0;j<mymap[current.x][current.y].size();j++){
            if(mymap[current.x][current.y][j].idx==i){
                start_idx=j;
                flag=true;
            }
            if(flag){
                mydata[mymap[current.x][current.y][j].idx].x=next.x;
                mydata[mymap[current.x][current.y][j].idx].y=next.y;
                temp.push_back(mydata[mymap[current.x][current.y][j].idx]);
            }
        }
        if(mycolor[next.x][next.y]==1)
            reverse(temp.begin(),temp.end());
        
        for(int j=0;j<temp.size();j++){
            mymap[next.x][next.y].push_back(temp[j]);
            mymap[current.x][current.y].pop_back();
        }
        if(mymap[next.x][next.y].size()>=4)
            return cnt;
    }
    return BFS(cnt+1);
}


int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cin>>mycolor[i][j];
    }
    
    for(int i=0;i<k;i++){
        int a,b,c;
        cin>>a>>b>>c;
        mydata.push_back({a,b,i,c-1});
        mymap[a][b].push_back(mydata[i]);
    }
    cout<<BFS(1);
}
