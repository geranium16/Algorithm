# Brute Force

> : 모든 경우를 시도해서 문제의 해를 찾는다.
>
> **Backtracking**
>
> : 노드의 유망성을 따져서 가능한 경우만 확인하며 해를 찾는다. 문제가 한정 조건을 가진 경우 한정 조건 내 모든 조합을 시도해서 문제의 해를 찾는다



### Basic BruteForce

``` c++
//입력: 10 3 8 4 2 1  
int mymin=a[0];

for(int i=1;i<n;i++){
 if(myMin>a[i])
	mymin=a[i];
}
```

### N중 for문을 돌려야할 경우(**자주 활용)

: 재귀함수 이용 -> 똑같이 N중 for문을 돌리지만 깔끔하고 간단한 코드로 구현 가능

``` c++


n개의 카드가 있고 각각은 1~N까지의 번호를 갖는다.

n개의 카드를 한 줄로 세울 수 있는 모든 경우의 수를 구하라.

int n=3;

doRecursion(int x) x번째 for문을 실행{
	if(x>n)
  	print Number;
	else{
		for(int i=1;i<=n;i++){
      if(아직 순자 i가 없었다면){
        x번째 for문에서 숫자 i를 등록하고
        dorecursion(x+1);
			}
		}
  }
```

---



### #1.순열구하기

> 문제: 서로 다른 n개의 원소들 중에서 r개만을 뽑아 일렬로 나열하는 것을 순열이라 한다. 예를 들어, 3개의 원소 a, b, c 중에서 2개만을 뽑아 나열하면 ab, ac, ba, bc, ca, cb 의 6가지 경우가 있다. n과 r이 주어질 때, n개의 소문자 중에서 r개만을 뽑아 나열하는 모든 경우를 출력하는 프로그램을 작성하시오. 단, a부터 시작하여 연속으로 n개의 알파벳을 갖고 있다고 하자.
>
> 입력: 첫 번째 줄에 n과 r이 주어진다. ( 1 ≤ n ≤ 10, 0 ≤ r ≤ min(n, 7) )
>
> 출력: 각 줄에 n개의 소문자 중에서 r개만을 뽑아 나열하는 경우를 사전순으로 나열한 결과를 출력한다.

**알고리즘:** 

- 재귀함수 이용 ***재귀함수 호출 전, 호출 후 초기화 중요 or Recursive(idx+1) 활용***

- flag[0]='a' flag[1]='b' ....를 이용
- Recursive : for(i<r) : flag[i]가 false(사용하지 않았으면) data[idx]='a'+i 
- 종료조건 idx>=r
- 시간복잡도: O(n*r)

``` C++
#include <iostream>
using namespace std;
int n,r;
bool flag[12];
char data[12];
void Recursive(int idx){
    if(idx>=r){
        for(int i=0;i<r;i++)
            cout<<data[i];
        cout<<"\n";
        return;
    }
    for(int i=0;i<n;i++){
        if(!flag[i]){
            data[idx]='a'+i;
            flag[i]=true;
            Recursive(idx+1);
            flag[i]=false;
            
        }
    
    }
    
}
int main()
{

    cin>>n>>r;
    Recursive(0);
}
```



### #2.tobbin

> 문제: 두 정수 n, k를 입력받아 k개의 1을 가진 n자리 이진 패턴을 출력하는 프로그램을 작성하세요.
>
> 입력: 두 정수 n, k가 입력으로 주어진다. ( 0 < n <= 30, 0 <= k < 8 , n >= k )
>
> 출력: 결과를 내림차순으로 출력한다.
>
> 예제 입력
> 2 1
> 예제 출력
> 10
> 01
>
> 예제 입력
> 2 0
> 예제 출력
> 00
>
> 예제 입력
> 4 2
> 예제 출력
> 1100
> 1010
> 1001
> 0110
> 0101
> 0011

**알고리즘:** 

