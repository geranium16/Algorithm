#include <iostream>
#include <algorithm>
#include <memory.h>
#include <queue>
using namespace std;
  
#define BASE 200
  
struct p {
    int r, x, y;
};
  
int t, tc;
int N, M, K;
int map[500][500];
int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };
  
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> t;
    for (tc = 1; tc <= t; ++tc) {
        memset(map, 0, sizeof(map));
        cin >> N >> M >> K;
        // remain_time, value, x, y
        queue<p> q[11];
        int ans = 0;
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
            cin >> map[i + BASE][j + BASE];
            if (map[i + BASE][j + BASE]) {
                q[map[i + BASE][j + BASE]].push({ 2*map[i + BASE][j + BASE], i + BASE, j + BASE });
            }
        }
        int s = 0;
        for (int i = 0; i <= K; ++i) {
            for (int j = 10; j >= 1; --j) {
                int siz = q[j].size();
                for (int k = 0; k < siz; ++k) {
                    auto x = q[j].front();
                    q[j].pop();
                    if (x.r > j) {
                        if (map[x.x][x.y] > 0) {
                            ans++;
                            map[x.x][x.y] = -map[x.x][x.y];
                        }
                        q[j].push({ x.r - 1,x.x,x.y });
                    }
                    else if (x.r == j) {
                         
                        q[j].push({ j - 1,x.x,x.y });
                        for (int l = 0; l < 4; ++l) {
                            int nx = x.x + dx[l];
                            int ny = x.y + dy[l];
                            if (map[nx][ny]) continue;
                            map[nx][ny] = j;
                            q[j].push({ 2*j,nx,ny });
                        }
                    }
                    else if (j > x.r && x.r) {
                        q[j].push({ x.r - 1,x.x,x.y });
                    }
                    else
                        ans--;
                }
            }
        }
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}
