//NN단표 (NNdan.cpp)
//
//
//문제
//알랩이는 구구단표처럼 NN단표를 만들었다고 한다.
//
//NN단표는 2차원 배열의 모양으로 곱셈 1단부터 N단까지의 값들을 적어놓은 형태이다.
//
//NN단표의 배열을 A라고 했을 때, 배열의 들어가는 수 A[i][j]=i*j이다.(즉, 4행 7열에는 28, 7행 5열에는 35가 들어가 있다.)
//
//알랩이는 N단까지 나온 숫자들 중에서 K번째로 작은 수를 찾고 싶어한다.
//
//이때, 중복되는 여러 수들을 고려한다. 즉 N*N개의 모든 수들 중에서 K번째 수를 구하는 것이다.
//
//입력
//첫째 줄에 배열의 크기 N이 주어진다. N은 100,000보다 작거나 같은 자연수이다. 둘째 줄에 K가 주어진다. K는 N*N보다 작거나 같고, 10,000,000,000보다 작거나 같은 자연수이다.
//
//출력
//K번째 원소를 출력한다.

//예제 입력
//3
//7
//예제 출력
//6

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
