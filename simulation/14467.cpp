#include <iostream>
#include <cstring>

using namespace std;
int n ;

bool actived[11];
int dir[11];
int cnt[11];

void dir_init() {
    memset(dir, 0xFF, sizeof(dir));
}

int main() {
    dir_init();
    cin >> n;
    for (int i = 0; i < n; i++) {
        int num, pos;
        cin >> num >> pos;
        if (!actived[num]) {
            actived[num] = true;
            dir[num] = pos;

        } else if (dir[num] != pos) {
            cnt[num]++;
            dir[num] = pos;
        }
    }
    
    int result = 0;
    for (int i = 1; i <= 10; i++) {
        result += cnt[i];
    }
    cout << result << endl;
    return 0;
}
