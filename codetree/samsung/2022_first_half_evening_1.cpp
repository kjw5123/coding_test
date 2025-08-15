#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <cstring>
#include <utility>
#include <queue>

using namespace std;
// 2025 08 12 오후 1시 43분 시작
//
// 3명 이상이 한 팀이 돼서 꼬리잡기 할 것이다
//
// 모든 사람은 자기 앞 사람 허리 잡고 이동
// 맨 앞사람을 머리사람, 뒷사람을 꼬리사람이라 지칭
// 주어진 이동선 따라서 이동 함
// 이동선은 연결돼있고, 다른 선이랑 안 곂침
//
// 게임은 라운드 별로 진행되며 각 라운드의 행동 규칙은 다음과 같다:
// 1. 머리 사람을 따라서 한칸 이동 
// 2. 공이 정해진 선 따라 던져짐 라운드 따라 한 행에 쫙 던져진다 ->(1~n), ^(n+1~2n), <-(2n+1,3n),v(3n+1~4n).. 다시 처음으로
// 3. 공이 던져질 때, 최초로 만나는 이눤이 점수를 얻는다
//    머리 사람 기준으로 k번째 사람이면 k의 제곱만큼 점수 획득 
//    아무도 공 안맞으면 아무도 점수 안받는다
//    공을 획득한 팀은 머리 <-> 꼬리 사람 swap 발생
// 4. 시뮬 예시 (그냥 생략 하겠다)
// 
// [입력]
// 격자 크기, 팀 개수 나타내는 n, m
// 라운드 수 k
// n개의 줄에 걸쳐 각 행체 초기 상태의 정보를 나타내는 정수 n개가 공백 두고 입력됨
// 0은 빈칸, 1은 머리사람, 2는 그 외 나머지, 3은 꼬리 사람, 4는 이동선
// 
// 출력은 뭐 각 팀 점수 총합 출력 하면 된다. 팀별로 점수 따로 관리할 필요 X
//
//
// [사견]
// 굳이 배열에서 낑낑대기보단
// 1. bfs로 각 path 추출 + 특정 팀의 head 정보와 길이, 역방향인지 정보 담는 구조체에 담아두기
// 2. board라는 pair<team_num, 순서> 2차원 격자에 표현
// 3. 공 던지기
// 4. 누군가가 맞으면 해당 팀 head 수정 및 점수 증가
//    뭐 대충 이렇게 하되, path에서 실수 안하게끔 조심하기

struct train {  // 솔직히 이름 뭐라고 해야할지 모르겠다;
    int idx;  // head 좌표
    int cnt;
};

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

int arr[21][21];
bool visited[21][21];
pair<int,int> board[21][21];
int n, m, turn;
train trains[6]; // 0번 인덱스는 그냥 비울거다
vector<pair<int,int> > paths[6]; // 마찬가지
bool isReverse[6];
long long int score;


void bfs(int y, int x, int team_num) {
    queue<pair<int,int>> q;
    q.push({y,x});
    paths[team_num].push_back({y,x});
    trains[team_num].idx = 0;
    trains[team_num].cnt = 1;
    visited[y][x] = true;

    while (!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (arr[ny][nx] == 0) continue;
            if (visited[ny][nx]) continue;
            
            q.push({ny, nx});
            if (arr[ny][nx] != 4) trains[team_num].cnt++;
            paths[team_num].push_back({ny,nx});
            visited[ny][nx] = true;
            break;
        }
    }
}

void train_move() {
    for (int i = 1; i <= m; i++) {
        int val = 0;
        if (isReverse[i]) val = -1;
        else val = 1;
        trains[i].idx = (trains[i].idx + (int)paths[i].size() + val) % (int)paths[i].size();
    }
}

// void board_init() {
//     memset(board, 0x00, sizeof(board));
//     for (int i = 1; i <= m; i++) {
//         int path = (int)paths[i].size();
//         int head = trains[i].idx;
//         int cnt = trains[i].cnt;

