#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 23

int n,m,k,a,b;
vector <int> receipt_t;
vector <int> repair_t;
vector <int> time_p;
vector <pair<int,int>> receipt_f[MAX];
vector <pair<int,int>> repair_f[MAX];
vector <int> people_1;
vector<int> people_2;
int cnt=0;
bool sol[MAX]={false,};

void receipt_function(int& cnt){
    sort(people_1.begin(),people_1.end(),dec);
    
    for(int i=0;i<n;i++){ //모든 창구 검사
        if(!receipt_f[i].empty()){ //창구가 누가있으면
            if(receipt_f[i].front().second==0){//완료되면
                people_2.push_back(receipt_f[i].front().first); //정비로 넣기 위한
                if(i==a)
                    sol[receipt_f[i].front().first]=true;
                receipt_f[i].pop_back();
            }
            
            else
                receipt_f[i].front().second--; //창구 시간 줄이기
        }
        
        else{
            for(int j=0;j<people_1.size();j++){
                receipt_f[i].push_back({people_1.back(),receipt_t[i]});
                people_1.pop_back();
            }
        }
    }
}

void repair_function(int& cnt){
    sort(people_2.begin(),people_2.end(),dec);
    for(int i=0;i<m;i++){
        if(!repair_f[i].empty()){ //창구가 피어있지 않으면
            repair_f[i].front().second--; //시간 줄이기
            if(receipt_f[i].front().second==0){ //시간 다되면 비워주기
                if(i==b){
                    if(!sol[receipt_f[i].front().first])
                        sol[receipt_f[i].front().first]=false;
                }
                receipt_f[i].pop_back();
                cnt++;
            }
        }
        else{ //칭구가 비어있으면 넣을 사람 있는지 확인
            for(int j=0;j<people_2.size();j++){
                receipt_f[i].push_back({people_2.back(),receipt_t[i]});
                people_2.pop_back();
            }
        }
    }
}
void DFS(int cnt){
    
    if(cnt>=k)
        return;
    
    for(int i=k-1;i>=0;i--){
        
        time_p[i]--;
        if(time_p[i]<=0){
            time_p.erase(time_p.begin()+i);
            people_1.push_back(i);
        }
    }
    
    receipt_function(cnt);
    repair_function(cnt);
        
    DFS(cnt);
}
int main(){
    cin>>n>>m>>k>>a>>b;
    for(int i=0;i<n;i++){
        int x;
        receipt_t.push_back(x);
    }
    for(int i=0;i<m;i++){
        int x;
        repair_t.push_back(x);
    }
    for(int i=0;i<k;i++){
        int x;
        time_p.push_back(x);
    }
    DFS(0);
    for(int i=1;i<k;i++){
        if(sol[i])
            cout<<i+1;
    }
}
