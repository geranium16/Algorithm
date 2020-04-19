#include <iostream>
#include <queue>
using namespace std;
const int MAX = 52;
int n,m,t;
int mymap[MAX][MAX];
int x[MAX],d[MAX],k[MAX];
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
int sum=0,num=0;

void BFS(){
    //인접
    bool visited[MAX][MAX]={false,};
    bool flag=false;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mymap[i][j]==0)
                continue;
            bool flag2=false;
            queue <pair<int,int>> q;
            q.push({i,j});
            int val=mymap[i][j];
            visited[i][j]=true;
            while(!q.empty()){
                pair<int,int> current = q.front();
                q.pop();
                for(int k=0;k<4;k++){
                    pair<int,int> next= {current.first+dx[k],current.second+dy[k]};
                    if(next.first<1 || next.first>n)
                        continue;
                    else if(next.second<1)
                        next.second=m;
                    else if(next.second>m)
                        next.second=1;
                    if(!visited[next.first][next.second] && mymap[next.first][next.second]==val){
                        if(!flag2){
                            sum-=mymap[current.first][current.second];
                            num--;
                            mymap[current.first][current.second]=0;
                            flag2=true;
                        }
                        flag=true;
                        sum-=mymap[next.first][next.second];
                        num--;
                        mymap[next.first][next.second]=0;
                        visited[next.first][next.second]=true;
                        q.push(next);
                        
                    }
                }
            }
        }
    }
    
    if(!flag){
        double avg=double(sum)/num;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mymap[i][j]==0)
                    continue;
                if(mymap[i][j]>avg){
                    sum--;
                    mymap[i][j]--;
                    
                }
                else if(mymap[i][j]<avg){
                    sum++;
                    mymap[i][j]++;
                }
            }
        }
    }
    
}

void rotation(int cnt){
    for(int i=x[cnt];i<=n;i+=x[cnt]){
        int temp[MAX];
        for(int j=1;j<=m;j++)
            temp[j]=mymap[i][j];
        for(int j=1;j<=m;j++){
            int col=(j+k[cnt])%(m+1);
            if(col<j)
                col++;
            if(d[cnt]==0)
                mymap[i][col]=temp[j]; //시계 회전
            else
                mymap[i][j]=temp[col];
        }
    }
}

void simulation(int cnt){
    
    if(cnt>=t||sum==0)
        return;
    rotation(cnt);
    BFS();
    simulation(cnt+1);
}

int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mymap[i][j];
            sum+=mymap[i][j];
            num++;
        }
    }
    for(int i=0;i<t;i++)
        cin>>x[i]>>d[i]>>k[i];
    simulation(0);
    cout<<sum;
}

