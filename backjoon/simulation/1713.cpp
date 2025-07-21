#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int photo_num;
int total_gachu;  // 개추 ㅋㅋ
int student_num;

struct album_info {
    int std_num = 0;
    int gachu = 0;
    int turn = 0;
};

album_info arr[21];

bool isExist() {
    for (int i = 0; i < photo_num; i++) {
        if (arr[i].std_num == student_num) {
            arr[i].gachu++;
            return true;
        }
    }
    return false;
}

int isEmpty() {
    for (int i = 0; i < photo_num; i++) {
        if (arr[i].std_num == 0) return i;
    }
    return -1;
}

bool cmp(album_info a1, album_info a2) {
    return a1.std_num < a2.std_num;
}

int findRemoveIdx() {
    // 개추 적은거부터 찾기
    // 만약 적은게 여러개면 오래된거 찾기
    vector<int> less_gachu;
    int minVal = INT_MAX;
    for (int i = 0; i < photo_num; i++) {
        minVal = min(minVal, arr[i].gachu);
    }

    for (int i = 0; i < photo_num; i++) {
        if (arr[i].gachu == minVal) less_gachu.push_back(i);
    }
    
    if ((int)less_gachu.size() == 1) return less_gachu[0];
    else {
        int minTurn = INT_MAX;
        int minIdx = INT_MAX;
        for (int i = 0; i < (int)less_gachu.size(); i++) {
            if (minTurn > arr[less_gachu[i]].turn) {
                minTurn = arr[less_gachu[i]].turn;
                minIdx = less_gachu[i];
            }
        }
        return minIdx;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> photo_num >> total_gachu;
    
    for (int turn = 1; turn <= total_gachu; turn++) {
        cin >> student_num;
        if (isExist()) continue;  // 함수안에서 개추 수 올려줌

        int idx = isEmpty();
        if (isEmpty() == -1) {
           idx = findRemoveIdx();
        }

        arr[idx] = {student_num, 1, turn};
    }
    
    sort(arr, arr + photo_num, cmp);
    for (int i = 0; i < photo_num; i++) {
        if (arr[i].std_num != 0) {
            cout << arr[i].std_num << " ";        
        }
    }
    return 0;
}
