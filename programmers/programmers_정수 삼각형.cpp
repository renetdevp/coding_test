#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int tl = triangle.size();
    vector<vector<int>> arr(tl, vector<int>(tl, 0));
    
    arr[0][0] = triangle[0][0];
    
    for (int i=1; i<tl; ++i){
        for (int j=0; j<=i; ++j){
            int v = triangle[i][j];

            if (j) arr[i][j] = max(arr[i][j], arr[i-1][j-1] + v);
            if (i != j) arr[i][j] = max(arr[i][j], arr[i-1][j] + v);
        }
    }
    
    for (int i=0; i<tl; ++i) answer = max(answer, arr[tl-1][i]);

    return answer;
}