- 재귀함수 이용
- 내림차순 : i-- 로 for문 설계
- Recursive(idx) : 1~0을 data[idx]에 저장
- 종료조건 : idx>=n, data[i]를 for문을 통해 1의 갯수가 k보다 적으면 출력
- 시간복잡도: O(n)

``` c++
#include <iostream>
using namespace std;
int n,k;
int data[35];

void Recursive(int idx,int count){
    if(idx>=n){
        if(count==k){
            for(int i=0;i<n;i++)
                cout<<data[i];
            cout<<'\n';
        }
        return;
    }
    for(int i=1;i>=0;i--){
        data[idx]=i;
        if(i==1){
            Recursive(idx+1,count+1);
        }
        else{
            Recursive(idx+1,count);
        }
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    cin>>n>>k;
    Recursive(0,0);
    return 0;
}

```



### #3.Division

> 문제: 임의의 자연수는 그보다 작은 자연수들의 합으로 표현될 수 있다. 예를 들어 4의 경우,
> 4
> = 3+1
> = 2+2
> = 2+1+1
> = 1+1+1+1
>
> 위와 같은 방법으로 표현 될 수 있다. 이 때 , 숫자의 구성이 같으면서 그 순서만이 다른 경우는 같은 경우로 생각하는데, 예를 들어 다음 세 가지 경우는 모두 같은 경우이다.
>
> //2 + 1 + 1, 1 + 2 + 1 , 1 + 1 + 2
>
> 자연수 n을 입력 받아 이를 n보다 작은 자연수들의 합으로 나타내는 방법을 모두 출력하는 프로그램을 재귀 호출을 사용하여 작성하시오.

**알고리즘:**

- 재귀함수 이용
- 내림차순: i-- for문 이용
- Recursive(sum, idx,maxNum) : for(maxNum~1)을 돌며 data[idx]에 저장 
- 종료조건: if(sum>=n) 일 때 sum>n이면 그냥 종료 sum==n for(0~maxNum) 출력
- 시간복잡도: O() 우찌 구하누?

``` c++

#include <iostream>
using namespace std;

int data[20];
int n;

void Recursive(int sum,int idx,int maxNum){
    if(sum>=n){
        if(sum==n){
            cout<<data[0];
            for(int i=1;i<idx;i++){
                cout<<"+"<<data[i];
            }
            cout<<"\n";
        }
        return;
    }
    for(int i=maxNum;i>0;i--){
        sum+=i;
        data[idx]=i;
        Recursive(sum,idx+1,i);
        sum-=i;
    }
    
}
int main(){
    cin>>n;
    Recursive(0,0,n-1);
}

```

### #3.Dessert

>  문제: 농부 존은 소들의 저녁식사 줄 세우는 새로운 방법을 개발 했다. N(1~15)마리의 소들을 순서대로 세 워놓은 후, 각 소들 사이에 +, - , . 셋 중 1가지가 써져있는 냅킨을 배치해서 최종 결과가 0 이 되게 해야 하는 것이다. 점(.)이 써져있는 냅킨을 통해 더 큰 수를 만들 수 있게 된다. 아래와 같은 경우를 보자. (ps .이 써져있는 냅킨은 '공백'이라고 생각하면 된다.) 1-2.3-4.5+6.7 이와 같은 배치는 1-23-45+67 을 나타낸다. 결과는 0 이다. 10.11은 1011 로 해석된다.
>
>  입력: 첫 째 줄에는 소들의 수 N(1 ≤ N ≤ 15)이 입력된다.
>
>  출력: 처음 20줄에 대해 가능한 20가지 답을 출력하는데, 사전 순으로 앞선 것을 출력한다. 순서는 +가 가장 앞서고 -와 . 이 순서대로 뒤따른다. 답이 20개 이하라면 가능한 답을 각 숫자와 문자 사이에 공백을 두고 출력한다. 모두 출력한다. 20개를 초과하는 경우 21번째 답부터는 출력하지 않는다. 마지막 줄에는 가능한 답의 총 가지수를 출력한다.
>
> 예제 입력
> 7
> 예제 출력
> 1 + 2 - 3 + 4 - 5 - 6 + 7
> 1 + 2 - 3 - 4 + 5 + 6 - 7
> 1 - 2 + 3 + 4 - 5 + 6 - 7
> 1 - 2 - 3 - 4 - 5 + 6 + 7
> 1 - 2 . 3 + 4 + 5 + 6 + 7
> 1 - 2 . 3 - 4 . 5 + 6 . 7
> 6

