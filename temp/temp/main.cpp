#include <iostream>
#include <vector>
using namespace std;

#define MAX 4100

class atom{
public:
    int x;
    int y;
    int k;
    int dir;
    
    atom(int x,int y,int k,int dir):x(x),y(y),k(k),dir(dir){};
};

int n;
int sol=0;

pair<int,int> dir[4]={{1,0},{-1,0},{0,-1},{0,1}};
vector <int> visited[MAX][MAX];
vector <atom> myatom;

void simulation(int sec){
    if(sec>1000)
        return;
    
    for(int i=1;i<=n;i++){
        
        myatom[i].x+=dir[myatom[i].dir].first;
        myatom[i].y+=dir[myatom[i].dir].second;
        visited[myatom[i].x][myatom[i].y].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if(visited[myatom[i].x][myatom[i].y].size()>1){
            for(int j=0;j<visited[myatom[i].x][myatom[i].y].size();j++){
                atom& temp=myatom[visited[myatom[i].x][myatom[i].y][j]];
                sol+=temp.k;
                temp.k=0;
            }
        }
        visited[myatom[i].x][myatom[i].y].clear();
    }
    simulation(sec+1);
}
int main(){
    int tc;
    cin>>tc;
    {
        for(int t=1;t<=tc;t++){
            cin>>n;
            myatom.push_back(atom(0,0,0,0));
            for(int i=0;i<n;i++){
                int x,y,dir,k;
                cin>>x>>y>>dir>>k;
                myatom.push_back(atom(y+2002,x+2002,k,dir));
            }
            simulation(0);
            cout<<sol;
        }
    }
}

//메모리리밋
