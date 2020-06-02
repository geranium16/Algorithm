#include <iostream>
#include <vector>
using namespace std;
const int MAX=14;

class horse{
public:
    int idx;
    int x;
    int y;
    int dir;
};

int n,k;
int mymap[MAX][MAX];
vector <horse> horses;
vector <horse> mydata[MAX][MAX];
int dx[5]={0,0,0,-1,1};
int dy[5]={0,1,-1,0,0};
int reverse_dir[5]={0,2,1,4,3};
bool final_flag=false;
int solution=-1;
bool range(int x,int y){
    return 1<=x && x<=n && 1<=y && y<=n;
}

bool finalcheck(int x,int y){
    if(mydata[x][y].size()>=4) return true;
    else return false;
}
void white(int idx,int x,int y){
    horse leader=horses[idx];
    int next_x =x+dx[leader.dir]; int next_y =y+dy[leader.dir];
    int idx2=0;
    for(int i=0;i<mydata[x][y].size();i++){
        if(mydata[x][y][i].idx==idx){
            idx2=i;
            break;
        }
    }
    for(int i=idx2;i<mydata[x][y].size();i++){
        horses[mydata[x][y][i].idx].x=x+dx[leader.dir];
        horses[mydata[x][y][i].idx].y=y+dy[leader.dir];
        mydata[next_x][next_y].push_back(horses[mydata[x][y][i].idx]);
        mydata[x][y].erase(mydata[x][y].begin()+i);
        i--;
    }
    final_flag=finalcheck(next_x,next_y);
}
void red(int idx,int x,int y){
    horse leader=horses[idx];
    int next_x =x+dx[leader.dir]; int next_y =y+dy[leader.dir];
    int idx2=0;
    for(int i=0;i<mydata[x][y].size();i++){
        if(mydata[x][y][i].idx==idx){
            idx2=i;
            break;
        }
    }
    
    for(int i = int(mydata[x][y].size())-1;i>=idx2;i--){
        horses[mydata[x][y][i].idx].x=x+dx[leader.dir];
        horses[mydata[x][y][i].idx].y=y+dy[leader.dir];
        mydata[next_x][next_y].push_back(horses[mydata[x][y][i].idx]);
    }
    for(int i=idx2;i<mydata[x][y].size();i++){
        mydata[x][y].erase(mydata[x][y].begin()+i);
        i--;
    }
    final_flag=finalcheck(next_x,next_y);
}
void blue(int idx,int x,int y){
    horses[idx].dir=reverse_dir[horses[idx].dir];
    for(int i=0;i<mydata[x][y].size();i++){
        if(mydata[x][y][i].idx==idx){
            mydata[x][y][i].dir=horses[idx].dir;
            break;
        }
    }
    int x_next = x+dx[horses[idx].dir]; int y_next = y+dy[horses[idx].dir];
    
    if(!range(x_next,y_next) ||mymap[x_next][y_next]==2)
        return;
    
    else if(mymap[x_next][y_next]==0)
        white(idx,x,y);
    
    else
        red(idx,x,y);
}

void simulation(int cnt){
    if(cnt>1000) return;
    
    for(int i=1;i<=k;i++){
        horse current = horses[i];
        horse next = {current.idx,current.x+dx[current.dir],current.y+dy[current.dir],current.dir};
        if(!range(next.x,next.y) ||mymap[next.x][next.y]==2)
            blue(i,current.x,current.y);
        
        else if(mymap[next.x][next.y]==0)
            white(i,current.x,current.y);
        
        else
            red(i,current.x,current.y);
        if(final_flag){
            solution=cnt;
            return;
        }
    }
    simulation(cnt+1);
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cin>>mymap[i][j];
    }
    horses.push_back({0,0,0});
    for(int i=1;i<=k;i++){
        int a,b,c;
        cin>>a>>b>>c;
        horses.push_back({i,a,b,c});
        mydata[a][b].push_back({i,a,b,c});
    }
    simulation(1);
    cout<<solution;
    
}
