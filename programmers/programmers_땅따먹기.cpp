#include <vector>

using namespace std;

int dp(vector<vector<int>> &arr, const vector<vector<int>> &land, int r, int c){    
    if (arr[r][c]) return arr[r][c];
    
    int result = -1;
    
    for (char i=0; i<4; ++i){
        if (i == c) continue;
        
        result = max(result, dp(arr, land, r-1, i) + land[r][c]);
    }
    
    arr[r][c] = result;
    
    return result;
}

int solution(vector<vector<int>> land){
    int answer = 0;
    int bl = -1;
    vector<vector<int>> arr(land.size(), vector<int>(4));

    for (char i=0; i<4; ++i) arr[0][i] = land[0][i];
    
    for (char i=0; i<4; ++i){
        answer = max(answer, dp(arr, land, land.size()-1, i));
    }

    return answer;
}