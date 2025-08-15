# 3가지 알고리즘 

## Dijkstra
음의 가중치 X
- [ ] 1277

## Bellan_Ford
음 허용
```c++
void Bellan_Ford() {
    dist[1] = 0; // 시작 지점
    for (int i = 1; i <= N - 1; i++) {
        for (int j = 0; j < (int)edge.size(); j++) {
            int from = edge[j].first.first;
            int to = edge[j].first.second;
            int cost = edge[j].second;

            if (dist[from] == INF) continue;
            if (dist[to] > dist[from] + cost) dist[to] = dist[from] + cost;
        }
    }

    for (int i = 0; i < edge.size(); i++) {
        int from = edge[i].first.first;
        int to = edge[i].first.second;
        int cost = edge[i].second;

        if (dist[from] == INF) continue;
        if (dist[to] > dist[from] + cost) {
            cout << "음의 사이클이 존재하는 그래프" << endl;
            return;
        }
        cout << "Good Graph" << endl;
    }
}


```
- [ ] 1865 아주 아름다운 문제라 생각한다...

## 플로이드-와샬 
N^3 회 연산 
