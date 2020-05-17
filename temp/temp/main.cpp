#include <iostream>

#include <algorithm>

using namespace std;



int main(){
    
    
    
    int a[10] = {1, 4, 7, 10, 2, 5, 8, 3, 6, 9};
    
    int *p, *q;
    
    
    
    p = find(a, a+10, 8);
    if(p == a+10) cout << "값 8을 찾지 못했습니다. ㅠㅠ" << endl;
    else cout << "값 8을 a[" << p-a << "]에서 찾았습니다." << endl;
    
    
    
    q = find(a+3, a+8, 4);
    if(q == a+8) cout << "값 4를 찾지 못했습니다. ㅠㅠ" << endl;
    else cout << "값 4를 a[" << q-a << "]에서 찾았습니다." << endl;
    
    
    
    return 0;
    
}
