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
> 
>
> 6

**소요시간:40분**

**알고리즘:**

 처음 생각했던 방법은 이중 for문을 이용해 구구단표 숫자를 하나씩 입력받는 대신 해당 숫자를 인덱스로 가지는 배열을 ++해주려고 했다. 하지만 이는 O(n^2)의 시간복잡도를 가져 Timeout이다. 따라서 일반 브루트포스 방법으로는 시간내에 해결하지 못한다.

 **Parametersearch을 사용한 최종 알고리즘**

1. 전체 1~n*n 범위에서 중간값을 선택해 해당 숫자가 몇번째인지 구할 것이다.  (getOrder)

2. 도출해낸 숫자의 순서가 k보다 크면 Parametersearch(s,mid), 작으면 Parametersearch(mid,e)

3. 기저조건(s+1>=e)까지 반복하면 k값 순서를 가지는 수가 s or e일 것이다.

4. 해당 숫자가 몇번째인지 구하는 getOrder(num)는 구구단표의 행을 기준으로 for문을 돌려 해당행의 최대수인 n*idx가 num보다 작으면 해당 행은 모든 수가 num보다 작다. 또한 num보다 큰 경우 해당 행은 num/idx만큼 num보다 작은 수를 가지고 있다. 이를 통해 전체 행렬에서 num보다 작은 수를 구할 수 있고 중복되는 num들 바로 전 숫자들의 최대 순서를 알 수 있다. 즉 1 2 2 4 4 4 5 5 에서 4의 순서를 getOrder를 통하면 1 2 2를 구해내 3이라는 숫자를 알아낼 수 있다. 

5. 이를 통해 구한 숫자가 order>=k ? true:false을 통해 반환하면서 true가 반환되면 (s,mid)가 들어가고이 때는 order==k일 수도 있으니 e값에 들어가는  mid가 정답일 수 있다. 그러나 false가 반환되면 (mid,e)가 들어간다. 이 때 order==k일 수 없기 때문에 s값에 들어가는 mid가 정답일 수 없다. 따라서 s+1>=e에서 우리가 찾는 값은 e이다.



**핵심**

**1. Parametersearch 생각!!!**

**2. 중복되는 숫자들의 순서 처리 -> getorder 반환 및 s, e를 동일한 논리로 설계**

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

# #3. 중복되지않는 구간

> ## 문제
>
> n개의 숫자 중 r개의 연속된 숫자를 선택했을 때, 이 연속 부분 내에서 중복되지 않기를 원한다.
>
> 1 3 1 2 4 2 1 3 2 1
>  위 숫자배열에서 최대연속구간은 4 2 1 3 ->4이다. 또는 3 1 2 4
>
>  1<=n<=100,000
>
> ## 출력
>
> 최대연속구간길이
>
> ## 예제 입력
>
> 10
> 1 3 1 2 4 2 1 3 2 1
>
> ## 예제 출력
>
> 4

**소요시간: 60분**

**알고리즘:**

 1. 브루트 포스 이중포문으로 하나하나 확인 O(n^2) 불가
 2. 이러한 구간 찾기 -> parametersearch생각
 3. 구간의길이를 기준으로 parametersearch 설계  구간의 길이 1 2 3 4 5 6 7 8 9 10
 o o o o o x x x x x --> 경계값 5도출 s+1>=e 에서 s출력
 4. 시간복잡도: 해당구간의 길이 중복여부 n  parametersearch log n  -> O(nlogn)
  5. 중복체크 알고리즘: visited를 둬 체크되어있으면 start증가시켜 중복안되는 구간 만들고 다음 인덱스 확인 O(n)

***핵심***

***2. parametersearch(s,e) 처음 s와 e 범위를 정할 때(1,n)일시 전체구간에 중복이 없을 때 s를 return하면 s=n-1되서 잘못 출력 따라서 이러한 경계조건 s,e을 줄 떄 s=무조건 가능한값 e=무조건 불가능한 값으로 줘야한다.***

***1. 중복체크 알고리즘 다시보기***

``` c++
#include <iostream>
#include <vector>
using namespace std;

int n;
vector <int> arr;

// length만큼의 구간에 중복체크
bool isOverlap(int length){
    bool visited[101010];
    int start=0,current_length=0;
    for(int i=0;i<n;i++)
    {
        while(visited[arr[i]]){
            visited[arr[start++]]=false;
            current_length--;
        }
        current_length++;
        visited[arr[i]] = true;
        if(current_length>=length)
            return true;
        
    }
    return false;
}
int parametersearch(int s,int e){
    if(s+1>=e)
        return s;
    int mid=(s+e)/2;
    if(isOverlap(mid))
        return parametersearch(mid,e);
    else
        return parametersearch(s,mid);
    
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        int var;
        cin>>var;
        arr.push_back(var);
    }
    cout<<parametersearch(1,n+1); // (1,n)일시 전체구간에 중복이 없을 때 s=n-1되서 잘못출력
    //따라서 이러한 경계조건 s,e을 줄 떄 s=무조건 가능한값 e=무조건 불가능한 값으로 줘야한다.
}


```

*내 알고리즘이 정확히 어뜨케 돌아가는지 모른다. 확실히 설계하고 알고리즘짜기!!!!!!