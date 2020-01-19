
/*
 문제
 n개의 숫자 중 r개의 연속된 숫자를 선택했을 때, 이 연속 부분 내에서 중복되지 않기를 원한다.
 
 1 3 1 2 4 2 1 3 2 1
 위 숫자배열에서 최대연속구간은 4 2 1 3 ->4이다. 또는 3 1 2 4
 
 
 1<=n<=100,000
 
 10
 1 3 1 2 4 2 1 3 2 1
 
 */
/*
 1. 브루트 포스 이중포문으로 하나하나 확인 O(n^2) 불가
 2. 이러한 구간 찾기 -> parametersearch생각
 3. 구간의길이를 기준으로 parametersearch 설계  구간의 길이 1 2 3 4 5 6 7 8 9 10
 o o o o o x x x x x --> 경계값 5도출 s+1>=e 에서 s출력
 4. 시간복잡도: 해당구간의 길이 중복여부 n  parametersearch log n  -> O(nlogn)
 */
#include <iostream>
#include <vector>
using namespace std;

int n;
vector <int> arr;

// length만큼의 구간에 중복체크
bool isOverlap(int length){
    bool data[101010];
    int start=0,current_length=0;
    for(int i=0;i<n;i++)
    {
        while(data[arr[i]]){
            data[arr[start++]]=false;
            current_length--;
        }
        current_length++;
        data[arr[i]] = true;
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

