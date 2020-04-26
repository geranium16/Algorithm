#include  <iostream>
using namespace std;
const int MAX= 12;
const int MAX2 = 304;
// i번 세로선의 결과가 i번이 나오도록 사다리 게임을 조작하려면, 추가해야하는 가로선 개수의 최소값
// 정답이 3보다 크면 -1출력

int m,n,h;
bool mymap[MAX2][MAX];
int y_init;
bool flag=false;
int solution=-1;

bool DFS(int x,int y,int x_temp,int y_temp){
    if(x>h){
        return y==y_init ? true : false;
    }
    if(mymap[x][y] && y_temp!=y+1)
        return DFS(x,y+1,x,y);
    else if(y>1 && mymap[x][y-1] && y_temp!=y-1)
        return DFS(x,y-1,x,y);
    else
        return DFS(x+1,y,x,y);
}

bool situation(){
    for(int i=1;i<=n;i++){
        y_init=i;
        if(!DFS(1,i,0,0))
            return false;
    }
    return true;
}

void combination(int idx,int cnt,int x,int y){
    if(idx<=cnt){
        if(situation()){
            flag=true;
        }
        return;
    }
    if(y>=n){
        x++;
        y=1;
    }
    if(x>h)
        return;
    
    for(int i=x;i<=h;i++){
        for(int j=y;j<n;j++){
            if(mymap[i][j])
                continue;
            mymap[i][j]=true;
            combination(idx,cnt+1,x,y+1);
            mymap[i][j]=false;
            if(flag)
                return;
        }
    }
}
int main(){
    cin>>n>>m>>h;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        mymap[a][b]=true;
    }
    for(int i=0;i<=3;i++){
        combination(i,0,1,1);
        if(flag){
            solution=i;
            break;
        }
    }
    cout<<solution;
}
