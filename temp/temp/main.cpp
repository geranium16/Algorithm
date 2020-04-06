#include <iostream>
using namespace std;
const int MAX=10;

int root[4][40]={{0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0,0,0,0,0},
    {10,13,16,19,25,30,35,40,0,0,0,0,0},
    {20,22,24,25,30,35,40,0,0,0,0,0},
    {30,28,27,26,25,30,35,40,0,0,0,0,0}
};
int mydata[MAX];
pair<int,int> horse[4]={{0,0},{0,0},{0,0},{0,0}};
bool horseflag[4]={false,};
int solution=0;


void change(int i){
    int value=root[horse[i].first][horse[i].second];
    if(horse[i].first==0){
        if(value==10)
            horse[i]={1,0};
        else if(value==20)
            horse[i]={2,0};
        else if(value==30)
            horse[i]={3,0};
    }
}

void simulation(int cnt,int value){
    if(cnt>=10){
        solution = solution > value ? solution : value;
        return;
    }
    
    bool flag=false;
    for(int i=0;i<4;i++){
        if(horseflag[i])
            continue;
        flag=true;
        pair<int,int> temp=horse[i];
        horse[i].second=horse[i].second+mydata[cnt];
        change(i);
        if(root[horse[i].first][horse[i].second]==0)
            horseflag[i]=true;
        
        if(!horseflag[i]){
            bool flag2=false;
            for(int j=0;j<4;j++){
                if(j==i||horseflag[j])
                    continue;
                
                else if(horse[i].first==horse[j].first && horse[i].second==horse[j].second){
                    flag2=true;
                    break;
                }
                
                else if(root[horse[i].first][horse[i].second]==root[horse[j].first][horse[j].second]){
                    int what=root[horse[i].first][horse[i].second];
                    if(what==25||what==35||what==40){
                        flag2=true;
                        break;
                    }
                    else if(what==30 && horse[j].second!=0 && horse[i].second!=0){
                        flag2=true;
                        break;
                    }
                }
            }
            if(flag2){
                horse[i]=temp;
                continue;
            }
        }
        simulation(cnt+1,value+root[horse[i].first][horse[i].second]);
        horseflag[i]=false;
        horse[i]=temp;
    }
    
    if(!flag)
        simulation(cnt+1,value);
}

int main(){
    for(int i=0;i<MAX;i++)
        cin>>mydata[i];
    simulation(0,0);
    cout<<solution;
    
}

