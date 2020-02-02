#include <iostream>
#include <vector>
using namespace std;

#define MAX 4000

class atom{
public:
    int x;
    int y;
    int dir;
    int k;

    
    atom(int x,int y,int dir,int k):x(x),y(y),dir(dir),k(k){};
};

int n;
int sol=0;

int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
vector<int> visited[MAX+50][MAX+50];
vector <atom> myatom;

bool range(int x,int y){
    return (0<=x && x<=MAX && 0<=y && y<=MAX);
}
void simulation(int sec){
    
    for(int i=1;i<=n;i++)
        visited[myatom[i].y][myatom[i].x]=0;
    
    if(sec>=2000)
        return;
    
    for(int i=1;i<=n;i++){
        if(myatom[i].k!=0)
        {
            //이동
            myatom[i].x+=dx[myatom[i].dir];
            myatom[i].y+=dy[myatom[i].dir];
            //해당노드에 부딪힐게 없으면 노드에 노드인덱스 입력
            if(!range(myatom[i].x,myatom[i].y)){
                myatom[i].k=0;
                continue;
            }
            
            if(visited[myatom[i].y][myatom[i].x]==0)
                visited[myatom[i].y][myatom[i].x]=i;
            //부딪힐게 있으면 원래 있던 노드, 현재 노드 k sol에 더해주고 k=0으로 atom 죽이기
            else{
                sol+=myatom[i].k;
                sol+=myatom[visited[myatom[i].y][myatom[i].x]].k;
                myatom[i].k=0;
                myatom[visited[myatom[i].y][myatom[i].x]].k=0;
            }
        }
    }
    simulation(sec+1);
}
int main(){
    int tc;
    cin>>tc;
    
    for(int t=1;t<=tc;t++){
        sol=0;
        myatom.clear();
        cin>>n;
        myatom.push_back(atom(0,0,0,0));
        for(int i=0;i<n;i++){
            int x,y,dir,k;
            cin>>x>>y>>dir>>k;
            myatom.push_back(atom((x+1000)*2,(y+1000)*2,dir,k));
        }
        simulation(0);
        cout<<"#"<<t<<" "<<sol<<"\n";
    }
    
}

//Memory Limit Exceeded
