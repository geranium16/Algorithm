### #1. 목수의미로탈출

> ### 문제
>
> ------
>
> 아래와 같이 이동할 수 있는 길, 그리고 이동할 수 없는 벽으로 이루어진 크기 N x M 의 지도가 주어진다. 이 때, (N-1, 0) 에서 출발하여 (0, M-1) 까지 도착하는 최단거리를 찾으려 한다. 그런데 목수는 도끼 하나를 갖고 있으며, 이 도끼를 이용하여 벽을 깨부술 수 있다. 하지만 이 도끼는 내구성이 그렇게 좋지 않기 때문에, 벽을 최대 1개밖에 깰 수 없다. 목수가 출발점에서 도착점까지 이동하기 위한 최단거리를 출력하는 프로그램을 작성하시오. 물론, 벽은 최대 1개까지 깰 수 있다. 아래 예제의 경우 ‘X’ 로 표시된 벽을 깰 경우 거리 18만에 출발점에서 도착점으로 이동할 수 있다.
>
> ![img](https://k.kakaocdn.net/dn/bjBkzn/btqxpd8BCTf/LCCy1ChcwKn4oGv2wRCn00/img.png)
>
> 
>
>  
>
> ### 입력
>
> ------
>
> 첫째 줄에 지도의 세로 길이 N과 지도의 가로 길이 M이 주어진다. ( 1 ≤ N, M ≤ 1,000 ) 둘째 줄부터 지도의 정보가 주어진다. 0은 이동할 수 있는 부분, 1은 이동할 수 없는 부분을 나타낸다.
>
>  
>
> ### 출력
>
> ------
>
> 목수가 (N-1, 0) 에서 출발하여 (0, M-1) 까지 이동하는 데 필요한 최단거리를 출력한다. 목수는 미로를 항상 탈출할 수 있다고 가정한다.
>
>  
>
> ### 예제 입력
>
> 10 10
> 0 0 0 0 0 0 1 1 0 0
> 0 1 1 1 0 0 1 0 1 0 
> 0 1 1 1 0 0 1 0 1 0
> 0 0 0 0 0 0 0 0 1 0
> 0 0 1 1 1 1 0 0 1 0
> 0 0 0 0 0 0 1 1 0 0
> 0 0 1 1 1 0 1 1 0 0
> 0 0 1 1 1 0 0 0 0 0 
> 0 0 0 0 0 1 1 1 0 0
> 0 0 0 0 0 0 0 1 0 0
>
> ### 예제 출력
>
> 18
>
>  
>
> ### 예제 입력
>
> 10 10
> 0 0 0 0 0 0 1 1 0 0
> 0 1 1 1 0 0 1 1 1 0
> 0 1 1 1 0 0 1 1 1 0
> 0 0 0 0 0 0 0 1 1 0
> 0 0 1 1 1 1 0 1 1 0
> 0 0 0 0 0 0 1 1 0 0
> 0 0 1 1 1 0 1 1 0 0
> 0 0 1 1 1 0 0 1 0 0
> 0 0 0 0 0 1 1 1 1 1
> 0 0 0 0 0 0 0 1 0 0
>
> ### 예제 출력
>
> 22 

**소요시간:90분**

**알고리즘**

미로 찾기 문제에 벽을 한 번 부술 수 있는 조건이 생겼다. 벽을 한번만 부술 수 있기 때문에 이를 사용했는지 안했는지 체크를 해줘야한다. 따라서 탐색 중인 해당 노드가 가져야할 정보가 여러개라 point 라는 클래스를 만들었다.

고려해야할 사항

- 벽을 부수고 이동하다 막힌 경우, 이 경로를 나중에 벽을 부수지않은 경로가 만나면 체크가 되었기 때문에 경로가 끝난다. 따라서 벽을 부순 경우와 벽을 부수지않은 경우 체크를 다르게 줘야 한다.   
  1. item 사용 -> visited[]=2
  2. item 미사용 -> visited[] =1
- 이를 고려한 조건
  - 맵 내부에 노드가 있는지 확인
    - 벽이 없는 경우
      - 아이템을 안썼을 경우 
        - 방문한적 없는 경우(0), 아이템사용으로 방문했을 경우(2) ->큐 삽입
      - 아이템을 썻을 경우 
        - 방문한적 없는 경우(0)  ->큐 삽입
    - 벽이 있을 경우
      - 아이템을 안썼을 경우  ->큐 삽입

***핵심***

***if문을 코드를 줄이기 위해 합칠 필요없다. 처음에 모든 조건을 따로 따로 작성하고 나중에  합칠 수 있으면 합치자!!***

``` c++
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int MAX=1050;
int myGraph[MAX][MAX];
int visited[MAX][MAX];
int n,m;
int answer=150213501;
class point
{
public:
    int x;
    int y;
    int idx; //길이
    bool item; // 벽 뚫기 1회
    point(int x,int y,int idx,int item):x(x),y(y),idx(idx),item(item){}//생성자 사용
};

int confirm[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

bool inside(int x,int y)
{
    return (x>=0&&x<n)&&(y>=0&&y<m);
}
void BFS()
{
    queue<point> myQueue;
    point current(n-1,0,0,false);
    myQueue.push(current);
    visited[n-1][0]=1;
    
    while(!myQueue.empty())
    {
        current=myQueue.front();
        myQueue.pop();
        
        if(current.x==0&&current.y==m-1&&answer>current.idx)
            answer=current.idx;
        
        for(int i=0;i<4;i++)
        {
            //길이와 아이템 사용여부 이어받을 수 있다.
            point next(current.x+confirm[i][0],current.y+confirm[i][1],current.idx+1,current.item);
            if(inside(next.x,next.y)) //행렬 내부 조건
            {
                if(myGraph[next.x][next.y]==0) // 벽x
                {
                    if(!next.item && visited[next.x][next.y]!=1) //벽뚫기 사용x -> 1만 아니면 다감, 2로 체크된 노드도 1로 덮어써도 된다. 어차피 벽뚫기 사용한 경우는 1이던 2이던 체크만 되어있으면 못감
                    {
                        visited[next.x][next.y]=1;
                        myQueue.push(next);
                    }
                    
                    else if(next.item && visited[next.x][next.y]==0) //벽뚫기 사용 ㅇ -> 1도 못감 이유: 전 노드를 들갈 수도 있따.
                    {
                        visited[next.x][next.y]=2;
                        myQueue.push(next);
                    }
                }
                else if(next.item==false) //벽o 벽뚫기 사용x일 시 벽뚫기 사용 &&  방문체크 2
                {
                    next.item=true;
                    visited[next.x][next.y]=2;
                    myQueue.push(next);
                }
            }
        }
        
    }
    
}
int main() {
    
    //Please Enter Your Code Here
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cin>>myGraph[i][j];
    }
    
    BFS();
    
    cout<<answer;
    return 0;
}

```

