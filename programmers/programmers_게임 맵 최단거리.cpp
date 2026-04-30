#include <vector>
#include <queue>

using namespace std;

int h, w;

bool checkRegion(const vector<vector<int>> &maps, int y, int x){
    if (y < 0 || y >= h) return false;
    if (x < 0 || x >= w) return false;
    if (!maps[y][x]) return false;
    
    return true;
}

int bfs(const vector<vector<int>> &maps){
    queue<pair<int, int>> q;
    vector<bool> visited(h*w);
    char dy[4] = { -1, 0, 1, 0 };
    char dx[4] = { 0, 1, 0, -1 };
    
    q.push({ 0, 1 });
    visited[0] = true;
    
    while (!q.empty()){
        pair<int, int> p = q.front();
        q.pop();
        
        for (char i=0; i<4; ++i){
            char ty = p.first/w + dy[i];
            char tx = p.first%w + dx[i];

            if (!checkRegion(maps, ty, tx)) continue;
            if (visited[ty*w + tx]) continue;
            
            if (ty*w + tx == h*w-1){
                return p.second+1;
            }

            q.push({ ty*w + tx, p.second+1 });
            visited[ty*w + tx] = true;
        }
    }
    
    return -1;
}

int solution(vector<vector<int>> maps)
{
    int answer = 0;
    
    h = maps.size(); w = maps[0].size();
    
    answer = bfs(maps);
    
    return answer;
}