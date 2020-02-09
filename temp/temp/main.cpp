#include <iostream>
#include <vector>
using namespace std;
#define MAX 12

int n,m,c;
int mymap[MAX][MAX]={0,};
int mydata[MAX][MAX]={0,};



//최대 채취량을 구하는 로직 : n개의 배열중 모든 가능한 조합 도출
int cal(vector <int>& v,int idx,int sum,int real){
    if(sum>c) return 0; //최대채취량보다 크면 종료
    if(idx==v.size()) return real; //벌통채취완료시 종류
    return max(cal(v,idx+1,sum+v[idx],real+v[idx]*v[idx]),cal(v,idx+1,sum,real));
}
//각 노드를 시작점으로 하는 최대 채취량
void getMax(int x,int y){
    
    vector <int> v;
    for(int i=0;i<m;i++)
        v.push_back(mymap[x][y+i]);
    mydata[x][y]=cal(v,0,0,0);
}
int dfs(int x,int y){
    //같은 라인
    int ans=0;
    for(int i=y+m;i<n-m+1;i++){
        ans=max(ans,mydata[x][i]);
    }
    for(int i=x+1;i<n;i++){
        for(int j=0;j<n-m+1;j++)
            ans=max(ans,mydata[i][j]);
    }
    return ans;
}
int main(){
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        cin>>n>>m>>c;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>mymap[i][j];
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n-m+1;j++){
                getMax(i,j);
            }
        }
        //i,j를 선택한 상태에서 찾을수 있는 나머지에 대해
        //비교하여 최대값 찾는다.
        int sol = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - m + 1; j++) {
                sol = max(sol, dfs(i, j)+mydata[i][j]);
            }
        }
        
        cout<<"#"<<t<<" "<<sol<<"\n";
    }
}
