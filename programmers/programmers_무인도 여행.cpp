#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int h, w;

bool checkRegion(int y, int x){
    if (y < 0 || y >= h) return false;
    if (x < 0 || x >= w) return false;
    
    return true;
}

int bfs(vector<string> &maps, vector<bool> &visited, int p){
    queue<int> q;
    int sum = 0;
    char dy[4] = { -1, 0, 1, 0 };
    char dx[4] = { 0, 1, 0, -1 };
    
    q.push(p);
    visited[p] = true;
    
    while (!q.empty()){
        int y = q.front()/w;
        int x = q.front()%w;

        q.pop();

        for (char i=0; i<4; ++i){
            char ty = y + dy[i];
            char tx = x + dx[i];

            if (!checkRegion(ty, tx)) continue;
            if (maps[ty][tx] == 'X') continue;
            if (visited[ty*w + tx]) continue;

            q.push(ty*w + tx);
            visited[ty*w + tx] = true;
        }
        
        sum += maps[y][x] - '0';
    }
    
    return sum;
}

vector<int> solution(vector<string> maps) {
    vector<int> answer;

    h = maps.size(); w = maps[0].size();

    vector<bool> visited(h*w, false);
    
    for (int i=0; i<maps.size(); ++i){
        for (int j=0; j<maps[0].size(); ++j){
            if (maps[i][j] == 'X') continue;
            if (visited[i*w + j]) continue;
            
            answer.push_back(bfs(maps, visited, i*w + j));
        }
    }
    
    if (answer.empty()) answer.push_back(-1);
    else sort(answer.begin(), answer.end());

    return answer;
}