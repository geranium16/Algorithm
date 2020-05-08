#include <iostream>
#include <vector>
using namespace std;
const int MAX= 102;

class curve{
public:
    int x; //세로
    int y; //가로
    int d; // 방향
    int g; //세대
};

int n; //드래곤 커브의 개수
int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};

bool mymap[MAX][MAX];
vector <vector<curve>> mydata;

bool range(int x,int y){
    return 0<=x && x<=100 && 0<=y && y<=100;
}

void simulation(){
    
    for(int i=0;i<n;i++){
        for(int k=0;k<mydata[i][0].g;k++){
            int last_idx=int(mydata[i].size())-1;
            curve last=mydata[i][last_idx];
            vector <curve> temp;
            for(int j=last_idx;j>0;j--){
                int new_dir = (mydata[i][j].d+1)%4;
                last.x+=dx[new_dir];
                last.y+=dy[new_dir];
                last.d=new_dir;
                mydata[i].push_back(last);
                mymap[last.x][last.y]=true;
            }
        }
    }
}

int main(){
    cin>>n;
    int x,y,d,g;
    for(int i=0;i<n;i++){
        cin>>x>>y>>d>>g; //시작점
        vector <curve> temp;
        mydata.push_back(temp);
        mydata[i].push_back({y,x,d,g});
        if(range(y+dy[d],x+dx[d])){
            mydata[i].push_back({y+dx[d],x+dy[d],d,g});
            mymap[y][x]=true;
            mymap[y+dx[d]][x+dy[d]]=true;
        }
    }
    
    simulation();
    
    int sol=0;
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            if(mymap[i][j] && mymap[i][j+1] && mymap[i+1][j] && mymap[i+1][j+1])
                sol++;
        }
    }
    cout<<sol;
}
