//<dessert>
//문제
//농부 존은 소들의 저녁식사 줄 세우는 새로운 방법을 개발 했다. N(1~15)마리의 소들을 순서대로 세 워놓은 후, 각 소들 사이에 +, - , . 셋 중 1가지가 써져있는 냅킨을 배치해서 최종 결과가 0 이 되게 해야 하는 것이다. 점(.)이 써져있는 냅킨을 통해 더 큰 수를 만들 수 있게 된다. 아래와 같은 경우를 보자. (ps .이 써져있는 냅킨은 '공백'이라고 생각하면 된다.) 1-2.3-4.5+6.7 이와 같은 배치는 1-23-45+67 을 나타낸다. 결과는 0 이다. 10.11은 1011 로 해석된다.

//입력
//첫 째 줄에는 소들의 수 N(1 ≤ N ≤ 15)이 입력된다.
//

//출력
//처음 20줄에 대해 가능한 20가지 답을 출력하는데, 사전 순으로 앞선 것을 출력한다. 순서는 +가 가장 앞서고 -와 . 이 순서대로 뒤따른다. 답이 20개 이하라면 가능한 답을 각 숫자와 문자 사이에 공백을 두고 출력한다. 모두 출력한다. 20개를 초과하는 경우 21번째 답부터는 출력하지 않는다. 마지막 줄에는 가능한 답의 총 가지수를 출력한다.
//
//
//
//예제 입력
//copy7
//예제 출력
//copy1 + 2 - 3 + 4 - 5 - 6 + 7
//1 + 2 - 3 - 4 + 5 + 6 - 7
//1 - 2 + 3 + 4 - 5 + 6 - 7
//1 - 2 - 3 - 4 - 5 + 6 + 7
//1 - 2 . 3 + 4 + 5 + 6 + 7
//1 - 2 . 3 - 4 . 5 + 6 . 7
//6
 

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
//        for(int i=1;i<n;i++)
//            cout<<i<<" "<<data[i]<<" ";
//        cout<< n<<" "<<sum<<"\n";

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
