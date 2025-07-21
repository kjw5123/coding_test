#include <iostream>

using namespace std;

/*
 * 아침 잠이 덜 깨서 이해가 안되네
 *
 * 고층 빌딩이 많은 동네에서 삶
 * 빌딩은 총 N 개가 있고 1차원으로 쭉 이어짐
 * 대충 높이 가짐 각자
 *
 * 시뮬레이션 쓰지 말라고 높이를 10억으로 넣어놨네 ㅁㅊ
 *
 * 암튼 A 빌딩에서 B 빌딩 바라볼 때
 *  두 빌딩 꼭대기 잇는 선분이 다른 고층 빌딩을 지나치지 않는 건물만 볼 수 있다 
 *  단적인 예시로, 1,3에서 3,1 바라봤을 때, 사이에 2,2 있으면 못본다
 * */
int n;
int arr[51];
int canSee[51];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> arr[i];


    for (int std = 1; std <= n; std++) {
        for (int small = std - 1; small >= 1; small--) {
            int small_y = arr[small]; int small_x = small;
            int std_y = arr[std]; int std_x = std;

            double a = double(small_y - std_y) / double(small_x - std_x);
            double bias = small_y - a * small_x;
            
            bool isOkay = true;
            for (int i = small_x+1; i <= std-1; i++) {
                if (arr[i] >= a * i + bias) isOkay = false;
            }
            if (isOkay) {
                // cout << "My idx is "  << std << " and I can see " << small << endl;
                canSee[std]++;
            }
        }

        for (int big = std + 1; big <= n; big++) {
            int big_y  =arr[big]; int big_x = big;
            int std_y = arr[std]; int std_x = std;

            double a = double(big_y - std_y) / double(big_x - std_x);
            double bias = big_y - a * big_x;
            
            bool isOkay = true;
            for (int i = std_x+1; i <= big_x-1; i++) {
                if (arr[i] >= a * i + bias) isOkay = false;
            }

            if (isOkay) {
                // cout << "My idx is "  << std << " and I can see " << big << endl;
                canSee[std]++;
            }
            
        }
    }

        int maxVal = -1;
        int maxIdx = -1;
        for (int i = 1; i <= n; i++) {
            if (maxVal < canSee[i]) {
                maxVal = canSee[i];
                maxIdx = i;
            }
            // cout << canSee[i] << " ";
        }

        cout << maxVal << endl;
    return 0;
}
