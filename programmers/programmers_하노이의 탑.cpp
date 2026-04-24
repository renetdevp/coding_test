#include <string>
#include <vector>

using namespace std;

void hanoi(vector<vector<int>> &answer, char src, char dest, char len){
    if (len == 1){
        answer.push_back({ src+1, dest+1 });
        return;
    }
    
    char d = (src+1)%3 == dest ? (src+2)%3 : (src+1)%3;

    hanoi(answer, src, d, len-1);
    answer.push_back({ src+1, dest+1 });
    hanoi(answer, d, dest, len-1);
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    
    hanoi(answer, 0, 2, n);

    return answer;
}