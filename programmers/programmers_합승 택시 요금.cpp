#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Vertex {
    vector<pair<int, int>> edges;
};

struct ComparePrice {
    bool operator()(pair<int, int> &a, pair<int, int> &b){
        return a.second > b.second;
    }
};

vector<Vertex> getVertices(vector<vector<int>> &fares, int &n){
    vector<Vertex> vertices(n);

    for (const auto &fare: fares){
        vertices[fare[0]-1].edges.push_back({ fare[1], fare[2] });
        vertices[fare[1]-1].edges.push_back({ fare[0], fare[2] });
    }
    
    return vertices;
}

vector<int> getDistances(vector<Vertex> &vertices, int &start, int &n){
    priority_queue<pair<int, int>, vector<pair<int, int>>, ComparePrice> pq;
    vector<int> distances(n, ~(1<<31));
    
    pq.push({ start, 0 });
    distances[start-1] = 0;
    
    while (!pq.empty()){
        pair<int, int> p = pq.top();
        pq.pop();
        
        if (distances[p.first-1] < p.second) continue;

        for (const auto &edge: vertices[p.first-1].edges){
            int nd = distances[p.first-1] + edge.second;

            if (distances[edge.first-1] <= nd) continue;

            distances[edge.first-1] = nd;

            pq.push({
                edge.first,
                nd
            });
        }
    }
    
    return distances;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    vector<Vertex> vertices = getVertices(fares, n);
    vector<int> distances_s = getDistances(vertices, s, n);
    vector<int> distances_a = getDistances(vertices, a, n);
    vector<int> distances_b = getDistances(vertices, b, n);
    
    answer = distances_s[a-1] + distances_s[b-1];

    for (int i=0; i<n; ++i){
        answer = min(answer, distances_s[i] + distances_a[i] + distances_b[i]);
    }
    
    return answer;
}