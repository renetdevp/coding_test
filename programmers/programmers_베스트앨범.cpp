#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, vector<pair<int, int>>> playInfo;
    vector<pair<string, int>> mostPlay;
    
    for (int i=0; i<genres.size(); ++i){
        playInfo[genres[i]].push_back({ plays[i], i });
    }
    
    for (auto &[k, v]: playInfo){
        sort(v.begin(), v.end(), [](const auto &a, const auto &b){
            if (a.first == b.first) return a.second < b.second;
            
            return a.first > b.first;
        });
        
        int sum = 0;
        
        for (const auto &[p, i]: v){
            sum += p;
        }
        
        mostPlay.push_back({ k, sum });
    }

    sort(mostPlay.begin(), mostPlay.end(), [](const auto &a, const auto &b){
        return a.second > b.second;
    });
    
    for (const auto &elem: mostPlay){
        answer.push_back(playInfo[elem.first].begin()->second);
        if (playInfo[elem.first].size() >= 2)
            answer.push_back((playInfo[elem.first].begin()+1)->second);
    }
    
    return answer;
}