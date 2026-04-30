#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Task {
    int processTime;
    int requestTime;
    int index;
};

struct CompareTask {
    bool operator()(Task &a, Task &b){
        if (a.processTime == b.processTime){
            if (a.requestTime == b.requestTime){
                return a.index > b.index;
            }
            
            return a.requestTime > b.requestTime;
        }
        
        return a.processTime > b.processTime;
    }
};

using TaskPQueue = priority_queue<Task, vector<Task>, CompareTask>;

vector<Task> getTasks(vector<vector<int>> &jobs){
    vector<Task> tasks;
    
    for (int i=0; i<jobs.size(); ++i){
        tasks.push_back({ jobs[i][1], jobs[i][0], i });
    }
    
    sort(tasks.begin(), tasks.end(), [](auto &a, auto &b){
        return a.requestTime < b.requestTime;
    });
    
    return tasks;
}

int getAvgTime(vector<Task> &tasks){
    TaskPQueue tpq;
    int t = 0, sum = 0, ti = 0;
    
    t = tasks[0].requestTime;
    
    while (ti < tasks.size() || !tpq.empty()){
        while (ti < tasks.size() && tasks[ti].requestTime <= t){
            tpq.push(tasks[ti++]);
        }

        // tpq에 들어있던 마지막 task 실행이 끝나도 남아있는 작업이 들어와있지 않은 경우
        if (tpq.empty() && ti < tasks.size()){
            ++t;
            continue;
        }

        Task p = tpq.top(); tpq.pop();

        t += p.processTime;
        sum += t - p.requestTime;
    };
    
    return sum / tasks.size();
}

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    vector<Task> tasks = getTasks(jobs);
    
    answer = getAvgTime(tasks);

    return answer;
}