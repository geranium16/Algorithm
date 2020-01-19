# Binary Search

> 정렬되어 있는 숫자 중에서 특정 숫자를 찾는다.
>
> 하나 하나 찾으면 O(n) 필요 BinarySearch 사용시 O(logn) 필요



- **2 3 4 5 7 8 9 11 14 23 에서 찾고자 하는 값: 5 일 때**

  1. 중간값 선택 7

  2. 7은 목표 숫자보다 크니 그 보다 큰 값인 8~23 버리기

  3. 2와7의 중간값 선택 4

  4. 2~3버리기

절반씩 지워나가면서 찾는다. n*(1/2)^k=1 ->O(logn)



** **정렬하면 결국 O(nlogn)이 아닌가요?***

***맞긴 맞다. 하지만 이미 정렬되어 들어오는 경우가 있다. 또한 찾을 숫자가 매우 많은 경우, 정렬 후 Binary Search가 좋음***



<코드 작성>

1. arr의 s번부터 e번째 값 중 value를 찾는 함수 && 위치 반환

2. 기저조건에서 동작하는지 확인

```c++
//함수의 정의
int binarysearch(int arr[],int start,int end,int value){
    
    if(start>end)
        return -1;
    
    else{
        int mid=(start+end)/2;
            if(arr[mid]==q)
                  return mid;
        
            else if(arr[mid]>q)
                  return binarysearch(arr,start,mid-1,q); //-1 해줘야 뒤짚어져서 끝남을 알 수 있다.
        
            else
                  return binarysearch(arr,mid+1,end,q); //+1 해줘야 뒤짚어져서 끝남을 알 수 있다.
    }
    
}

```

# ParameterSearch

>  Binary Search를 이용하여 문제를 해결하는 테크닉이다. 기본 틀은 BinarySearch와 같지만 mid의 값을 알아내는 것이 목적인 반면 ParameterSearch는 내가 원하는 조건을 만족하는 가장 알맞은 값을 알아내고 싶을 때 사용한다.



### #1.구간의합

>  문제:N개의 숫자와 S가 주어질 때, 몇 개의 연속된 값을 합해야 그 합이 S이상이 되는가?(1<=N<=100,000)
>
> 7 14
>
> 2 1 8 1 3 7 2 6 3   —> 7 2 6 ( 3 )

**알고리즘:**

* ParameterSearch 이용: 구간의 길이 : 1 2 3 4 ..... n인 경우 합이 s이상인 경우와 그렇지 못한 경우의 경계를 찾아 정답 도출                          
* 경계를 알아내기 위해서는  (start,mid), (mid,end)에 if(start+1>=end) 으로 조건을 주어 X O 를 통해 경계 도출           
* 시간복잡도: O(logn)



``` c++
#include <iostream>
#include <vector>
using namespace std;

int n,s;
vctor<int> arr;

//start길이 ~ end길이의 중간값인 mid길이만큼 배열에서 연속적으로 더해 해당 mid길이의 sum이 목표값이 s보다 큰지 작은지 확인하여 경계를 알아내는 함수
int ParameterSearch(int start,int end){
    if(start+1>=end) // X O 가 만나면 O인 길이 출력
        return end;
    int mid=(start+end)/2; //중간길이 확인
    for(int i=0;i<mid;i++){ //구간의 길이(m)만큼 더하기 위한 for
        int sum=0;
        for(int j=i;j<i+mid;j++){ // 배열내 sum의 구간의 길이(m)만큼 더하는 모든 경우
            sum+=arr[i];
            if(sum>=s) // 구간의 길이 m이 가능하면 더 줄이기
                return ParameterSearch(start,mid);
        }
    }
    return ParameterSearch(mid,end);
}
int main(){
    cin>>n>>s;
    for(int i=0;i<n;i++){
        int var;
        cin>>var;
        arr.push_back(var);
    }
    cout<<ParameterSearch(0,n-1);
    
    
}

```

### #2.NN단표

> 문제
>
> ---
>
> 알랩이는 구구단표처럼 NN단표를 만들었다고 한다.
> NN단표는 2차원 배열의 모양으로 곱셈 1단부터 N단까지의 값들을 적어놓은 형태이다.
> NN단표의 배열을 A라고 했을 때, 배열의 들어가는 수 A[i][j]=i*j이다.(즉, 4행 7열에는 28, 7행 5열에는 35가 들어가 있다.)
> 알랩이는 N단까지 나온 숫자들 중에서 K번째로 작은 수를 찾고 싶어한다.
> 이때, 중복되는 여러 수들을 고려한다. 즉 N*N개의 모든 수들 중에서 K번째 수를 구하는 것이다.
>
> 입력
>
> ---
>
> 첫째 줄에 배열의 크기 N이 주어진다. N은 100,000보다 작거나 같은 자연수이다. 둘째 줄에 K가 주어진다. K는 N*N보다 작거나 같고, 10,000,000,000보다 작거나 같은 자연수이다.
>
> 출력
> ---
>
> K번째 원소를 출력한다.
>
> 예제 입력
> ---
>
> 3
> 7
>
> 예제 출력
> ---
>
> 6

소요시간:40분

``` c++
//1 2 3 4 5
//2 4 6 8 10
//3 6 9 12
//4 8 12 16

//1번6을 찾는다.
//-> 1:if(n<6) ->n개 else n개
//-> 2:if(n*2<6) n개     else num/2개
//-> 3:              else n/3개
//...... O(n) 걸림 최댜 100,000
//2번: parametersearch이용 lonn 총 nlogn
//1 2 2 3 3 3 4 4 4 4 k=5
//      O O    // X O 경계조건에서 찾아야함
//즉, 1번과정에서 같은 숫자를 포함하면 if(s+1>=e) 조건에서 e를 출력해야한다.
#include <iostream>
using namespace std;

long int n,k;
bool getOrder(long int num){
    long int order=0;
    for(int i=1;i<=n;i++){
        if(n*i<=num)
            order+=n;
        else
            order+=num/i;
    }
    return order>=k ? true:false;
    
}

long int ParameterSearch(long int s,long int e){
    if(s+1>=e)
        return e;
    long int mid=(s+e)/2;
    if(getOrder(mid))
        return ParameterSearch(s,mid);
    else
        return ParameterSearch(mid,e);
    
}
int main(){
    cin>>n>>k;
    cout<<ParameterSearch(1,n*n);
    
}
```

