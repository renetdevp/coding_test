#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    
    sort(phone_book.begin(), phone_book.end());
    
    for (size_t i=1; i<phone_book.size(); ++i){
        string &prev = phone_book[i-1];
        string &s = phone_book[i];
        
        if (s.size() < prev.size()) continue;
        if (s.compare(0, prev.size(), prev)) continue;
        
        answer = false;
        break;
    }
    
    return answer;
}