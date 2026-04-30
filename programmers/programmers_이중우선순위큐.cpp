#include <string>
#include <vector>
#include <cstdlib>
#include <queue>

using namespace std;

using MaxHeap = priority_queue<pair<int, int>>;
using MinHeap = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>;

int hl = 0;
int i = 0;
MaxHeap maxHeap;
MinHeap minHeap;
vector<bool> deleted;

void insert(int n){
    maxHeap.push({ n, i });
    minHeap.push({ n, i++ });
    deleted.push_back(false);
    ++hl;
}

void removeDeletedElem(){
    while (deleted[maxHeap.top().second]){
        maxHeap.pop();
    }
    while (deleted[minHeap.top().second]){
        minHeap.pop();
    }
}

void deleteMax(){
    if (!hl) return;
    
    removeDeletedElem();

    deleted[maxHeap.top().second] = true;
    maxHeap.pop();
    --hl;
}

void deleteMin(){
    if (!hl) return;
    
    removeDeletedElem();

    deleted[minHeap.top().second] = true;
    minHeap.pop();
    --hl;
}

void cmd(string &op, vector<bool> &deleted){
    char cmd = op[0];
    int n = atoi(op.substr(2, op.size()).c_str());
    
    if (cmd == 'I') insert(n);
    else if (cmd == 'D'){
        if (n == 1) deleteMax();
        else deleteMin();
    }
}

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    vector<bool> deleted;
    
    for (auto &op: operations){
        cmd(op, deleted);
    }
    
    if (!hl){
        answer.push_back(0);
        answer.push_back(0);
    }else {
        removeDeletedElem();
        
        answer.push_back(maxHeap.top().first);
        answer.push_back(minHeap.top().first);
    }

    return answer;
}