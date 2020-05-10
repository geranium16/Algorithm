
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAX = 52;

int r,c,t;
int mymap[MAX][MAX];
int solution=0;
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
pair<int,int> merchine[2];

bool range(int x,int y){
    return 0<=x && x<r && 0<=y && y<c;
}

void diffusion(){
    int temp[MAX][MAX]={0,};
    temp[merchine[0].first][merchine[0].second]=-1;
    temp[merchine[1].first][merchine[1].second]=-1;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(mymap[i][j]>0){
                int numofdiff=0;
                for(int k=0;k<4;k++){
                    pair <int,int> next={i+dx[k],j+dy[k]};
                    if(range(next.first,next.second) && mymap[next.first][next.second]>=0){
                        temp[next.first][next.second]+=mymap[i][j]/5;
                        numofdiff++;
                    }
                }
                temp[i][j] += mymap[i][j]-mymap[i][j]/5*numofdiff; //A-(A/5)*확산 수
            }
        }
    }
    memcpy(mymap,temp,sizeof(mymap));
}
void cleaning(){
    solution-=mymap[merchine[0].first-1][0];
    for(int i=merchine[0].first-1;i>0;i--)
        mymap[i][0]=mymap[i-1][0];
    for(int i=0;i<c-1;i++)
        mymap[0][i]=mymap[0][i+1];
    for(int i=0;i<merchine[0].first;i++)
        mymap[i][c-1]=mymap[i+1][c-1];
    for(int i=c-1;i>1;i--)
        mymap[merchine[0].first][i]=mymap[merchine[0].first][i-1];
    mymap[merchine[0].first][merchine[0].second+1]=0;

    solution-=mymap[merchine[1].first+1][0];
    for(int i=merchine[1].first+1;i<r-1;i++)
        mymap[i][0]=mymap[i+1][0];
    for(int i=0;i<c-1;i++)
        mymap[r-1][i]=mymap[r-1][i+1];
    for(int i=r-1;i>merchine[1].first;i--)
        mymap[i][c-1]=mymap[i-1][c-1];
    for(int i=c-1;i>1;i--)
        mymap[merchine[1].first][i]=mymap[merchine[1].first][i-1];
    mymap[merchine[1].first][merchine[1].second+1]=0;
}

void simulation(int cnt){
    if(cnt>=t)
        return;
    diffusion();
    cleaning();
    simulation(cnt+1);
}

int main(){
    cin>>r>>c>>t;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>mymap[i][j];
            if(mymap[i][j]>0)
                solution+=mymap[i][j];
            else if(mymap[i][j]==-1 && mymap[i-1][j]==-1){
                merchine[0]={i-1,j};
                merchine[1]={i,j};
            }
        }
    }
    simulation(0);
    cout<<solution;
}