**소요시간: 90분**

**알고리즘:**

- 핵심:  `.`의 처리이다. 이를 처리하기 위해 `.`  전까지만 계산해야 한다. 이를 위해 Recursive 재귀함수를 돌면서 idx함수속에서 idx-1까지 계산해야 한다.   

``` c++
#include <iostream>
using namespace std;
const int MAX=17;
// idx==0,1일 경우 sum에 sign부호에 맞춰 var 계산 var에 idx전달
// idx==2일 경우 sum 그대로, sign 그대로 var에 var*10+idx 전달
// 10이 넘어갈 경우 && idx==2인 경우 var*100
// 1.2.3인경우 그냥 똑같이 *10 해주면 된다.
// data[]에 부호 저장, 출력을 위해
// 시작점은 1부터 sum=0 var=0
// 종료점은 빼서 계산
int n;
char data[MAX];
int cnt=0;

void Recursive(int idx, int sum, int sign, int var){
    if(idx>=n){ //기저조건
        if(sign==0)
            sum+=var+idx;
        else
            sum-=(var+idx);
        if(sum==0){
            if(cnt<=20){
                for(int i=1;i<n;i++)
                    cout<<i<<" "<<data[i]<<" ";
                cout<< n<<"\n";
            }
            cnt++;
        }
        return;
    }
    for(int i=0;i<3;i++){
        if(i==0){
            data[idx]='+';
            if(sign==0)
                Recursive(idx+1,sum+var+idx,i,0);
            else
                Recursive(idx+1,sum-var-idx,i,0);
        }
        else if(i==1){
            data[idx]='-';
            if(sign==0)
                Recursive(idx+1,sum+var+idx,i,0);
            else
                Recursive(idx+1,sum-var-idx,i,0);
        }
        else if(i==2 && idx<n){
            data[idx]='.';
            if(idx<9)
                Recursive(idx+1,sum,sign,(var+idx)*10);
            else
                Recursive(idx+1,sum,sign,(var+idx)*100);
        }
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    cin>>n;
    Recursive(1,0,0,0);
    cout<<cnt;
}

```

### #4.inequal

