#include <iostream>

using namespace std;
int n, m;
bool arr[4001];

// 1번 명령어 i x, i번째 전구를 x로 변경
// 2번 명령어 l r, l~r 전구 toggle
// 3번 명령어 l r, l~r 전구 끄기
// 4번 명령어 l r, l~r 전구 키기
bool toggle(int idx) {
    return arr[idx] ^ 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int o1, o2, o3;
    for (int i = 0; i < m; i++) {
        cin >> o1 >> o2 >> o3;
        if (o1 == 1) {
            arr[o2] = o3;

        } else if (o1 == 2) {
            for (int j = o2; j <= o3; j++) {
                arr[j] = toggle(j);
            }

        } else if (o1 == 3) {
            for (int j = o2; j <= o3; j++) {
                arr[j] = false;
            }

        } else if (o1 == 4) {
            for (int j = o2; j <= o3; j++) {
                arr[j] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    
    
    return 0;
}
