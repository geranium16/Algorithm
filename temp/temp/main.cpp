//문제:거듭제곱구하기L
//
//n과 m이 주어질 때, n의 m승을 구하는 프로그램을 작성하시오. 단, n의 m승의 값이 커질 수 있기 때문에, 정답을 10,007 으로 나눈 나머지를 출력한다.
//
//
//
//입력
//첫 번째 줄에 숫자 n과 m이 주어진다. ( 1 ≤ n ≤ 100, 1 ≤ m ≤ 1,000,000,000,000,000,000 )
//
//출력
//첫째 줄에 n의 m승을 10,007 으로 나눈 나머지를 출력한다.
//
//
//
//예제 입력
//copy3 4
//예제 출력
//copy81

//Recursive 10승씩
//마지막남은건
//Recursive 내용 :



#include <iostream>
using namespace std;

int n;
long int m;

//x*x의 나머지는 y=x의나머지*x의나머지 만약 y가 x보다크면 y/x의 나머지와 같다. 따라서 n^m을하고 10007을 하는것이 아닌 계속해서 n%10007을하며 나머지만 제곱해서 끌고 가면된다.
//거듭제곱으로 올라가기 but 끝지점쯤에서 1024, 2048 사이의 값이면 일일이 계산해야하는 부분이 많다.
//따라서 거듭제공으로 내려오기 짝수 : 2024/2 홀수 :5-1
//기저조건: x==1 n^1이기때문에 n자체

long int Recursive(long int x){
    if(x==1)
        return n;
    
    
    if(x%2==0){
        long int y = Recursive(x/2);
        return (y*y)%10007;
        
    }
    else{
        long int y = Recursive(x-1);
        return (y*n)%10007;
    }
    
    
}
int main(){
    cin>>n>>m;
    cout<<Recursive(m);
}
