#include <string>
#include <vector>
#include <queue>

using namespace std;

int N;

int bfs(vector<vector<int>> &table, vector<vector<int>> &wires, int &i){
    queue<int> q;
    vector<int> visited(N, 0);

    q.push(0);
    visited[0] = 1;

    int cnt=0;
    while (q.size()){
        int src = q.front();
        q.pop();

        for (int j=0; j<N; ++j){
            if (!table[src][j]) continue;
            if (visited[j]) continue;
            if (src == wires[i][0]-1 && j == wires[i][1]-1) continue;
            if (src == wires[i][1]-1 && j == wires[i][0]-1) continue;

            q.push(j);
            visited[j] = 1;
        }

        ++cnt;
    }
    
    return cnt;
}

int solution(int n, vector<vector<int>> wires) {
    int answer = ~(1<<31);
    vector<vector<int>> table(n, vector<int>(n, 0));
    
    N = n;
    
    for (int i=0; i<wires.size(); ++i){
        table[wires[i][0]-1][wires[i][1]-1] = 1;
        table[wires[i][1]-1][wires[i][0]-1] = 1;
    }

    for (int i=0; i<wires.size(); ++i){
        answer = min(answer, abs(n-2*bfs(table, wires, i)));
    }
    
    return answer;
}