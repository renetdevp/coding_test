#include <string>
#include <vector>
#include <queue>

using namespace std;

int h, w;

bool checkPosition(const vector<string> &board, char y, char x){
    if (y < 0 || y >= h) return false;
    if (x < 0 || x >= w) return false;
    if (board[y][x] == 'D') return false;
    
    return true;
}

pair<int, int> getPosition(const vector<string> &board){
    pair<int, int> result;
    
    result = { -1, -1 };

    for (int i=0; i<h; ++i){
        for (int j=0; j<w; ++j){
            if (board[i][j] == 'R') result.first = i*w + j;
            if (board[i][j] == 'G') result.second = i*w + j;
            
            if (result.first != -1 && result.second != -1){
                return result;
            }
        }
    }
}

void move(const vector<string> &board, queue<pair<int, int>> &q, vector<bool> &visited){
    pair<int, int> qf = q.front();
    char dy[4] = { -1, 0, 1, 0 };
    char dx[4] = { 0, 1, 0, -1 };
    
    for (char i=0; i<4; ++i){
        char ty = qf.first / w;
        char tx = qf.first % w;

        while (checkPosition(board, ty+dy[i], tx+dx[i])){
            ty += dy[i]; tx += dx[i];
        }
        
        if (visited[ty*w + tx]) continue;
        
        q.push({ ty*w + tx, qf.second+1 });
        visited[ty*w + tx] = 1;
    }
}

int bfs(const vector<string> &board){
    vector<bool> visited(h*w, false);
    queue<pair<int, int>> q;
    pair<int, int> position = getPosition(board);
    
    q.push({ position.first, 0});
    visited[position.first] = true;
    
    while (!q.empty()){
        if (q.front().first == position.second){
            return q.front().second;
        }

        move(board, q, visited);
        q.pop();
    }
    
    return -1;
}

int solution(vector<string> board) {
    int answer = 0;
    
    h = board.size(); w = board[0].size();

    answer = bfs(board);
    
    return answer;
}