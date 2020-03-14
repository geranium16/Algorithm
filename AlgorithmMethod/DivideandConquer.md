# Divide and Conquer

 **분할 정복**은 한 문제를 유형이 비슷한 여러 개의 하위 문제로 나누어 재귀적으로 해결하고 이를 합쳐 원래 문제를 해결한다. 분할 정복 방식이 하위 문제를 재귀적으로 해결하기 때문에 하위 문제 각각은 원래 문제보다 범위가 작아야 하며 하위 문제는 각 문제마다 **탈출 조건**이 존재해야 한다. 분할 정복 알고리즘을 이해하기 위해 다음과 같이 세 부분으로 나눠서 생각해봅시다.

1. **분할**: 원래 문제를 분할하여 비슷한 유형의 더 작은 하위 문제들로 나눈다.
2. **정복**: 하위 문제 각각을 재귀적으로 해결한다. 하위 문제의 규모가 충분히 작으면 문제를 탈출 조건으로 놓고 해결한다.
3. **합치기**: 하위 문제들의 답을 합쳐서 원래 문제를 해결한다.

 분할 정복 알고리즘의 단계를 *분할, 정복, 합치기* 세 개로 나누면 쉽게 기억할 수 있다. 병합 정렬과 Quick 정렬 두 가지 정렬 방법은 모두 이러한 분할 정복을 기반으로 하고 있다.



## #3. 연속부분최대합

> ### 문제 
>
> N개의 정수가 주어질 때, 연속된 부분을 선택하여 합을 최대화 하는 프로그램을 작성하시오. 예를 들어, 아래와 같이 8개의 숫자가 있을 경우, 색칠된 부분을 선택했을 때 그 합이 가장 최대가 된다.
>
> ### 입력
>
> ---
>
> 첫 번째 줄에 n이 주어진다. ( 1 ≤ n ≤ 100,000 ) 두 번째 줄에 n개의 정수가 주어진다.
>
> ### 출력
>
> ---
>
> 연속된 부분을 선택하였을 때의 최댓값을 출력한다.
>
> ### 예제 입력
>
> ---
>
> 8
>
> 2 3 -5 8 -3 4 2 -9
>
> ### 예제 출력
>
> ---
>
> 11
>
> ### 예제 입력
>
> ---
>
> 5
>
> -1 -2 3 -2 4
>
> ### 예제 출력
>
> ---
>
> 5



```c++
//<방법1:BruteForce O(n^2)>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector <int> arr;


int main(){
    cin>>n;
    int max=-987987987;
    for(int i=0;i<n;i++){
        int var;
        cin>>var;
        arr.push_back(var);
    }
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=i;j<n;j++){
            sum+=arr[j];
            if(sum>max)
                max=sum;
        }
    }
    cout<<max;
}
```

``` c++
//<방법2:Divide and Conquer O(nlogn)>

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;
vector <int> arr;

int DivideConquer(int s,int e){
    if(s>=e) //탈출조건
        return arr[s];
    
    int m=(s+e)/2;
    int left=DivideConquer(s,m); //분할
    int right=DivideConquer(m+1,e);//분할
   
  	//정복
    int mSol1=0,maxmSol1=-987987987,mSol2=0,maxmSol2=-987987987;
    for(int i=m;i>=s;i--){
        mSol1+=arr[i];
        if(maxmSol1<mSol1)
            maxmSol1=mSol1;
    }
    
    for(int i=m+1;i<=e;i++){
        mSol2+=arr[i];
        if(maxmSol2<mSol2)
            maxmSol2=mSol2;
    }
    int mid=mSol1+mSol2; //left경계를 포함하는 왼쪽 최대 right 경계를 포함하는 오른쪽 최대
    return max(max(left,right),mid);
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        arr.push_back(a);
    }
    cout<<DivideConquer(0, n-1);
}
```



```c++
//<방법3 O(n)>

#include <iostream>
#include <vector>
using namespace std;

int n;
vector <int> arr;

int main(){
    cin>>n;
    int sum=0;
    int max=-987987987;
    for(int i=0;i<n;i++){
        int var;
        cin>>var;
        arr.push_back(var);
    
        if(sum+var>0){ //sum+var>0이면 즉,1이라도 양수이면 sum값은 올라가기때문에 sum에 변수를 더해야한다.
            sum+=var;
            if(max<sum)
                max=sum;
        }
        if(max<var) // 모든수가 음수를 대비해서
            max=var;
           
        
    }
    cout<<max;
}

```



