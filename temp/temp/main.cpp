#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAX=55;


int mymap[MAX][MAX];
int copy_map[MAX][MAX];
int n,m,k; // k=회전 횟수
vector <int> row; //row
vector <int> col; //co
vector <int> s; // 칸수
vector <vector<int>> per;
vector <int> temp;

bool visited[7];
int sol=987987987;
int calculate(){
    int sum=987987987;
    for(int i=1;i<=n;i++){
        int temp_sum=0;
        for(int j=1;j<=m;j++){
            temp_sum+=copy_map[i][j];
            //cout<<copy_map[i][j]<<" ";
        }
    
       // cout<<temp_sum<<"\n";
        sum=min(sum,temp_sum);
    }
    return sum;
}
void simulation(int row_s, int row_e, int col_s, int col_e,int totalcnt,int cnt){
    
    if(cnt>=totalcnt)
        return;
        

    int temp=copy_map[row_s][col_s];
    for(int i=row_s;i<row_e;i++) // col=col_s 고정
        copy_map[i][col_s] = copy_map[i+1][col_s];
    
    for(int i=col_s;i<col_e;i++) // row=row_e-1 고정
        copy_map[row_e][i]=copy_map[row_e][i+1];
    
    for(int i=row_e;i>row_s;i--) // col=col_e-1 고정
        copy_map[i][col_e]=copy_map[i-1][col_e];
    
    for(int i=col_e;i>col_s;i--) // row=row_s 고정
        copy_map[row_s][i]=copy_map[row_s][i-1];
    copy_map[row_s][col_s+1]=temp;
    
    simulation(row_s+1,row_e-1,col_s+1,col_e-1,totalcnt,cnt+1);
}

void permutation(int cnt){
    if(cnt>=k){
        per.push_back(temp);
        return;
    }
    for(int i=0;i<k;i++){
        if(!visited[i]){
            visited[i]=true;
            temp.push_back(i);
            permutation(cnt+1);
            temp.pop_back();
            visited[i]=false;
        }
    }
}

int main(){
    cin>>n>>m>>k;
    for(int i=0;i<k;i++){
        vector<int> element;
        
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            cin>>mymap[i][j];
    }
    
    for(int i=0;i<k;i++){
        int a,b,c;
        cin>>a>>b>>c;
        row.push_back(a);
        col.push_back(b);
        s.push_back(c);
    }
    permutation(0);
    
    for(int j=0;j<per.size();j++){
        memcpy(copy_map,mymap,sizeof(mymap));
        for(int i=0;i<k;i++)
          simulation(row[per[j][i]]-s[per[j][i]],row[per[j][i]]+s[per[j][i]],col[per[j][i]]-s[per[j][i]],col[per[j][i]]+s[per[j][i]],s[per[j][i]],0);
        
        int ans=calculate();
        if(sol>ans)
            sol=ans;
    }
    cout<<sol;
    
}

