### #1. 목수의미로탈출

> 



``` c++

/*
 -출발점: (n-1,0) 도착점: (0,m-1)
 -도끼로 벽을 한번 꺨 수 있다.
 -일반적인 BFS로 짤경우 먼저 도끼를 이용해서 벽을깬 경우 도끼를 이용하지않고 더 느린 루트들을 다 먹어버린다.
 -따라서 한 방문한 노드를 판별할 떄 방문x,벽사용x방문,벽사용o방문 이 세가지로 나눠야한다.
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX=1005;

int n,m;
int mymap[MAX][MAX];
int visited[MAX][MAX];
int visited2[MAX][MAX];

pair<int,int> dir[4]={{-1,0},{0,1},{1,0},{0,-1}};

bool range(pair<int,int> node){
    return (0<=node.first && node.first<n && 0<=node.second && node.second<m );
}

bool inspect(pair<int,int> node){
    return node.first==0 && node.second==m-1;
}

void BFS(pair<int,int> start){
  
    queue <pair<pair<int,int>,bool>> q;
    q.push({{start.first,start.second},false});
    visited[start.first][start.second]=1;
    visited2[start.first][start.second]=1;
    
    while(!q.empty()){
        pair<pair<int,int>,bool> current=q.front();
        q.pop();
        for(int j=0;j<4;j++){
            pair<pair<int,int>,bool> next={{current.first.first+dir[j].first,current.first.second+dir[j].second},current.second};
           
           
            if(range(next.first)){ //맵안에 들어오는 경우
                if(!mymap[next.first.first][next.first.second]){ // 벽이 없을 경우
                    if(visited[next.first.first][next.first.second]==0){   //맵1 방문 안했을 경우
                        if(!next.second){    //아이템X 경우 = 아이템을 안썻을 경우에만 맵1,맵2 방문
                            visited[next.first.first][next.first.second]=visited[current.first.first][current.first.second]+1;
                            visited2[next.first.first][next.first.second]=visited2[current.first.first][current.first.second]+1;
                            q.push(next);
                          
                            if(inspect(next.first))
                                return;
                            
                        }
                        //아이템O 경우 && 맵2 방문X인 경우 맵2만 방문
                        else if(visited2[next.first.first][next.first.second]==0){
                            visited2[next.first.first][next.first.second]=visited2[current.first.first][current.first.second]+1;
                            q.push(next);
                            
                        		if(inspect(next.first))
                                return;
                        }
                    }
                }
                //벽이 있을 경우 && 아이템 안썻을 경우
                else if(!next.second && visited2[next.first.first][next.first.second]==0){
                    next.second=true;
                    visited2[next.first.first][next.first.second]=visited2[current.first.first][current.first.second]+1;
                    q.push(next);
                    if(inspect(next.first))
                        return;
                }
            }
        }
    }
    
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mymap[i][j];
        }
    }
    BFS({n-1,0});
    if(visited[0][m-1]!=0)
        cout<<visited[0][m-1]-1;
    else
        cout<<visited2[0][m-1]-1;
}
```

