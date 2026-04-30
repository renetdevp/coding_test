#include <string>
#include <vector>

using namespace std;

// prices[i]의 가격이 끝날 때까지 떨어지지 않았다면, pl-1 - i 초 동안 떨어지지 않은 상태일거임.
// prices[i]의 가격이 중간에 떨어졌다면, [떨어진 시점의 index] - i 초 동안 떨어지지 않은 상태일거임.

vector<int> solution(vector<int> prices) {
    int pl = prices.size();
    vector<int> answer(pl, 0);
    pair<int, int> mp;
    
    mp = { pl-1, prices[pl-1] };
    
    for (int i=pl-1; i>=0; --i){
        if (prices[i] <= mp.second){
            mp = { i, prices[i] };
            answer[i] = pl-1-i;
        }else {
            for (int j=i+1; j<=mp.first; ++j){
                if (prices[i] <= prices[j]) continue;
                
                answer[i] = j-i;
                break;
            }
        }
    }
    
    return answer;
}