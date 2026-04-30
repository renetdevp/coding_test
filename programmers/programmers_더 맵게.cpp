#include <string>
#include <vector>
#include <queue>

using namespace std;

struct CompareAscent {
    bool operator()(int a, int b){
        return a>b;
    }
};

using MinHeap = priority_queue<int, vector<int>, CompareAscent>;

void mix(MinHeap &pq){
    if (pq.empty() || pq.size() < 2) return;

    int first = pq.top(); pq.pop();
    int second = pq.top(); pq.pop();
    
    pq.push(first + second*2);
}

bool check(MinHeap &pq, int K){
    if (pq.empty()) return false;
    if (pq.top() < K) return false;
    
    return true;
}

int solution(vector<int> scoville, int K) {
    int answer = -1;
    MinHeap pq;
    
    for (const auto &s: scoville){
        pq.push(s);
    }
    
    int i=0;
    while (!pq.empty() && pq.size() >= 2){
        if (check(pq, K)){
            answer = i;
            break;
        }
        
        mix(pq);
        ++i;
    }
    if (check(pq, K)) answer = i;   // 모든 음식을 섞은 마지막 한 음식이 K 이상일 경우
    
    return answer;
}