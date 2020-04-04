#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX=105;

class shark{
public:
    int x;
    int y;
    int v;
    int dir;
    int bulk;
    bool dead;
};
class fisherman{
public:
    int x;
    int y;
    int bulk;
};
int r,c,m;
vector<int> mymap[MAX][MAX];
int dx[5]={0,-1,1,0,0}; // 상 하 우 좌
int dy[5]={0,0,0,1,-1};
vector <shark> mydata;
fisherman me({0,0,0});

bool Standard(int A, int B)
{
    if (mydata[A].bulk > mydata[B].bulk) return true;
    return false;
}
 
bool range(int x,int y,int dir){
    return (dir==1 && x==1) ||(dir==2 && x==r) || (dir==3 && y==c) || (dir==4 && y==1);
}

void move(int idx){
    for(int i=0;i<mydata[idx].v;i++){
        if(range(mydata[idx].x,mydata[idx].y,mydata[idx].dir))
            mydata[idx].dir%2==0 ? mydata[idx].dir-- : mydata[idx].dir++;
        mydata[idx].x+=dx[mydata[idx].dir];
        mydata[idx].y+=dy[mydata[idx].dir];
    }
    mymap[mydata[idx].x][mydata[idx].y].push_back(idx);
}

void summary(int idx){
    int x= mydata[idx].x;
    int y= mydata[idx].y;
    sort( mymap[x][y].begin(), mymap[x][y].end(), Standard);
    int Live_Index = mymap[x][y][0];
    for(int i=1;i<mymap[x][y].size();i++){
        mydata[mymap[x][y][i]].dead=true;
        mydata[mymap[x][y][i]].x=-1;
        mydata[mymap[x][y][i]].y=-1;
    }
    mymap[x][y].clear();
    mymap[x][y].push_back(Live_Index);
}

void situation(){
    //낚시꾼 이동
    me.y++;
    if(me.y>c)
        return;
    //상어잡기
    for(int i=1;i<=r;i++){
        if(!mymap[i][me.y].empty() &&!mydata[mymap[i][me.y][0]].dead ){
            me.bulk+=mydata[mymap[i][me.y][0]].bulk;
            mydata[mymap[i][me.y][0]].dead=true;
            mydata[mymap[i][me.y][0]].x=-1;
            mydata[mymap[i][me.y][0]].y=-1;
            mymap[i][me.y].clear();
            break;
        }
    }
    for(int i=1;i<mydata.size();i++){
        if(!mydata[i].dead){
            mymap[mydata[i].x][mydata[i].y].clear();
        }
    }
    //상어 이동
    for(int i=1;i<mydata.size();i++){
        if(!mydata[i].dead){
            move(i);
        }
    }
    //summary
    for(int i=1;i<mydata.size();i++){
        if(!mydata[i].dead && mymap[mydata[i].x][mydata[i].y].size()>1)
            summary(i);
    }
    situation();
}

int main(){
    cin>>r>>c>>m;
    
    mydata.push_back({-1,-1,-1,-1-1});
    for(int i=1;i<=m;i++){
        int temp1,temp2,temp3,temp4,temp5;
        cin>>temp1>>temp2>>temp3>>temp4>>temp5;
        if(temp4==1 || temp4==2){
            int Rotate = (r - 1) * 2;
            if (temp3 >= Rotate) temp3 = temp3 % Rotate;
        }
        else{
            int Rotate = (c - 1) * 2;
            if (temp3 >= Rotate) temp3 = temp3 % Rotate;
        }
        mydata.push_back({temp1,temp2,temp3,temp4,temp5});
        mymap[temp1][temp2].push_back(i);
        
    }
    situation();
    cout<<me.bulk;
}
