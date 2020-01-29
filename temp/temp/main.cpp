

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


/*
 1.
 
 
 */





#define MAX 105

int n; //셀의개수
int m; //결리시간
int k; //미생물군집의 수
long int sol=0;
class bugs{
public:
    pair<int,int> node;
    int num;
    int dir;
    bool live=true;
    bugs(pair<int,int> node,int num,int dir) : node(node),num(num),dir(dir){};
    
};

vector<int> mymap[MAX][MAX];
vector<bugs> mybugs;
pair<int,int> dir[4]={{-1,0},{1,0},{0,-1},{0,1}};
int dir2[4]={1,0,3,2};


bool range(pair<int,int> node){
    return 1<=node.first && node.first<n-1 && 1<=node.second && node.second<n-1;
}

/*
 
 1/최초
 2. 한시간마다 이동
 3.약품에 도착시 절반이 죽고, 이동방향 반개 , 홀수=소수점버림
 4. 두개이상의 군집이 모이면 합침, 미생물 수가 많은 군집의 방향을 따라감
 */

void DFS(int idx){
    
    if(idx>=m){
        
        for(int i=0;i<mybugs.size();i++){
            if(mybugs[i].live)
                sol+=mybugs[i].num;
        }
        return;
    }
    for(int i=0;i<mybugs.size();i++){
        if(mybugs[i].live){
            for(int j=0;j<mymap[mybugs[i].node.first][mybugs[i].node.second].size();j++){
                if(mymap[mybugs[i].node.first][mybugs[i].node.second][j]==i){
                    mymap[mybugs[i].node.first][mybugs[i].node.second].erase(mymap[mybugs[i].node.first][mybugs[i].node.second].begin()+j);
                    break;
                }
            }
            mybugs[i].node.first+=dir[mybugs[i].dir].first;
            mybugs[i].node.second+=dir[mybugs[i].dir].second;
            mymap[mybugs[i].node.first][mybugs[i].node.second].push_back(i);
        }
    }
    
    for(int i=0;i<mybugs.size();i++){
        if(mybugs[i].live){
            //cout<<"size"<<i<<" "<<mymap[mybugs[i].node.first][mybugs[i].node.second].size()<<" "<<"\n";
            if(mymap[mybugs[i].node.first][mybugs[i].node.second].size()>1){
               // cout<<"a";
                bugs current= bugs({mybugs[i].node.first,mybugs[i].node.second},0,0);
                int temp=0;
                for(int j=0;j<mymap[mybugs[i].node.first][mybugs[i].node.second].size();j++){
                    current.num+=mybugs[mymap[mybugs[i].node.first][mybugs[i].node.second][j]].num;
                    mybugs[mymap[mybugs[i].node.first][mybugs[i].node.second][j]].live=false;
                    if(temp<mybugs[mymap[mybugs[i].node.first][mybugs[i].node.second][j]].num){
                        temp=mybugs[mymap[mybugs[i].node.first][mybugs[i].node.second][j]].num;
                        current.dir=mybugs[mymap[mybugs[i].node.first][mybugs[i].node.second][j]].dir;
                    }
                    
                        
                }
                mymap[mybugs[i].node.first][mybugs[i].node.second].clear();
                mymap[mybugs[i].node.first][mybugs[i].node.second].push_back(i);
                mybugs[i]=current;
            }
            else if(!range(mybugs[i].node)){
               // cout<<i<<"c";
                mybugs[i].num/=2;
                if(mybugs[i].num<=0){
                    mybugs[i].live=false;
                    for(int j=0;j<mymap[mybugs[i].node.first][mybugs[i].node.second].size();j++){ //없어서 1개 못맞춤
                        if(mymap[mybugs[i].node.first][mybugs[i].node.second][j]==i){
                            mymap[mybugs[i].node.first][mybugs[i].node.second].erase(mymap[mybugs[i].node.first][mybugs[i].node.second].begin()+j);
                            break;
                        }
                    }
                    
                }
                
                mybugs[i].dir=dir2[mybugs[i].dir];
            }
        }
        
    }
    DFS(idx+1);
}
void init(){
    
    mybugs.clear();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            mymap[i][j].clear();
        
    }
    sol=0;
    
}
int main(){
    int testcase;
    cin>>testcase;
    for(int t=1;t<=testcase;t++){
        init();
        cin>>n>>m>>k;
        for(int i=0;i<k;i++){
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            mybugs.push_back(bugs({a,b},c,d-1));
            mymap[a][b].push_back(i); // 0번부터가 아닌 1번부터 시작
            
        }
        DFS(0);
        cout<<sol<<"\n";
    }
    
}