> <inequal>
>  두 종류의 부등호 기호 ‘<’와 ‘>’가 k 개 나열된 순서열 A가 있다. 우리는 이 부등호 기호 앞뒤에 서로 다른 한 자릿수 숫자를 넣어서 모든 부등호 관계를 만족시키려고 한다. 예를 들어, 제시된 부등호 순서열 A가 다음과 같다고 하자.
>   A ⇒ < < < > < < > < >
>
> 부등호 기호 앞뒤에 넣을 수 있는 숫자는 0부터 9까지의 정수이며 선택된 숫자는 모두 달라야 한다. 아래는 부등호 순서열 A를 만족시키는 한 예이다.
>
>  3 < 4 < 5 < 6 > 1 < 2 < 8 > 7 < 9 > 0
>
>  이 상황에서 부등호 기호를 제거한 뒤, 숫자를 모두 붙이면 하나의 수를 만들 수 있는데 이 수를 주어진 부등호 관계를 만족시키는 정수라고 한다. 그런데 주어진 부등호 관계를 만족하는 정수는 하나 이상 존재한다. 예를 들어 3456128790 뿐만 아니라 5689023174도 아래와 같이 부등호 관계 A를 만족시킨다.
>
>  5 < 6 < 8 < 9 > 0 < 2 < 3 > 1 < 7 > 4
>
>  여러분은 제시된 k 개의 부등호 순서를 만족하는 (k+1) 자리의 정수 중에서 최대값과 최소값을 찾아야 한다. 앞서 설명한 대로 각 부등호의 앞뒤에 들어가는 숫자는 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } 중에서 선택해야 하며 선택된 숫자는 모두 달라야 한다. 프로그램의 실행시간은 0.5초를 넘을 수 없다.
>
>  입력
>  첫 줄에 부등호 문자의 개수를 나타내는 정수 가 주어진다. 그 다음 줄에는 k 개의 부등호 기호가 하나의 공백을 두고 한 줄에 모두 제시된다. k 의 범위는 2 <= k <= 9이다.
>
>  출력
>  여러분은 제시된 부등호 관계를 만족하는 자리의 최대, 최소 정수를 첫째 줄과 둘째 줄에 각각 출력해야 한다. 단 아래 예(1)과 같이 첫 자리가 0인 경우도 정수에 포함되어야 한다. 모든 입력에 답은 항상 존재하며 출력 정수는 하나의 문자열이 되도록 해야 한다.
>
> 입력
> 2
> < >
> 예제 출력
> 897
> 021
>
> 예제 입력
> 9
> /> < < < > > > < <
> 예제 출력
> 9567843012
> 1023765489

**소요시간: 30분**

**알고리즘:**

- BruteForce로 처리하면 O(10^n)이라 Timeout이다.
- BackTracking으로 처리하여 재귀를 돌 때마다 flag[]를 통해 사용한 숫자를 체크하고 조건을 확인하며 불가능한 경우를 사전에 거른다.
- RecursiveAscend(int idx), RecursiveDescend(int idx)의 for문 알고리즘을 함수로 작성하여 코드길이 단축 가능
- for문 알고리즘 중 else if(!flag[i]) 하위 조건 2개를 합쳐서 코드길이 단축 가능

``` c++
#include <iostream>
using namespace std;

int data[10];
char sign[10];
bool flag[10];
int n;
bool finish=false;

void RecursiveAscend(int idx){
    if(idx>n){
        for(int i=0;i<=n;i++)
            cout<<data[i];
        finish=true;
        return;
    }
    for(int i=9; i>=0  ;i--){
        if(idx==0){
            data[idx]=i;
            flag[i]=true;
            RecursiveAscend(idx+1);
            flag[i]=false;
        }
        else if(!flag[i]){
            if(sign[idx-1]=='>' && data[idx-1]>i ){
                data[idx]=i;
                flag[i]=true;
                RecursiveAscend(idx+1);
                flag[i]=false;
            }
            else if(sign[idx-1]=='<' && data[idx-1]<i){
                data[idx]=i;
                flag[i]=true;
                RecursiveAscend(idx+1);
                flag[i]=false;
            }
            
        }
        if(finish)
            return;
    }
}
void RecursiveDescend(int idx){
    if(idx>n){
        for(int i=0;i<=n;i++)
            cout<<data[i];
        finish=true;
        return;
    }
    for(int i=9; i>=0  ;i--){
        if(idx==0){
            data[idx]=i;
            flag[i]=true;
            RecursiveAscend(idx+1);
            flag[i]=false;
        }
        else if(!flag[i]){
            if(sign[idx-1]=='>' && data[idx-1]>i){
                data[idx]=i;
                flag[i]=true;
                RecursiveAscend(idx+1);
                flag[i]=false;
            }
            else if(sign[idx-1]=='<' && data[idx-1]<i){
                data[idx]=i;
                flag[i]=true;
                RecursiveAscend(idx+1);
                flag[i]=false;
            }
            
        }
        if(finish)
            return;
    }
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>sign[i];
    RecursiveAscend(0);
    RecursiveDescend(0);
}


```

















