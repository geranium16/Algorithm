#include <iostream>
using namespace std;

char mymap[6][3][3];
int n;

void rotation(int a){
    
    int temp=mymap[a][0][0];
    for(int i=0;i<3;i++){
        
    }
    for(int i=0;i<3;i++){
        
    }
    for(int i=2;i>=0;i--){
        
    }
    for(int i=2;i>0;i--){
        
    }
    
}
int main(){
    for(int i=0;i<6;i++){
        char temp;
        if(i==0)
            temp='w'; //윗면
        else if(i==1)
            temp='y'; //아랫면
        else if(i==2)
            temp='r'; //앞면
        else if(i==3)
            temp='b'; //오른쪽면
        
        else if(i==4)
            temp='o'; //뒷면
        else
            temp='g'; //왼
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++)
                mymap[i][j][k]=temp;
        }
    }//L- U- L+ U- L- U- U- L+ U+ U+
    //위 아래 앞 오 뒷 왼
    cin>>n;
    for(int i=0;i<n;i++){
        char var[2];
        cin>>var;
        if(var[0]=='L'||var[0]=='R'){
            //앞면: row=2 col=0,1,2
            //오른쪽면: col=2 row=2,1,0
            //뒷면: row=0 col=2,1,0
            //왼쪽면: col=0 row=0,1,2
            //시계방향 뒤(4)->위(0)->앞(2)->아래(1)
            int l;
            if(var[0]=='L')
                l=0;
            
            else{
                l=2;
                if(var[1]=='-')
                    var[1]='+';
                else
                    var[1]='-';
            }
            if(var[1]=='+'){
                int temp[3];
                temp[0]=mymap[0][2][l];
                temp[1]=mymap[0][1][l];
                temp[2]=mymap[0][0][l];
                mymap[0][2][l]=mymap[4][2][l];
                mymap[0][1][l]=mymap[4][1][l];
                mymap[0][0][l]=mymap[4][0][l];
                mymap[4][2][l]=mymap[1][2][l];
                mymap[4][1][l]=mymap[1][1][l];
                mymap[4][0][l]=mymap[1][0][l];
                mymap[1][2][l]=mymap[2][2][l];
                mymap[1][1][l]=mymap[2][1][l];
                mymap[1][0][l]=mymap[2][0][l];
                mymap[2][2][l]=temp[0];
                mymap[2][1][l]=temp[1];
                mymap[2][0][l]=temp[2];
            }
            else if(var[1]=='-'){//반시계방향 앞(2)->위(0)->뒤(4)->아래(1)
               int temp[3];
                temp[0]=mymap[0][2][l];
                temp[1]=mymap[0][1][l];
                temp[2]=mymap[0][0][l];
                mymap[0][2][l]=mymap[2][2][l];
                mymap[0][1][l]=mymap[2][1][l];
                mymap[0][0][l]=mymap[2][0][l];
                mymap[2][2][l]=mymap[1][2][l];
                mymap[2][1][l]=mymap[1][1][l];
                mymap[2][0][l]=mymap[1][0][l];
                mymap[1][2][l]=mymap[4][2][l];
                mymap[1][1][l]=mymap[4][1][l];
                mymap[1][0][l]=mymap[4][0][l];
                mymap[4][2][l]=temp[0];
                mymap[4][1][l]=temp[1];
                mymap[4][0][l]=temp[2];
            }
        }
        
        if(var[0]=='F'|| var[0]=='B'){  // 앞 뒤
            char temp[3]; // 0:위 3:오른 1: 아래 5:왼
            int l1,l2;
            if(var[0]=='F'){
                l1=2;
                l2=0;
            }
            else{
                l1=0;
                l2=2;
                if(var[1]=='-')
                    var[1]='+';
                else
                    var[1]='-';
            }
            if(var[1]=='-'){  //반시계
                temp[0]=mymap[0][l2][2];
                temp[1]=mymap[0][l2][1];
                temp[2]=mymap[0][l2][0];
                mymap[0][l2][2]=mymap[3][l1][0];
                mymap[0][l2][1]=mymap[3][l1][1];
                mymap[0][l2][0]=mymap[3][l1][2];
                mymap[3][l1][0]=mymap[1][l1][0];
                mymap[3][l1][1]=mymap[1][l1][1];
                mymap[3][l1][2]=mymap[1][l1][2];
                mymap[1][l1][0]=mymap[5][l1][0];
                mymap[1][l1][1]=mymap[5][l1][1];
                mymap[1][l1][2]=mymap[5][l1][2];
                mymap[5][l1][0]=temp[0];
                mymap[5][l1][1]=temp[1];
                mymap[5][l1][2]=temp[2];
            }
            else{ //시계
                temp[0]=mymap[0][l2][2];
                temp[1]=mymap[0][l2][1];
                temp[2]=mymap[0][l2][0];
                mymap[0][l2][2]=mymap[5][l1][0];
                mymap[0][l2][1]=mymap[5][l1][1];
                mymap[0][l2][0]=mymap[5][l1][2];
                mymap[5][l1][0]=mymap[1][l1][0];
                mymap[5][l1][1]=mymap[1][l1][1];
                mymap[5][l1][2]=mymap[1][l1][2];
                mymap[1][l1][0]=mymap[3][l1][0];
                mymap[1][l1][1]=mymap[3][l1][1];
                mymap[1][l1][2]=mymap[3][l1][2];
                mymap[3][l1][0]=temp[0];
                mymap[3][l1][1]=temp[1];
                mymap[3][l1][2]=temp[2];
            }
        }
        if(var[0]=='U'||var[0]=='D'){ //앞면:2 오른쪽면:3 뒷면:4 왼쪽면:5
            //앞면: row=2 col=0,1,2
            //오른쪽면: col=2 row=2,1,0
            //뒷면: row=0 col=2,1,0
            //왼쪽면: col=0 row=0,1,2
            //시계방향
            int l1,l2;
            if(var[0]=='U'){
                l1=2;
                l2=0;
            }
            
            else{
                l1=0;
                l2=2;
                if(var[1]=='-')
                    var[1]='+';
                else
                    var[1]='-';
            }
            if(var[1]=='+'){//앞면:2 오른쪽면:3 뒷면:4 왼쪽면:5
                int temp[3];
                temp[0]=mymap[2][l1][0];
                temp[1]=mymap[2][l1][1];
                temp[2]=mymap[2][l1][2];
                mymap[2][l1][0]=mymap[3][2][l1];
                mymap[2][l1][1]=mymap[3][1][l1];
                mymap[2][l1][2]=mymap[3][0][l1];
                mymap[3][2][l1]=mymap[4][l2][2];
                mymap[3][1][l1]=mymap[4][l2][1];
                mymap[3][0][l1]=mymap[4][l2][0];
                mymap[4][l2][2]=mymap[5][0][l2];
                mymap[4][l2][1]=mymap[5][1][l2];
                mymap[4][l2][0]=mymap[5][2][l2];
                mymap[5][0][l2]=temp[0];
                mymap[5][1][l2]=temp[1];
                mymap[5][2][l2]=temp[2];
            }
            if(var[1]=='-'){
                int temp[3];
                temp[0]=mymap[2][l1][0];
                temp[1]=mymap[2][l1][1];
                temp[2]=mymap[2][l1][2];
                mymap[2][l1][0]=mymap[5][0][l2];
                mymap[2][l1][1]=mymap[5][1][l2];
                mymap[2][l1][2]=mymap[5][2][l2];
                mymap[5][0][l2]=mymap[4][l2][2];
                mymap[5][1][l2]=mymap[4][l2][1];
                mymap[5][2][l2]=mymap[4][l2][0];
                mymap[4][l2][2]=mymap[3][2][l1];
                mymap[4][l2][1]=mymap[3][1][l1];
                mymap[4][l2][0]=mymap[3][0][l1];
                mymap[3][2][l1]=temp[0];
                mymap[3][1][l1]=temp[1];
                mymap[3][0][l1]=temp[2];
            }
        }
        //위 아래 앞 오 뒷 왼
        for(int i=2;i>=0;i--){
            for(int j=0;j<3;j++)
                cout<<mymap[0][i][j]<<" ";
            cout<<"\n";
        }
        cout<<"\n";
        
        
    }
    return 0;
}
