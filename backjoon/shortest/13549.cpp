#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

/* [문제]
 * 수빈이는 수박꼭지 중이다
 * 수빈이는 N에 위치한다 (0 ~ 100,000)
 * 동생은 K에 위치한다 (0 ~ 100,000)
 *
 * 수빈이가 위치 X일때 걸으면 1초 후 좌우로 이동
 * 순간이동 시엔 0초만에 2 * x 로 이동
 *
 * 동생 찾는 가장 빠른 시간 구하기
 *
 * */
int n, k;
int arr[100001];
struct cmp {
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.second > p2.second;
    }
};

void dijkstra(int start) {
    priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int c_idx = pq.top().first;
        int c_time = pq.top().second;
        pq.pop();

        if (c_idx == k) {cout << c_time << endl; exit(0);}

        if (c_idx + 1 <= 100000) {
            if (arr[c_idx+1] > c_time+1) {
                arr[c_idx+1] = c_time+1;
                pq.push({c_idx+1, c_time+1});
            }
        }
        if (c_idx - 1 >= 0) {
            if (arr[c_idx-1] > c_time+1) {
                arr[c_idx-1] = c_time+1;
                pq.push({c_idx-1, c_time+1});
            }
        }
        if (c_idx * 2 <= 100000) {
            if (arr[c_idx*2] > c_time) {
                arr[c_idx*2] = c_time;
                pq.push({c_idx * 2, c_time});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for (int i = 0; i <= 100000; i++) arr[i] = INT_MAX;   
    dijkstra(n);
    
    
    return 0;
}
