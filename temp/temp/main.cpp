#include <iostream>
#include <vector>
using namespace std;
const int MAX=12;
int n; //3<=n<=10
int m; //1<=m<=5; // 벌통의 개수 M
int c; //10<=c<=30; 한 사람이 꿀을 채취할 수 있는 최대 양
int mymap[MAX][MAX];
int solution=0;
int val2=0;
vector <int> comb;

void combination(int x,int y,int end,int cnt,int idx){
    if(end<=cnt){
        int sum1=0;
        int sum2=0;
        for(int i=0;i<comb.size();i++){
            sum1+=mymap[x][y+comb[i]];
            sum2+=mymap[x][y+comb[i]]*mymap[x][y+comb[i]];
        }
        if(sum1<=c) val2 = val2 > sum2 ? val2 : sum2;
        
        return ;
    }
    for(int i=idx;i<m;i++){
        comb.push_back(i);
        combination(x,y,end,cnt+1,i+1);
        comb.pop_back();
    }
}

void simulation(int sum,int cnt,int x,int y){
    
    if(cnt>=2){ //OK
        solution= solution > sum ? solution : sum;
        return;
    }
    
    for(int j=y;j<=n-m;j++){ //첫행
        int add=0;
        for(int k=1;k<=m;k++){
            val2=0;
            combination(x,j,k,0,0);
            add = add > val2 ? add : val2;
        }
        simulation(sum+add,cnt+1,x,j+m);
    }
    
    for(int i=x+1;i<n;i++){
        for(int j=0;j<=n-m;j++){
            int add=0;
            for(int k=1;k<=m;k++){
                val2=0;
                combination(i,j,k,0,0);
                add = add > val2 ? add : val2;
            }
            simulation(sum+add,cnt+1,i,j+m);
        }
    }
}

int main(){
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        solution=0;
        cin>>n>>m>>c;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cin>>mymap[i][j];
        }
        simulation(0,0,0,0);
        cout<<"#"<<t<<" "<<solution<<"\n";
    }
}
