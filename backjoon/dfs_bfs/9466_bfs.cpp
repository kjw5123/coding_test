#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

/* [문제]
 * 
 * 우리는 텀프로젝트를 해야한다 
 * 팀원 수 제한 X
 * 모은 학생들이 한 팀인 경우도 있을 수 있다
 *
 * 팀을 구성하기 위해, 학생들은 같이 하고 싶은 사람 정해야함 (이거만 보면 Union Find 같은데)
 * 한 명 만 선택 가능하다
 * 혼자 하고 싶은 사람은 자기 자신을 골라도 된다 (1인 1팀도 허용)
 * 
 * 학생이 1 ~ r 명 있을 때 
 * r이 1이고, 1번 학생이 1번을 선택하는 경우
 * or
 * 1이 2를, 2가 3을, s_r-1이 s_r을 고르고 s_r이 1을 선택하는 경우엔 모든 수강 인원이 1팀이 된다고 할 수 있다
 *
 * 1 2 3 4 5 6 7 (학생)
 * 3 1 3 7 3 4 6 (같이 하고 싶은 사람 번호)
 * (3), (4  6 7), 그 외 떨거지들
 * 사이클 발생 해야 1팀으로 인정해준다 
 *
 * [입력]
 * T: 테스트 케이스 수
 * n: 각 테스트 케이스 학생 수 (1 ~ 100,000;;)
 * n개의 정수: 같이 하고 싶은 사람의 번호
 *
 * [출력]
 * 각 테스트 케이스 별 팀 없는 학생 수 ('\n'으로 각 테스트케이스 구분)
 * 
 * [사견]
 * bfs 문제니 bfs 풀긴 할 것인데..
 * 표현 방법에 대한 고민이 필요한 것 같다
 *
 * 아 유니온 파인드 비스무리하게 풀이 하려 했는데 
 * 걍 각 element 별로 queue로 상태 관리 해도 됐겠네 아!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 * 1번 째 풀이 틀렸다.
 * queue 쓰자.
 * 아니 바보도 아니고, 당연히 worst에선 dfs가 100,000번 호출될텐데 메모리 초과가 뜨지..
 * */

int tc, n, val;
queue<int> wantWho[100001];
bool cycle[100001];

void bfs(int idx) {
    int root_idx = idx;
    vector<int> hist;
    hist.push_back(idx);
    
    int next_idx = wantWho[idx].front();
    if (wantWho[next_idx].empty()) return;

    wantWho[idx].pop();
    hist.push_back(next_idx);
    int prev_idx = idx;
    idx = next_idx;
    
    while(!wantWho[idx].empty()) {
        next_idx = wantWho[idx].front();
        wantWho[idx].pop();
        hist.push_back(next_idx);
        prev_idx = idx;
        idx = next_idx;
    }
    if (root_idx == idx) {  // 탐색한 모든 것이 깔끔하게 cycle
        for (int i = 0; i < (int)hist.size(); i++) {
            cycle[hist[i]] = true;
        }

    } else {
        int pos = -1;
        for (int i = 0; i < (int)hist.size(); i++) {
            if (idx == hist[i]) { pos = i; break; }
        }
        if (pos != -1 && pos < (int)hist.size() - 1) {  
            for (int i = pos; i < (int)hist.size(); i++) {
                cycle[hist[i]] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tc;
    for (int t = 0; t < tc; t++) {
        cin >> n;
        memset(cycle, 0x00, sizeof(cycle));
        for (int i = 1; i <= n; i++) {
            cin >> val;
            wantWho[i].push(val);
        }

        for (int i = 1; i <= n; i++) {
            if (!wantWho[i].empty()) bfs(i);
        }
        
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (!cycle[i]) cnt++;
        }
        cout << cnt << '\n';

        for(int i = 1; i <= n; i++) {
            while(!wantWho[i].empty()) wantWho[i].pop();
        }
    }
    return 0;
}
