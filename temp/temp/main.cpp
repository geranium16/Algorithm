#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX=17;

int n,w,h;
int mymap[MAX][MAX]={0,};
int col_top[MAX]={0,};
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
int sol=987987987;
bool range(int x,int y){
    return 0<=x && x<h && 0<=y && y<w;
}
void remove_stone(int row,int col){
    int cnt=mymap[row][col]-1;
    mymap[row][col]=0;
    for(int i=0;i<4;i++){
        int temp_x=row; int temp_y=col;
        for(int j=0;j<cnt;j++){
            temp_x+=dx[i]; temp_y+=dy[i];
            
            if(!range(temp_x,temp_y)) break;
            if(mymap[temp_x][temp_y]>1) remove_stone(temp_x,temp_y);
            else if(mymap[temp_x][temp_y]==1) mymap[temp_x][temp_y]=0;
        }
    }
}

void move_stone(){
    for(int j=0;j<w;j++){
        queue <int> q;
        bool flag=false;
        for(int i=h-1;i>=0;i--){
            if(mymap[i][j]!=0){
                flag=true;
                q.push(mymap[i][j]);
            }
        }
        if(!flag) {
            col_top[j]=-1;
            continue;
        }
        for(int i=h-1;i>=0;i--){
            if(!q.empty()){
                col_top[j]=i;
                mymap[i][j]=q.front();
                q.pop();
            }
            else mymap[i][j]=0;
        }
    }
}

void init(){
    fill(col_top,col_top+MAX,-1);
    fill(&mymap[0][0],&mymap[0][0]+MAX*MAX,0);
    sol=987987987;
}

void simulation(int cnt){
    if(cnt>=n){
        int ans=0;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++)
                if(mymap[i][j]>0) ans++;
        }
        sol = sol < ans ? sol : ans;
        return;
    }
    for(int i=0;i<w;i++){
        if(col_top[i]==-1) {
            simulation(cnt+1);
            continue;
        }
        int copy_map[MAX][MAX]={0,};
        int copy_col_top[MAX]={0,};
        copy(&mymap[0][0],&mymap[0][0]+MAX*MAX,&copy_map[0][0]);
        copy(col_top,col_top+MAX,copy_col_top);
        remove_stone(col_top[i],i);
        move_stone();
        simulation(cnt+1);
        copy(&copy_map[0][0],&copy_map[0][0]+MAX*MAX,&mymap[0][0]);
        copy(copy_col_top,copy_col_top+MAX,col_top);
    }
}

int main(){
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        init();
        cin>>n>>w>>h;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                cin>>mymap[i][j];
                if(mymap[i][j]>0 && col_top[j]==-1)
                    col_top[j]=i;
            }
        }
        
        simulation(0);
        
        cout<<"#"<<t<<" "<<sol<<"\n";
    }
}
