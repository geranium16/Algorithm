#include <iostream>
#include <vector>
using namespace std;

#define MAX 105

class node{
public:
    int x;
    int y;
    int n;
    int dir;
};

pair<int,int> dir[5]={{0,0},{-1,0},{1,0},{0,-1},{0,1}}; //1 상 2 하 3좌 4우
int dir2[5]={0,2,1,4,3}; //방향체인지
vector <node> mynode;
vector <int> mymap[MAX][MAX];
int sol=0;
int n,m,k;

bool range(int x,int y){
    return 0<x && x<n-1 && 0<y && y<n-1;
}

void simulation(int hour){
    if(hour>=m){
        for(int i=0;i<mynode.size();i++)
            sol+=mynode[i].n;
        return;
    }
  
    for (int i = 0; i < mynode.size(); i++) {
                  /*아래 코드가 이동영역에 들어있어서 Fail이났다.*/
                  //아래 코드는 이동전 map정보를 없애주기 위해서 있는 것이다.
                  //근데 만약 이동전 위치가 다른 군집들의 다음 위치였다면
                  //이 다른 군집들의 위치를 모두 없애주는 오류가 발생한다.
                  //즉 idx=3일 떄 push_back 된게 idx=5일 때 없어질 수 있음
                  //따라서 따로 빼서 이러한 경우를 없애줌
        mymap[mynode[i].x][mynode[i].y].clear();
    }
    /*이동*/
    for(int i=0;i<mynode.size();i++){
        mynode[i].x+=dir[mynode[i].dir].first;
        mynode[i].y+=dir[mynode[i].dir].second;
        mymap[mynode[i].x][mynode[i].y].push_back(i);
    }
    
    /* 확인 시작*/
    for(int i=0;i<mynode.size();i++){
        if(mynode[i].n==0) continue;
        
        if(!range(mynode[i].x,mynode[i].y)){
            mynode[i].n/=2;
            mynode[i].dir=dir2[mynode[i].dir];
        }
        //현재노드에 n을 다더해서 넣고 방향을 최대치를 가지고 있는걸로 갱신할 것이다.
        else if(mymap[mynode[i].x][mynode[i].y].size()>1){
            int maxn=mynode[i].n;
            int maxdir=mynode[i].dir;
            for(int j=0;j<mymap[mynode[i].x][mynode[i].y].size();j++){
                int idx=mymap[mynode[i].x][mynode[i].y][j];
                if(idx!=i){
                    mynode[i].n+=mynode[idx].n;
                    if(maxn<mynode[idx].n){
                        maxn=mynode[idx].n;
                        maxdir=mynode[idx].dir;
                    }
                    mynode[idx].n=0;
                }
            }
            mynode[i].dir=maxdir;
        }
    }
    simulation(hour+1);
    
}
void init(){
    sol=0;
    mynode.clear();
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++)
            mymap[i][j].clear();
    }
}
int main(){
    int testcase;
    cin>>testcase;
    for(int t=1;t<=testcase;t++){
        init();
        cin>>n>>m>>k;
        for(int i=0;i<k;i++){
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            mynode.push_back({a,b,c,d});
            mymap[a][b].push_back(i);
        }
        
        simulation(0);
        cout<<"#"<<t<<" "<<sol<<"\n";
    }
}
