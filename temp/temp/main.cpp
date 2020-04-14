#include <iostream>
using namespace std;
const int MAX=22;
const int MAX2=1002;
int n,m,x,y,k;
int mymap[MAX][MAX];
int comm[MAX2];
int dice_dir[7]={0,1,2,3,4,5,6}; //처음 윗면:1 동쪾:3 북쪽:5 서쪽:4 남쪽:2 아랫면:6
int dice_num[7]={0,};
int dx[5]={0,0,0,-1,1};
int dy[5]={0,1,-1,0,0};

//동쪽이동: 1->4, 3->1, 6->3 4->6
//서쪽이동: 1->3, 3->6, 6->4, 4->1
//남쪽이동: 1->5, 2->1, 6->2, 5->6
//북쪽이동: 1->2, 5->1, 6->5, 2->6
bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<m;
}
void simulation(int cnt){
    if(cnt>=k)
        return;
    if(range(x+dx[comm[cnt]],y+dy[comm[cnt]])){
        x+=dx[comm[cnt]];
        y+=dy[comm[cnt]];
        if(comm[cnt]==1){ //동쪽 1->4, 3->1, 6->3 4->6
            int temp=dice_dir[1];
            dice_dir[1]=dice_dir[4]; dice_dir[4]=dice_dir[6]; dice_dir[6]=dice_dir[3]; dice_dir[3]=temp;
        }
        else if(comm[cnt]==2){
            int temp=dice_dir[1];
            dice_dir[1]=dice_dir[3]; dice_dir[3]=dice_dir[6]; dice_dir[6]=dice_dir[4]; dice_dir[4]=temp;
        }
        else if(comm[cnt]==3){
            int temp=dice_dir[1];
            dice_dir[1]=dice_dir[5]; dice_dir[5]=dice_dir[6]; dice_dir[6]=dice_dir[2];  dice_dir[2]=temp;
        }
        else if(comm[cnt]==4){
            int temp = dice_dir[1];
            dice_dir[1]=dice_dir[2]; dice_dir[2]=dice_dir[6]; dice_dir[6]=dice_dir[5]; dice_dir[5]=temp;
        }
        if(mymap[x][y]==0)
            mymap[x][y]=dice_num[dice_dir[6]];
        else{
            dice_num[dice_dir[6]]=mymap[x][y];
            mymap[x][y]=0;
        }
        cout<<dice_num[dice_dir[1]]<<"\n";
    }
    simulation(cnt+1);
}

int main(){
    cin>>n>>m>>x>>y>>k;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cin>>mymap[i][j];
    }
    for(int i=0;i<k;i++)
        cin>>comm[i];
    simulation(0);
}
