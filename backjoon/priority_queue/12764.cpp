#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
/* [문제]
 * 싸지방에 사람이 많이 몰려서 컴퓨터가 부족한 상황 
 * 마음의 편지로 해결함
 *
 * 컴퓨터를 증설 할 것이며, 사용률에 따라 성능이 달라짐
 *
 * 사람 수만큼 컴퓨터 못삼
 *
 * 모든 사람이 정해진 시간에 싸지방 이용함
 *
 * 1 ~ N번까지 각 컴퓨터에 번호가 부여됨 
 * 모든 사람들은 싸지방에 들어왔을 때, 비어있는 자리 중 번호가 작은 자리에 앉음 
 * 
 * 모든 사람이 기다리지 않고 싸지방 이용할 수 있는 컴퓨터의 최소 개수와, 자리별로 몇명이 이용했는지를 구해보자
 * */

int n;  // 인원 수 1 ~ 100,000

int cnt[100001];
int ucc = 1;  // using_computer_cnt 인데 이거 다 치면 한세월이다;
int a, b;

struct cmp{
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        if (p1.first == p2.first) return p1.second > p2.second;  // 개중에 일찍 일어나는 순서
        return p1.first > p2.first;  // 먼저오는 사람 순서
    }
};

struct early {
    bool operator() (pair<int,int> p1, pair<int,int> p2) {  // idx, end_time
        return p1.second > p2.second;  
    }
};
/*
struct minIdx {
    bool operator() (pair<int,int> p1, pair<int,int> p2) {  // idx, end_time
        return p1.first > p2.first;  
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, minIdx> min_idx;
*/
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
priority_queue<pair<int,int>, vector<pair<int,int>>, early> now_active;

struct minIdx {
    bool operator() (int a, int b) {
        return a > b;  
    }
};
priority_queue<int, vector<int>, minIdx> min_idx;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        pq.push({a,b});
    }
    int idx = 0; 
    cnt[idx]++;
    now_active.push({idx++, pq.top().second});
    pq.pop();
    while(!pq.empty()) {
        int s = pq.top().first; int e = pq.top().second; pq.pop();
        // cout << "I'm " << s << " " << e << endl;
        if (!now_active.empty()) {
            while(now_active.top().second <= s) {
                min_idx.push(now_active.top().first);
                now_active.pop();
                if (now_active.empty()) break;
            }
        }

        int used_idx;
        if (!min_idx.empty()) {
            used_idx = min_idx.top();
            min_idx.pop();

        } else used_idx = idx++;

        cnt[used_idx]++;
        now_active.push({used_idx, e});
    }

    cout << idx << endl;
    for (int i = 0; i < idx; i++) {
        cout << cnt[i] << " ";
    }
    return 0; 
}
