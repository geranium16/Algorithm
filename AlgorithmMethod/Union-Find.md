# Union-Find 알고리즘

> 두 정점을 하나의 그룹으로 묶어라
>
> 두 정점이 같은 그룹에 속하는가?

 **Union-Find(유니온-파인드)**는 대표적인 그래프 알고리즘이다. 바로 '합집합 찾기'라는 의미를 가진 알고리즘이다. 여기서 합집합은 **Disjoint Set**이라는 자료구조로 부른다. <u>서로 중복되지 않는 부분 집합들로 나눠진 원소들에 대한 정보를 저장하고 조작하는 자료구조이다.</u>  따라서 Union-Find 알고리즘을 **Disjoint-Set(서로소 집합)** 알고리즘이라고도 부르고 Disjoint Set을 표현할 때 사용하는 알고리즘이다. <u>구체적으로 여러개의 노드가 존재할 때 두 개의 노드를 선택해서 현재 이 노드가 서로 같은 그래프에 속하는지 판별하는 알고리즘이다.</u>

- **Union-Find 알고리즘** = **Disjoint-set 알고리즘** = 여러개의 노드가 존재할 때 두 개의 노드를 선택해서 현재 이 노드가 서로 같은 그래프에 속하는지 판별하는 알고리즘이다.
- **Disjoint Set** = 서로 중복되지 않는 부분 집합들로 나눠진 원소들에 대한 정보를 저장하고 조작하는 자료구조이다.



<img src="/Users/DaeHyeon/Library/Application Support/typora-user-images/스크린샷 2020-03-15 오후 4.04.39.png" alt="스크린샷 2020-03-15 오후 4.04.39" style="zoom: 33%;" />

 위와 같이 여러 개의 노드가 서로 자유분방하게 존재한다고 생각해보자. 이와 같이 모두 연결되지 않고 각자 자기 자신만을 집합의 원소로 가지고 있을 때를 다음과 같이 표현할 수 있다. <u>모든 값이 자기 자신을 가르키도록 만드는 것이다.</u>



### Union-Find의 연산

- make-set(x)
  1. 초기화
  2. x를 유일한 원소로 하는 새로운 집합을 만든다.
- union(x,y)
  1. 합하기
  2. x가 속한 집합과 y가 속한 집합을 합친다. 즉, x와 y가 속한 두 집합을 합치는 연산
- find(x)
  1. 찾기
  2. x가 속한 집합의 대료값을 반환한다. 즉, x가 어떤 집합에 속해 있는지 찾는 연산



#### Union-Find의 과정과 사용 예시
#### Union-Find의 과정

<img src="https://gmlwjd9405.github.io/images/algorithm-union-find/union-find-example.png" alt="img" style="zoom:50%;" />



``` c++
#include <iostream>

int getParent(int parent[],int x){
  if(parent[x] == x) return x; // 루트 노드는 부모 노드 번호로 자기 자신을 가진다.
  return parent[x] = getParent(parent, parent[x]); //루트노드로 거슬러 올라간다.
}
int find(int parent[],int a,int b){
 	a=getParent(parent,a);
  b=getParent(parent,b);
 	if(a==b) return 1;
  else return;
}

void union(int parent[],int a,int b){
  //각 원소가 속한 트리의 루트 노드를 찾는다.
  a=getParent(parent,a);
  b=getParent(parent,b);
  if(a<b) parent[b]=a;
  else parent[a]=b;
}

int main(void){
  int parent[11];
  for(int i=1 ; i<=10 ;i++)
    parent[i]=i;
  union(parent, 1, 2);
  union(parent, 2, 3);
  union(parent, 3, 4);
  union(parent, 5, 6);
  union(parent, 6, 7);
  union(parent, 7, 8);
  cout<<"1과 5가 연결되어 있나요?\n"<<findParent(parent, 1,5); // 0
  union(parent,1,5);
  cout<<"1과 5가 연결되어 있나요?\n"<<findParent(parent, 1,5); // 1
}
```

***일반적으로 숫자가 작은 노드를 루트 노드로 합친다.***

노드와 노드가 연결되었는지는 루트 노드를 통해 알 수 있다. 루트 노드가 같으면 같은 그래프이고 다르면 다른 다른 그래프이다.



### 루트 노드에 합치는 이유

#### 최악의 상황

<img src="https://gmlwjd9405.github.io/images/algorithm-union-find/worst-case.png" alt="img" style="zoom:50%;" />

루트 노드로 합치지 않고 그냥 현재 노드에 합치는 경우 위와 같은 최악의 경우가 발생한다.

- 트리 구조가 완전 비대칭인 경우
- 트리의 높이가 매우 커진다.
- 원소의 개수가 N일 때, 트리의 높이가 N-1이므로 union과 find(x)의 시간 복잡도가 모두 O(N)이 된다. 



#### find 연산 최적화

<img src="https://gmlwjd9405.github.io/images/algorithm-union-find/path-compression.png" alt="img" style="zoom:48%;" />



### Union-Find의 사용 예시

- Kruskal MST 알고리즘에서 새로 추가할 간선의 양끝 정점이 같은 집합에 속해 있는지(사이클 형성 여부 확인)에 대해 검사하는 경우
- 초기에 {0}, {1}, {2}, … {n} 이 각각 n+1개의 집합을 이루고 있다. 여기에 합집합 연산과, 두 원소가 같은 집합에 포함되어 있는지를 확인하는 연산을 수행하려는 경우

- 어떤 사이트의 친구 관계가 생긴 순서대로 주어졌을 때, 가입한 두 사람의 친구 네트워크에 몇 명이 있는지 구하는 프로그램을 작성하는 경우



### 관련 자료

- https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html
- https://m.blog.naver.com/ndb796/221230967614