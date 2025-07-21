#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[10];
vector<int> v;
int main() {
    for (int i = 1; i <= 9; i++) {
        cin >> arr[i];
    }
    bool break_flag = false;
    // Brute Force에 있으니까 이렇게 해보긴 할 것인데..
    // 흠...
    for (int i1 = 1; i1 <= 9; i1++) {
        for (int i2 = i1+1; i2 <= 9; i2++) {
            for (int i3 = i2+1; i3 <= 9; i3++) {
                for (int i4 = i3+1; i4 <= 9; i4++) {
                    for (int i5 = i4+1; i5 <= 9; i5++) {
                        for (int i6 = i5+1; i6 <= 9; i6++) {
                            for (int i7 = i6+1; i7 <= 9; i7++) {
                                if (arr[i1] + arr[i2] + arr[i3] + arr[i4] + arr[i5] + arr[i6] + arr[i7] == 100) {
                                    v.push_back(arr[i1]);
                                    v.push_back(arr[i2]);
                                    v.push_back(arr[i3]);
                                    v.push_back(arr[i4]);
                                    v.push_back(arr[i5]);
                                    v.push_back(arr[i6]);
                                    v.push_back(arr[i7]);
                                    break_flag = true;
                                    break;
                                }
                            }
                            if (break_flag) break;
                        }
                        if (break_flag) break;
                    }
                    if (break_flag) break;
                }
                if (break_flag) break;
            }
            if (break_flag) break;
        }
        if (break_flag) break;
    }
    // 3^14면 500만회도 안되네 굿
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << '\n';
    }
    return 0;
}
