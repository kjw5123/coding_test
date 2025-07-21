#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

vector<pair<int,int> > v;

int arr[100001] = {0};  // v의 index만 저장할 것임

bool cmp(pair<int,int> p1, pair<int,int> p2) {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}

bool cmp2(pair<int,int> p1, pair<int,int> p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;
        v.push_back({start, end});
    }    

    sort(v.begin(), v.end(), cmp2);



    // 1. arr에는 v의 index만 넣어둠 (이걸로 v[arr[0]].first, second 꺼내 쓰는 방향으로)
    // 2. activated는 현재 활성화된 회의실이고, 이걸 범위로 해서 arr 순회할 것
    // 3. actived 끝까지 다 돌아도 뭐 없으면 actived++; 하고 걍 거기에 인덱스 넣기 
    // 4. 비교 로직은.. 결국 지금 넣고자 하는게 들어갈 수 있는지 확인하는거니까 뭐
    // 아오 근데 이러면 O(NlogN)인가? 좀 성능 구리네 2초 제한이기 망정이지
    //
    // 위 주석대로 로직 안짰는데, 접근 시도 했던 컨셉 자체는 유효하다 생각해서 일단 안지우고 남김
    //
    // 일단 근본적으로 arr를 각 회의실이라 가정하고, 끝나는 시간들을 저장해두고
    // 이에 대해 선형 탐색 하게 한게 패착인듯 하다 
    // 앞으로도, 이런 식으로 (모든 회의실 중 가장 빨리 끝나는 걸 찾아야 하는 상황이라면)
    // 우선순위 큐를 쓰는게 정배라고 생각하자... 왜 이걸 몰랐을까 지금까지도
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; i++) {
        if (!pq.empty() && pq.top() <= v[i].first) {
            // cout << "My index is " << i << " and I pop " << pq.top() << endl;
            pq.pop();
        }

        pq.push(v[i].second);
        // cout << "My index is " << i << " and I push " << v[i].first << " " << v[i].second << endl;
       
    }
    cout << pq.size() << endl;
    return 0;
}
