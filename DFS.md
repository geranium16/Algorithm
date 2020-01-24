



### #1. 2색칠하기

``` c++

//DFS
//2가지 색 : 1,2
//현재 위치가 1인데 다음노드가 1로 되어있으면 불가능,현재 위치가 2인데 다음노드가 2로 되어있으면 불가능
//다음노드(0)인게 없으면 종료
//즉,
//현재 노드 = 1
////1. 다음 노드가 0이면 들어가고 1
////2. 다음 노드가 1이면 FALSE 반환 끝
////3. 다음 노드가 2이면 건너띄기

//

#include <iostream>
#include <vector>
using namespace std;
const int MAX=10005;

int n,m;
vector<int> mygraph[MAX];
int visited[MAX];
bool flag=false; // false이면 가능 true이면 불가능
void DFS(int current){
    
    for(int i=0;i<mygraph[current].size();i++){
        int next=mygraph[current][i];
        
        if(visited[next]==0){
            visited[next]=visited[current]%2+1; // 현재가 1이면 next는 2, 현재가 2이면 next=1
            DFS(next);
        }
        else if(visited[current]==visited[next]){
            flag=true;
            return;
        }
            
    }
}
int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        mygraph[a].push_back(b);
        mygraph[b].push_back(a);
    }
    
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            visited[i]=1;
            DFS(i);
            if(flag){
                cout<<"NO";
                return 0;

            }
        }
    }
    
    cout<<"YES";
   
}

```



### #2. 이분그래프



> [백준:1707번]: https://www.acmicpc.net/problem/1707
>
> ## 문제
>
> 그래프의 정점의 집합을 둘로 분할하여, 각 집합에 속한 정점끼리는 서로 인접하지 않도록 분할할 수 있을 때, 그러한 그래프를 특별히 이분 그래프 (Bipartite Graph) 라 부른다.
>
> 그래프가 입력으로 주어졌을 때, 이 그래프가 이분 그래프인지 아닌지 판별하는 프로그램을 작성하시오.
>
> ## 입력
>
> 입력은 여러 개의 테스트 케이스로 구성되어 있는데, 첫째 줄에 테스트 케이스의 개수 K(2≤K≤5)가 주어진다. 각 테스트 케이스의 첫째 줄에는 그래프의 정점의 개수 V(1≤V≤20,000)와 간선의 개수 E(1≤E≤200,000)가 빈 칸을 사이에 두고 순서대로 주어진다. 각 정점에는 1부터 V까지 차례로 번호가 붙어 있다. 이어서 둘째 줄부터 E개의 줄에 걸쳐 간선에 대한 정보가 주어지는데, 각 줄에 인접한 두 정점의 번호가 빈 칸을 사이에 두고 주어진다.
>
> ## 출력
>
> K개의 줄에 걸쳐 입력으로 주어진 그래프가 이분 그래프이면 YES, 아니면 NO를 순서대로 출력한다.
>
> ## 예제 입력 1 복사
>
> ```
> 2
> 3 2
> 1 3
> 2 3
> 4 4
> 1 2
> 2 3
> 3 4
> 4 2
> ```
>
> ## 예제 출력 1
>
> ```
> YES
> NO
> ```

**소요시간:20분**

**알고리즘:**

문제를 해석하면 인접하는 정점끼리 같은 집합이 될 수 없을 때 전체 그래프가 두 집합으로 나타낼 수 있는지를 판별하는 것이다. 즉 두 집합을 1팀,2팀라고 가정했을 때 인접하는 정점끼리 1팀,1팀 또는 2팀,2팀인 같은 팀이 나올 수 없고 무조건 다른 팀이여야한다. 따라서 각 노드의 팀을 나타내는 visited 배열을 이용하고 DFS를 통해 각 노드에 팀을 부여해줄 것이다.

1. 인접노드가 visited가 0일 때 (방문X) : current%2+1 값을 넣어주어 현재노드와 다른 팀을 부여해주었다. current가 1일 때 2가 출력되며 current가 0일 때 1이 출력된다.  이 규칙으로 탐색을하며 각 노드에 팀을 부여한다.
2. 만약 인접노드가 방문된 경우 중 현재노드와 같은 팀일 경우 : 이는 문제의 규칙에 어긋난다. 이 같은 경우 무조건 이분 그래프가 될 수 없으므로 모든 걸 멈추고 "NO"출력
3. 2번 규칙에 해당하는 경우가 발생하지 않고 모든 노드에 팀을 부여했으면 이는 1팀 2팀으로 규칙에 맞게 팀 배분이 완성 따라서 "YES" 출력

***Skills***

***visited[next]=visited[current]%2+1를 통해 if,else를 이용해 팀을 부여하는 4줄짜리 코드길이를 줄일 수 있다.*** 

***fill_n(visited,MAX,0); :fill_n(시작주소,중료주소,변경값)***
***for(int i=1;i<=n;i++) mygraph[i].clear();: vector 초기화 **

***

```` c++
#include <iostream>
#include <vector>
using namespace std;

const int MAX=20005;
int k,n,m;
vector <int> mygraph[MAX];
int visited[MAX];
bool flag;


void DFS(int current){
    for(int i=0;i<mygraph[current].size();i++){
        int next=mygraph[current][i];
        if(visited[next]==0){
            visited[next]=visited[current]%2+1;
            DFS(next);
        }
        else if(visited[next]==visited[current])
            flag=true;
        if(flag)
            return;
    }
    
}
int main(){
    
    cin>>k;
    
    for(int j=0;j<k;j++){

        flag=false;
        fill_n(visited,MAX,0);
        for(int i=1;i<=n;i++) //vector초기화
            mygraph[i].clear();
        
        cin>>n>>m;
        
        for(int i=0;i<m;i++){
            int a,b;
            cin>>a>>b;
            mygraph[a].push_back(b);
            mygraph[b].push_back(a);
        }
        for(int i=1;i<=n;i++){
            if(visited[i]==0){
                visited[i]=1;
                DFS(i);
                if(flag){
                    cout<<"NO\n";
                    break;
                }
            }
        }
        if(!flag)
            cout<<"YES\n";
    }
}
````



