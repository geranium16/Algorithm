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

#### #1.순열구하기

> 문제: 서로 다른 n개의 원소들 중에서 r개만을 뽑아 일렬로 나열하는 것을 순열이라 한다. 예를 들어, 3개의 원소 a, b, c 중에서 2개만을 뽑아 나열하면 ab, ac, ba, bc, ca, cb 의 6가지 경우가 있다. n과 r이 주어질 때, n개의 소문자 중에서 r개만을 뽑아 나열하는 모든 경우를 출력하는 프로그램을 작성하시오. 단, a부터 시작하여 연속으로 n개의 알파벳을 갖고 있다고 하자.
>
> 입력: 첫 번째 줄에 n과 r이 주어진다. ( 1 ≤ n ≤ 10, 0 ≤ r ≤ min(n, 7) )
>
> 출력: 각 줄에 n개의 소문자 중에서 r개만을 뽑아 나열하는 경우를 사전순으로 나열한 결과를 출력한다.

재귀함수 사용시 앞뒤로 초기화가 중요하다!!! ,Recursive 이전에 flag[i]=true 해줬으면 재귀함수 뒤 flag[i]=false 초기화

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

``` c++

#include <iostream>
using namespace std;
int flag[20]={0,};
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
        flag[i]--;
        sum-=i;
    }
    
}
int main(){
    cin>>n;
    Recursive(0,0,n-1);
}

```



















