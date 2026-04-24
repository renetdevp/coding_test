#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    vector<string> result;

    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());

    set_difference(participant.begin(), participant.end(), completion.begin(), completion.end(), back_inserter(result));

    string answer = *result.begin();

    return answer;
}