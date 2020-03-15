# Kruskal 알고리즘

**탐욕적인 방법(greedy method)**을 이용하여 네트워크(가중치를 간선에 할당한 그래프)의 모든 정점을 최소 비용으로 연결하는 최적 해답을 구하는 것이다.



- Greedy method
  - 결정을 해야 할 때마다 그 순간에 가장 좋다고 생각되는 것을 선택함으로써 최종적인 해답에 도달하는 것
  - 탐욕적인 방법은 그 순간에는 최적이지만, 전체적인 관점에서 최적이라는 보장이 없기 때문에 반드시 감증을 해야 한다.
  - 다행이 Kruskal 알고리즘은 최적의 해답을 주는 것으로 증명되어 있다.

- MST(최소 비용 신장 트리) 가 1) 최소 비용의 간선으로 구성됨 2) 사이클을 포함하지 않음 의 조건에 근거하여 각 단계에서 사이클을 이루지 않는 최소 비용 간선을 선택 한다.
  

### Kruskal 알고리즘의 동작

1. 그래프의 간선들을 가중치의 오름차순으로 정렬한다.
2. 정렬된 간선 리스트에서 순서대로 사이클을 형성하지 않는 간선을 선택한다.
   - 즉, 가장 낮은 가중치를 먼저 선택한다.
   - 사이클을 형성하는 간선을 제외한다.
3. 해당 간선을 현재의 MST(최소 비용 신장 트리)의 집합에 추가한다.



### Kruskal 알고리즘의 구체적인 동작

Kruskal 알고리즘을 이용하여 MST(최소 비용 신장 트리)를 만드는 과정

간선 선택을 기반 으로 하는 알고리즘
이전 단계에서 만들어진 신장 트리와는 상관없이 무조건 최소 간선만을 선택하는 방법

![img](https://gmlwjd9405.github.io/images/algorithm-mst/kruskal-example2.png)



***주의!***

- 다음 간선을 이미 선택된 간선들의 집합에 추가할 때 사이클을 생성하는지를 체크!

- - 새로운 간선이 이미 다른 경로에 의해 연결되어 있는 정점들을 연결할 때 사이클이 형성된다.
  - 즉, 추가할 새로운 간선의 양끝 정점이 같은 집합에 속해 있으면 사이클이 형성된다.
- 사이클 생성 여부를 확인하는 방법
  - 추가하고자 하는 간선의 양끝 정점이 같은 집합에 속해 있는지를 먼저 검사해야 한다.
  - ‘union-find 알고리즘’ 이용



### Kruskal 알고리즘의 시간 복잡도

- union-find 알고리즘을 이용하면 Kruskal 알고리즘의 시간 복잡도는 간선들을 정렬하는 시간에 좌우된다.
- 즉, 간선 e개를 퀵 정렬과 같은 효율적인 알고리즘으로 정렬한다면
  - Kruskal 알고리즘의 시간 복잡도는 O(elog₂e) 이 된다.

Prim의 알고리즘의 시간 복잡도는 O(n^2) 이므로

- 그래프 내에 적은 숫자의 간선만을 가지는 ‘희소 그래프(Sparse Graph)’의 경우 Kruskal 알고리즘이 적합하고
- 그래프에 간선이 많이 존재하는 ‘밀집 그래프(Dense Graph)’ 의 경우는 Prim 알고리즘이 적합하다.



### 코드

``` c++



#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//부모 노드를 가져옴
int getParent(int set[], int x){
    if(set[x]==x) return x;
    return getParent(set,set[x]);
}

//부모 노드를 병합
void unionParent(int set[],int a,int b){
  a=getParent(set, a);
  b=getParent(set, b);
  if(a<b) set[b] = a;
  else set[a] = b;
}
//같은 부모를 가지는지 확인
int find(int set[],int a,int b){
  a = getParent(set,a);
  b = getParent(set,b);
  if(a==b) return 1;
  else return 0;
}

class Edge{
public:
  int node[2];
  int distance;
  Edge(int a, int b, int distance){
    this->node[0]=a;
    this->node[1]=b;
    this->distance=distance;
  }
    bool operator <(const Edge &edge) const { // const를 모두 붙여줘야 된다. why?
    return this->distance < edge.distance;
  }
};


int main(void){
    int n = 7;
    int m = 11;
    
    vector<Edge> v;
    v.push_back(Edge(1,7,12));
    v.push_back(Edge(1,4,28));
    v.push_back(Edge(1,2,67));
    v.push_back(Edge(1,5,17));
    v.push_back(Edge(2,4,24));
    v.push_back(Edge(2,5,62));
    v.push_back(Edge(3,5,20));
    v.push_back(Edge(3,6,37));
    v.push_back(Edge(4,7,13));
    v.push_back(Edge(5,6,45));
    v.push_back(Edge(5,7,73));
    
    //간선의 비용으로 오름차순 정렬
    sort(v.begin(),v.end());
  
    //각 정점이 포함된 그래프가 어디인지 저장
    int set[n];
    for(int i=0;i<n;i++){
        set[i]=i;
    }
    
    //거리의 합을 0으로 초기화
    int sum=0;
    for(int i=0;i<v.size();i++){
        //동일한 부모를 가르키지 않는 경우, 즉 사이클이 발생하지 않을 때만 선택
        if(!find(set,v[i].node[0]-1,v[i].node[1]-1)){ //실제 node는 1부터, 저장노드는 0부터 시작
                    sum+=v[i].distance;
          unionParent(set,v[i].node[0]-1,v[i].node[1]-1);
        }
    }
  cout<<sum;
}

```



### 참고 자료

- https://gmlwjd9405.github.io/2018/08/29/algorithm-kruskal-mst.html

