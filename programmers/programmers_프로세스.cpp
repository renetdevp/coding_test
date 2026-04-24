#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    vector<int> sorted(priorities);
    vector<pair<int, int>> tmp;
    
    sort(sorted.rbegin(), sorted.rend());

    for (int i=0; i<priorities.size(); ++i){
        tmp.push_back({ priorities[i], i });
    }
    
    while (tmp.size()){
        if (tmp[0].first != sorted[0]){
            auto elem = tmp[0];
            tmp.erase(tmp.begin());
            tmp.push_back(elem);
            continue;
        }
        
        ++answer;

        if (tmp[0].second == location) break;

        tmp.erase(tmp.begin());
        sorted.erase(sorted.begin());
    }
    
    return answer;
}