//         for (int j = 0; j < cnt; j++) {
//             int idx;
//             if (isReverse[i]) idx = (head - j + path) % path;
//             else idx = (head + j) % path;

//             int y = paths[i][idx].first;
//             int x = paths[i][idx].second;
//             board[y][x].first = i;
//             board[y][x].second = j + 1;
//         }
//     }
// }

void board_init() {
    memset(board, 0x00, sizeof(board));
    for (int i = 1; i <= m; i++) {
        int L = (int)paths[i].size();
        int head = trains[i].idx;
        int cnt  = trains[i].cnt;
        int step = isReverse[i] ? -1 : +1;

        for (int j = 0; j < cnt; j++) {
            int idx = (head + (long long)step * j % L + L) % L; // 안전 모듈러
            int y = paths[i][idx].first;
            int x = paths[i][idx].second;
            board[y][x] = {i, j + 1};  // 머리=1, …, 꼬리=cnt
        }
    }
}


void shoot_ball(int now_turn) {
    int t = (now_turn - 1) % (4 * n);
    int y = -1; int x = -1;
    
    if (t < n) {
        int i = t + 1;
        for (int j = 1; j <= n; j++) {
            if (board[i][j].second) {y = i; x = j; break;}
        }
    } else if (t < 2 * n) {
        int j = t - n + 1;
        for (int i = n; i >= 1; i--) {
            if (board[i][j].second) {y = i; x = j; break;}
        }

    } else if (t < 3 * n) {
        int i = n - (t - 2*n);
        for (int j = n; j >= 1; j--) {
            if (board[i][j].second) {y = i; x = j; break;}
        }

    } else {
        int j = n - (t - 3*n);
        for (int i = 1; i <= n; i++) {
            if (board[i][j].second) {y = i; x = j; break;}
        }
    } 

    if (y == -1) return;

    int team_num = board[y][x].first;
    int val = board[y][x].second;

    score += val * val;

    int path = (int)paths[team_num].size();
    int head = trains[team_num].idx;
    int cnt = trains[team_num].cnt;

    int tail_idx;
    if (isReverse[team_num]) tail_idx = (head - (cnt - 1) + path) % path;
    else tail_idx = (head + (cnt - 1)) % path;

    trains[team_num].idx = tail_idx;
    isReverse[team_num] = !isReverse[team_num];
}

void init_direction(int team) {
    int L = (int)paths[team].size();
    int head = trains[team].idx;

    auto next_non4 = [&](int start, int step) {
        int cur = start;
        while (true) {
            cur = (cur + step + L) % L;
            int y = paths[team][cur].first;
            int x = paths[team][cur].second;
            if (arr[y][x] != 4) return cur; // 사람(1,2,3) 만날 때까지 전진
        }
    };

    int plusIdx  = next_non4(head, +1);
    int minusIdx = next_non4(head, -1);

    int yP = paths[team][plusIdx].first,  xP = paths[team][plusIdx].second;
    int yM = paths[team][minusIdx].first, xM = paths[team][minusIdx].second;

    // 2(몸통) 쪽이 '머리 기준 다음 사람'이다. (3=꼬리, 1=머리 자기 자신 아님)
    bool plusToHuman2  = (arr[yP][xP] == 2);
    bool minusToHuman2 = (arr[yM][xM] == 2);

    if (plusToHuman2 && !minusToHuman2)      isReverse[team] = false; // + 방향이 사람쪽
    else if (!plusToHuman2 && minusToHuman2) isReverse[team] = true;  // - 방향이 사람쪽
    else                                     isReverse[team] = false; // 애매하면 기본값
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> turn;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];    
        }
    }
    
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[i][j] == 1) { bfs(i, j, cnt); init_direction(cnt++);}
        }
    }

    for (int i = 1; i <= turn; i++) {
        train_move();
        board_init();
        shoot_ball(i);
    }

    cout << score << endl;
    return 0;
}
