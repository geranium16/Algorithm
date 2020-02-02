#include <iostream>
using namespace std;

#define MAX 23

bool mymap[MAX][MAX];
int n,m;

int cal(int x){
    return x*x+(x-1)*(x-1);
}
bool range(int x,int y){
    return 0<=x && x<n && 0<=y && y<n;
}
int confirm(int k,int x,int y){
    
    int num=0;
    
    for(int i=0;i<2*k-1;i++){
        if(range(x-k+1+i,y)&&mymap[y][x-k+1+i])
            num++;
    }
    
    for(int i=1;i<k;i++){
        for(int j=0;j<2*(k-i)-1;j++){
            if(range(x-k+1+i+j,y-i) && mymap[y-i][x-k+1+i+j])
                num++;
            if(range(x-k+1+i+j,y+i) && mymap[y+i][x-k+1+i+j])
                num++;
        }
    }
    if(cal(k)<=num*m)
        return num;
    else
        return 0;
}

int simulation(int k){
    int cmax=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int c=confirm(k,j,i);
            if(cmax<c)
                cmax=c;
        }
    }
    return cmax;
}


int main(){

   
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        int numofhome=0;
        int totalmax=0;
        cin>>n>>m;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>mymap[i][j];
                if(mymap[i][j])
                    numofhome++;
            }
        }
        
        for(int i=n+1;i>0;i--){
            if(cal(i)<numofhome*m){
                int totalc=simulation(i);
                if(totalmax<totalc)
                    totalmax=totalc;
            }
            
        }
        cout<<"#"<<t<<" "<<totalmax<<"\n";
    }
    
}
