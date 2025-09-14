#include <iostream>  // cin, cout
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

struct santa {
    int y, x;
    int score;
};

int rdy[8] = {1, 1, -1, -1, 0, 0, 1, -1};
int rdx[8] = {0, 1, 0, 1, 1, -1, -1, -1};

int sdy[4] = {-1, 0, 1, 0};
int sdx[4] = {0, 1, 0, -1};


int n, m, p, c, d;
int ry, rx;  // 루돌프 위치

santa santas[31];
bool isDie[31];
int isStun[31];

int arr[51][51];  // idx 발사대다. 아니 이거 없으면 인생이 팍팍해질 거다

void check_santas() {
    for (int i =1 ; i <= p ; i++) cout << "idx: " << i << " y x is " << santas[i].y << " " << santas[i].x << endl;
    cout << endl;
}

void arr_init() {
    memset(arr,0x00,sizeof(arr));
    for (int i = 1; i <= p; i++) {
        if (isDie[i]) continue;

        arr[santas[i].y][santas[i].x] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if( i == ry && j == rx) cout << "R ";
            else cout << arr[i][j] << " ";
            
        }
        cout << endl;
    }
    cout << endl;
}

// 귀찮은데 재귀로 만들어버리자 ㅋㅋㅋ
void interaction(int r_dir, int idx) {
    int sy = santas[idx].y; int sx = santas[idx].x;
    int ny = sy + rdy[r_dir]; int nx = sx + rdx[r_dir];

    if (ny <= 0 || ny > n || nx <= 0 || nx > n) {
        isDie[idx] = true;
        return;
    } else if (arr[ny][nx] != 0) {
        interaction(r_dir, arr[ny][nx]);
    }

    santas[idx].y = ny; santas[idx].x = nx;  // 여기서 한번에 사르륵 최신화 해주는거다
}

void deer_move() {
    int min_idx = INT_MAX;  // 얜 굳이 이럴 필요 없음 ㅎㅎ;
    int min_dist = INT_MAX;
    int m_sy, m_sx;
    for (int i = 1; i <= p; i++) {
        if (isDie[i]) continue;
        int dist = (ry - santas[i].y) * (ry - santas[i].y) + (rx - santas[i].x) * (rx - santas[i].x);

        if (min_dist > dist) { min_idx = i; min_dist = dist; m_sy = santas[i].y; m_sx = santas[i].x; }

        else if (min_dist == dist) {  // 이거 조건 깜빡할 뻔 했다
            if (m_sy > santas[i].y) {
                continue;
            } else if (m_sy == santas[i].y) {
                if (m_sx < santas[i].x) {min_idx = i; m_sy = santas[i].y; m_sx = santas[i].x; }
                else continue;

            } else { min_idx = i; m_sy = santas[i].y; m_sx = santas[i].x; }
        }
    }

    int sy = santas[min_idx].y; int sx = santas[min_idx].x;
    int min_dir; min_dist = INT_MAX;

    for (int i = 0; i < 8; i++) {  // 가장 가까워질 수 있는 방향 선정
        int ny = ry + rdy[i]; int nx = rx + rdx[i];
        if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
        
        int dist = (sy - ny) * (sy - ny) + (sx - nx) * (sx - nx);
        if (min_dist > dist) { min_dir = i; min_dist = dist; }
    }

    // 이제 밀출 애랑, 방향이 전부 전해졌다 
    ry += rdy[min_dir]; rx += rdx[min_dir];
    if (arr[ry][rx] != 0) {
        santas[min_idx].score += c;  // 점수 넣어주기
        sy += rdy[min_dir] * c; sx += rdx[min_dir] * c;  // 산타 위치 최신화 (아직 하지 않았다)
        isStun[min_idx] = 2; // 담턴까지 기절시켜야 한다

        if (sy <= 0 || sy > n || sx <= 0 || sx > n) { isDie[min_idx] = true; return; }
    

        santas[min_idx].y = sy; santas[min_idx].x = sx;
        if (arr[sy][sx] != 0) interaction(min_dir, arr[sy][sx]);
        cout << "After deer move" << endl;
        arr_init();  // interaction으로 최신화 된 좌표 갱신해주기
    }
}

int change_dir(int dir) { 
    return (dir + 2) % 4;
}

void santa_move() {
    for (int i = 1; i <= p; i++) {
        if (isDie[i]) continue;  // 죽었으면 그냥 넘어간다
        if (isStun[i] != 0) continue; // 기절도 스킵 
        
        int sy = santas[i].y; int sx = santas[i].x;
        int next_dist = (ry - sy) * (ry - sy) + (rx - sx) * (rx - sx);
        int s_dir = INT_MIN;

        for (int j = 0; j < 4; j++) {
            int ny = sy + sdy[j]; int nx = sx + sdx[j];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;  // arr 넘으면 당연히 안됨
            if (arr[ny][nx] != 0) continue;  // 누군가 있으니까 포기하는 idx

            int dist = (ry - ny) * (ry - ny) + (rx - nx) * (rx - nx);  // sdy, sdx에 따른 추정 거리
            if (dist > next_dist) continue;  // 멀어지면 무시
            else if (dist == next_dist) continue;  // 같아도 무시 ( 가까워지지도 못하고, 그냥 의미가 없다 )
            else { s_dir = j; next_dist = dist; }
        }

        if (s_dir != INT_MIN) {  // 어쨌든 무언가로 향하는 방향이 선택됐을 때
            santas[i].y += sdy[s_dir]; santas[i].x += sdx[s_dir];
            if (santas[i].y == ry && santas[i].x == rx) {
                santas[i].score += d; isStun[i] = 2;
                int n_dir = change_dir(s_dir);
                santas[i].y += sdy[n_dir] * d; santas[i].x += sdx[n_dir] * d;
                if (santas[i].y <= 0 || santas[i].y > n || santas[i].x <= 0 || santas[i].x > 0) { isDie[i] = true; continue; }
                if (arr[santas[i].y][santas[i].x] != 0) {
                    interaction(n_dir, arr[santas[i].y][santas[i].x]);
                    cout << "After " << i << "th Santa move " << endl;
                    arr_init();
                }
            }
        }
    }
}

void everyone_cheer_up() {
    for (int i = 1; i <= p; i++) { if (!isDie[i]) santas[i].score++; }
}

void print_score() {
    for (int i = 1; i <= p; i++) { cout << santas[i].score << " "; }
}

void stun_down() {
    for (int i = 1; i <= p; i++) { if (isStun[i] > 0) isStun[i]--; }
}

bool isAllDie() {
    for (int i =1 ; i <= p; i++) { if (!isDie[i]) return false; }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> p >> c >> d;
    cin >> ry >> rx;
    int idx;
    for (int i = 1; i <= p; i++) {
        cin >> idx >> santas[idx].y >> santas[idx].x;
    }
    int turn_cnt = 1;
    while(m--) {
        cout << "Turn " << turn_cnt << endl;
        arr_init();
        deer_move();
        check_santas();
        santa_move();
        check_santas();

        if (isAllDie()) break;
        everyone_cheer_up();
        stun_down();
        turn_cnt++;
    }
    print_score();

    return 0;
}
