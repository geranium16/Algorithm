#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX1 10
#define MAX2 1020
int n,m,k,a,b;

vector <int> receipt_t;
vector <int> repair_t;

int people_t[MAX2];
bool visited[MAX2]={false,};

queue <int> wait_1;
queue <int> wait_2;

vector <pair<int,int>> repair_c[MAX1];
vector <pair<int,int>> receipt_c[MAX1];

vector <int> finish;
int sol[MAX2]={0,};

//핵심: 먼저 도착할수록 , 고객번호가 앞설수록 = 먼저 접수 = queue
void visite_f(){ //고객 이동 시간 완료시: 완료시 접수창구로 넘기기
    for(int i=0;i<k;i++){
        if(people_t[i]>0)
            people_t[i]--;
        else if(!visited[i]){ // 고객이 이동이 완료한 경우
            visited[i]=true;
            wait_1.push(i);
        }
    }
}

void receipt_f(){
    //접수창구에서 빼내는 로직을 모두 진행한 후 접수창구에 넣는 로직을 진행 해야 한다.
    for(int i=0;i<n;i++){
        if(!receipt_c[i].empty()){
            receipt_c[i][0].second--;
            if(receipt_c[i][0].second==0){
                wait_2.push(receipt_c[i][0].first);
                receipt_c[i].pop_back();
            }
        }
    }
    for(int i=0;i<n;i++){
        if(wait_1.empty())
            break;
        if(receipt_c[i].empty()){
            if(i==a-1)
                sol[wait_1.front()]++;
            receipt_c[i].push_back({wait_1.front(),receipt_t[i]});
            wait_1.pop();
        }
    }
}

void repair_f(){
    
    for(int i=0;i<m;i++){
        if(!repair_c[i].empty()){
            repair_c[i][0].second--;
            if(repair_c[i][0].second==0){
                finish.push_back(repair_c[i][0].first);
                repair_c[i].pop_back();
            }
        }
    }
    
    for(int i=0;i<m;i++){
        if(wait_2.empty())
            break;
        if(repair_c[i].empty()){
            if(i==b-1)
                sol[wait_2.front()]++;
            
            repair_c[i].push_back({wait_2.front(),repair_t[i]});
            wait_2.pop();
        }
        
    }
    
}
void simulation(){
    if(finish.size()>=k) //고객들 모두 처리하면 끝
        return;
    visite_f();
    receipt_f();
    repair_f();
    simulation();
    
}
void init(){

    receipt_t.clear();
    repair_t.clear();
    while( !wait_1.empty() ) wait_1.pop();
    while( !wait_2.empty() ) wait_2.pop();
    finish.clear();
    fill_n(sol,MAX2,0);
    fill_n(people_t,MAX2,0);
    fill_n(visited,MAX2,false);
    for(int i=0;i<MAX1;i++){
        receipt_c[i].clear();
        repair_c[i].clear();
        
    }
}

int main(){
    
    int tc;
    cin>>tc;
    
    for(int t=1;t<=tc;t++){
        init();
        
        cin>>n>>m>>k>>a>>b;

//        접수창구: 창구 별 소요 시간
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            receipt_t.push_back(x);
        }
//        수리창구: 창구 별 소요 시간
        for(int i=0;i<m;i++){
            int x;
            cin>>x;
            repair_t.push_back(x);
        }
//        고객: 고객 별 소요 시간
        for(int i=0;i<k;i++){
            cin>>people_t[i];
        }
        
        simulation();
        
        int real_sol=0;
        for(int i=0;i<k;i++){
            if(sol[i]==2){
                real_sol+=i+1;
            }
        }
        
        
        if(real_sol==0)
            cout<<"#"<<t<<" "<<-1<<"\n";
        else
            cout<<"#"<<t<<" "<<real_sol<<"\n";
    }
}
