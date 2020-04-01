#include <iostream>
#include <cstring>
using namespace std;
const int MAX=22;

int n; //1<=n<=20
int mymap[MAX][MAX]={0,};
bool summary[MAX][MAX]={0,};
int solution=0;

void rotation(){
    int temp[MAX][MAX];
    memcpy(temp,mymap,sizeof(temp));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            mymap[j][n-1-i]=temp[i][j];
    }
}

void move(){
    for(int j=0;j<n;j++){
        for(int i=0;i<n;i++){
            if(mymap[i][j]!=0){
                for(int k=i-1;k>=0;k--){
                    if(mymap[k][j]!=0){
                        if(mymap[k][j]==mymap[i][j] &&!summary[k][j]){
                            mymap[k][j]*=2;
                            mymap[i][j]=0;
                            summary[k][j]=true;
                            if(solution<mymap[k][j])
                                solution=mymap[k][j];
                        }
                        else if(k+1!=i){
                            mymap[k+1][j]=mymap[i][j];
                            mymap[i][j]=0;
                        }
                        break;
                    }
                    else if(k==0){
                        mymap[k][j]=mymap[i][j];
                        mymap[i][j]=0;
                    }
                }
            }
        }
    }
}
void DFS(int cnt){
    
    if(cnt>=5)
        return;
    
    int copy_map[MAX][MAX];
    for(int dir=0;dir<4;dir++){
        memcpy(copy_map,mymap,sizeof(copy_map));
        memset(summary,0,sizeof(summary));
        move();
        DFS(cnt+1);
        memcpy(mymap,copy_map,sizeof(mymap));
        rotation();
    }
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>mymap[i][j];
            if(solution<mymap[i][j])
                solution=mymap[i][j];
        }
    }
    DFS(0);
    cout<<solution;
}
