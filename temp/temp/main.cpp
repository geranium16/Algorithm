#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n;
char U[3][3],D[3][3],F[3][3],B[3][3],L[3][3],R[3][3];
vector <pair<char,char>> command;
void rotation(char (*mymap)[3]){ //OK
    char copy_map[3][3];
    memcpy(copy_map,mymap,sizeof(copy_map));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            mymap[i][j]=copy_map[2-j][i];
        }
    }
}
void reverse_rotation(char (*mymap)[3]){ //OK
    char copy_map[3][3];
    memcpy(copy_map,mymap,sizeof(copy_map));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            mymap[i][j]=copy_map[j][2-i];
        }
    }
}

void simulation(){
    for(int i=0;i<command.size();i++){
        if(command[i].first=='U' && command[i].second=='+'){
            char temp[3][3];
            memcpy(temp,F,sizeof(temp));
            for(int i=0;i<3;i++){
                F[0][i]=R[0][i];
                R[0][i]=B[0][i];
                B[0][i]=L[0][i];
                L[0][i]=temp[0][i];
            }
            rotation(U);
        }
        else if(command[i].first=='U' && command[i].second=='-'){
            char temp[3][3];
            memcpy(temp,F,sizeof(temp));
            for(int i=0;i<3;i++){
                F[0][i]=L[0][i];
                L[0][i]=B[0][i];
                B[0][i]=R[0][i];
                R[0][i]=temp[0][i];
            }
            reverse_rotation(U);
        }
        else if(command[i].first=='D' && command[i].second=='+'){
            char temp[3][3];
            memcpy(temp,F,sizeof(temp));
            for(int i=0;i<3;i++){
                F[2][i]=L[2][i];
                L[2][i]=B[2][i];
                B[2][i]=R[2][i];
                R[2][i]=temp[2][i];
            }
            rotation(D);
        }
        else if(command[i].first=='D' && command[i].second=='-'){
            char temp[3][3];
            memcpy(temp,F,sizeof(temp));
            for(int i=0;i<3;i++){
                F[2][i]=R[2][i];
                R[2][i]=B[2][i];
                B[2][i]=L[2][i];
                L[2][i]=temp[2][i];
            }
            reverse_rotation(D);
        }
        else if(command[i].first=='F' && command[i].second=='+'){
            char temp[3][3];
            memcpy(temp,U,sizeof(temp));
            for(int i=0;i<3;i++){
                U[2][i]=L[2-i][2];
                L[2-i][2]=D[0][2-i];
                D[0][2-i]=R[i][0];
                R[i][0]=temp[2][i];
            }
            rotation(F);
        }
        else if(command[i].first=='F' && command[i].second=='-'){
            char temp[3][3];
            memcpy(temp,U,sizeof(temp));
            for(int i=0;i<3;i++){
                U[2][i]=R[i][0];;
                R[i][0]=D[0][2-i];
                D[0][2-i]=L[2-i][2];
                L[2-i][2]=temp[2][i];
            }
            reverse_rotation(F);
        }
        else if(command[i].first=='B' && command[i].second=='+'){
            char temp[3][3];
            memcpy(temp,R,sizeof(temp));
            for(int i=0;i<3;i++){
                R[2-i][2]=D[2][i];
                D[2][i]=L[i][0];
                L[i][0]=U[0][2-i];
                U[0][2-i]=temp[2-i][2];
            }
            rotation(B);
        }
        else if(command[i].first=='B' && command[i].second=='-'){
            char temp[3][3];
            memcpy(temp,R,sizeof(temp));
            for(int i=0;i<3;i++){
                R[2-i][2]=U[0][2-i];
                U[0][2-i]=L[i][0];
                L[i][0]=D[2][i];
                D[2][i]=temp[2-i][2];
            }
            reverse_rotation(B);
        }
        else if(command[i].first=='L' && command[i].second=='+'){
            char temp[3][3];
            memcpy(temp,U,sizeof(temp));
            for(int i=0;i<3;i++){
                U[i][0]=B[2-i][2];
                B[2-i][2]=D[i][0];
                D[i][0]=F[i][0];
                F[i][0]=temp[i][0];
            }
            rotation(L);
        }
        else if(command[i].first=='L' && command[i].second=='-'){
            char temp[3][3];
            memcpy(temp,U,sizeof(temp));
            for(int i=0;i<3;i++){
                U[i][0]=F[i][0];
                F[i][0]=D[i][0];
                D[i][0]=B[2-i][2];
                B[2-i][2]=temp[i][0];
            }
            reverse_rotation(L);
        }
        else if(command[i].first=='R' && command[i].second=='+'){
            char temp[3][3];
            memcpy(temp,U,sizeof(temp));
            for(int i=0;i<3;i++){
                U[i][2]=F[i][2];
                F[i][2]=D[i][2];
                D[i][2]=B[2-i][0];
                B[2-i][0]=temp[i][2];
            }
            rotation(R);
        }
        else if(command[i].first=='R' && command[i].second=='-'){
            char temp[3][3];
            memcpy(temp,U,sizeof(temp));
            for(int i=0;i<3;i++){
                U[i][2]=B[2-i][0];
                B[2-i][0]=D[i][2];
                D[i][2]=F[i][2];
                F[i][2]=temp[i][2];
            }
            reverse_rotation(R);
        }
    }
}

int main(){
    int tc;
    cin>>tc;
    for(int t=0;t<tc;t++){
        cin>>n;
        command.clear();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                U[i][j]='w';
                D[i][j]='y';
                L[i][j]='g';
                F[i][j]='r';
                R[i][j]='b';
                B[i][j]='o';
            }
        }
        for(int i=0;i<n;i++){
            char a,b;
            cin>>a>>b;
            command.push_back({a,b});
        }
        simulation();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cout<<U[i][j];
            }
            cout<<"\n";
        }
    }
}
