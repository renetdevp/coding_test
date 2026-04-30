#include <string>
#include <vector>

using namespace std;

char discount[4] = { 10, 20, 30, 40 };
int el;

pair<int, int> userPurchase(const vector<vector<int>> &users, const vector<int> &emoticons, vector<char> &dis){
    pair<int, int> result(0, 0);

    for (const auto &user: users){
        int sum = 0;

        for (int i=0; i<emoticons.size(); ++i){
            if (dis[i] < user[0]) continue;

            sum += emoticons[i] - (emoticons[i]/100 * dis[i]);
            
            if (sum >= user[1]) break;
        }
        
        if (sum >= user[1]) ++result.first;
        else result.second += sum;
    }
    
    return result;
}

void recursion(const vector<vector<int>> &users, const vector<int> &emoticons, vector<int> &answer, vector<char> &dis, char depth){
    if (depth == el){
        pair<int, int> result = userPurchase(users, emoticons, dis);
        
        if (answer[0] < result.first || (answer[0] == result.first && answer[1] < result.second)){
            answer[0] = result.first;
            answer[1] = result.second;
        }

        return;
    }
    
    for (char i=0; i<4; ++i){
        dis[depth] = discount[i];
        recursion(users, emoticons, answer, dis, depth+1);
    }
}

// 할인율 4종, 이모티콘 7종에서 나올 수 있는 할인의 경우의 수 = 4^7 ~= 2^14 = 2^10*2^4 = 1024 * 16 = 16384
// 사용자 100명, 이모티콘 7종, 할인 경우의 수 16384을 곱해도 1억 이하 > 완전탐색 가능
vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer(2);
    
    el = emoticons.size();
    vector<char> dis(el);
    
    recursion(users, emoticons, answer, dis, 0);

    return answer;
}