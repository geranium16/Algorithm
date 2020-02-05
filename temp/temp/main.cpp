#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 18
int n;
int mymap[MAX][MAX];
vector <pair<int,int>> team1;
vector <pair<int,int>> team2;
vector <int> var1;
vector<int> var2;

bool visited[MAX];
int sol=987987987;
int a=0;
void permutation(){
    for(int i=0;i<var1.size()-1;i++){
        for(int j=i+1;j<var1.size();j++){
            team1.push_back({var1[i],var1[j]});
            team1.push_back({var1[j],var1[i]});
            team2.push_back({var2[i],var2[j]});
            team2.push_back({var2[j],var2[i]});
            
        }
        
    }
}
void cal(){
    int a=0,b=0;
    for(int i=0;i<team1.size();i++){
        a+=mymap[team1[i].first][team1[i].second];
        b+=mymap[team2[i].first][team2[i].second];
        //        cout<<"i :"<<i<<"식재료1: "<<team1[i].first<<", "<<team1[i].second<<"\n";
        //        cout<<"i :"<<i<<"식재료2: "<<team2[i].first<<", "<<team2[i].second<<"\n";
    }
    
    //  cout<<a<<" "<<b<<"\n";
    if(abs(a-b)<sol)
        sol=abs(a-b);
}
void combination(int idx,int cnt){
    if(idx>=n/2){
        for(int i=0;i<n;i++){
            if(!visited[i])
                var2.push_back(i);
        }
        //        for(int i=0;i<var1.size();i++){
        //            cout<<var1[i]<<", "<<var2[i]<<"\n";
        //        }
        permutation();
        cal();
        var2.clear();
        team1.clear();
        team2.clear();
        
        return;
        
    }
    
    
    for(int i=cnt;i<(n/2)+idx;i++){
        if(!visited[i]){
            var1.push_back(i);
            visited[i]=true;
            combination(idx+1,i+1);
            var1.pop_back();
            visited[i]=false;
            
        }
    }
}
void init(){
    sol=987987987;
    team1.clear();
    team2.clear();
    var1.clear();
    var2.clear();
}
int main(){
    
    int tc;
  
    cin>>tc;

    for(int t=1;t<=tc;t++){
        init();
        cin>>n;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>mymap[i][j];
      
            }
        }
        combination(0,0);
        cout<<"#"<<t<<" "<<sol<<"\n";
    }
}
