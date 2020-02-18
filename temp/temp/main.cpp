#include <iostream>
using namespace std;
#define MAX 22

int k;
bool magnetic[4][8];
int dir[4]={0,};
bool visited[4]={false,};
pair<int,int> inform[MAX]; // 자석번호 방향

bool range(int x){
    return 0<=x && x<4;
}
void decide(pair<int,int> v){
    dir[v.first]=v.second;
    visited[v.first]=true;
    if(!visited[v.first-1]&&range(v.first-1)){
        if(magnetic[v.first-1][2]!=magnetic[v.first][6])
            decide({v.first-1,-v.second});
    }
    if(!visited[v.first+1]&&range(v.first+1)){
        if(magnetic[v.first][2]!=magnetic[v.first+1][6])
            decide({v.first+1,-v.second});
    }
}

void action(){
    for(int i=0;i<4;i++){
        if(dir[i]==1){
            int s=magnetic[i][7];
            for(int j=7;j>0;j--)
                magnetic[i][j]=magnetic[i][j-1];
            magnetic[i][0]=s;
            
        }
        else if(dir[i]==-1){
            int s=magnetic[i][0];
            for(int j=0;j<7;j++)
                magnetic[i][j]=magnetic[i][j+1];
            magnetic[i][7]=s;
        }
    }
}
void DFS(int idx){
    if(idx>=k)
        return;
    
    fill_n(dir,4,0);
    fill_n(visited,4,false);
    decide(inform[idx]);
    action();
    DFS(idx+1);
}
int getresult(){
    int ans = 0;
    for (int i = 0; i < 4; i++)
        if (magnetic[i][0] == 1) ans += (1 << i); //1의 비트 값을 왼쪽으로 i번 이동
    return ans;
}
int main(){
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        cin>>k;
        for(int i=0;i<4;i++){
            for(int j=0;j<8;j++)
                cin>>magnetic[i][j];
        }
        for(int i=0;i<k;i++){
            cin>>inform[i].first>>inform[i].second;
            inform[i].first--;
        }
        DFS(0);
        cout<<"#"<<t<<" "<<getresult()<<"\n";
    }
}

