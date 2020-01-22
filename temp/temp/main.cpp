#include <iostream>
#include <vector>
using namespace std;

int n;
vector <bool> data;
int main(){
    cin>>n;
    data.push_back(true); // 기저조건 f(0)=철수승
    data.push_back(true); // 기저조건 f(1)=철수승
    data.push_back(true); // 기저조건 f(2)=철수승
    
    for(int i=3;i<n;i++){
        if(!data[i-1] || !data[i-2] || !data[i-3]) // 전 3항 중 하나라도 영희가 무조건 승인 경우가 있으면 data[i]는 참
            data.push_back(true);
        else
            data.push_back(false);
    }
    if(data[n-1])
        cout<<"YES";
    else
        cout<<"NO";
}
