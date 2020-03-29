#include <iostream>
#include <vector>
using namespace std;

int main(){
    const int MAX = 100010;
    const int MAX2 = 5005;
    
    int tc;
    cin>>tc;
    for(int t=0;t<tc;t++){
        int arr_size=0, code_size=0, input_size=0;
        int arr_idx=0, code_idx=0, input_idx=0;
        
        cin>>arr_size>>code_size>>input_size;
        
        int arr[MAX]={0,};
        char code[MAX2];
        char input[MAX2];
        int loop[MAX2];
        int looptemp[MAX2];
        bool flag=false;
        cin>>code;
        cin>>input;
        
        //[][]의 짝을 지어줄 것이다.
        //]이 나오면 최신 [과 함께 제거해주고 [idx에 ]idx를 ]idx에 [idx를 넣어줄 것이다.
        int j=-1;
        int max_code_idx=0;
        for(int i=0;i<code_size;i++){
            if(code[i]=='[')
                looptemp[++j]=i;
            else if(code[i]==']'){
                looptemp[++j]=i;
                loop[looptemp[j]]=looptemp[j-1];
                loop[looptemp[j-1]]=looptemp[j];
                j-=2; //최신 [] 제거
            }
        }
        
        for(int i=0;i<50000000;i++){
            if (code_idx >= code_size) {
                flag = true;
                break;
            }
            if(code[code_idx]=='-')
                arr[arr_idx] = (arr[arr_idx]-1) < 0 ? 255 : arr[arr_idx]-1;
            
            else if(code[code_idx]=='+')
                arr[arr_idx] = (arr[arr_idx]+1) % 256;
            
            else if(code[code_idx]=='<')
                arr_idx = (arr_idx-1) < 0 ? arr_size-1 : arr_idx-1;
            
            else if(code[code_idx]=='>')
                arr_idx = (arr_idx+1) % arr_size;
            
            
            else if(code[code_idx]=='['){
                if(arr[arr_idx]==0)
                    code_idx=loop[code_idx];
            }
            
            else if(code[code_idx]==']'){
                if(arr[arr_idx]!=0)
                    code_idx=loop[code_idx];
            }
            
            else if(code[code_idx]==','){
                if(input_idx<input_size)
                    arr[arr_idx]=(int)input[input_idx++];
                else
                    arr[arr_idx]=255;
            }
            
            
            code_idx+=1;
            max_code_idx = code_idx > max_code_idx ? code_idx : max_code_idx;
        }
        if(flag)
            cout<<"Terminates\n";
        else{
            cout<<"Loops "<<loop[max_code_idx]<<" "<<max_code_idx<<"\n";
        }
    }

}
