#include <iostream>
#include <algorithm>

using namespace std;

long long int arr[100001] = {0};
long long int l[100001] = {0};
long long int r[100001] = {0};
long long int total[100001] = {0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];

    l[0] = arr[0];
    r[n-1] = arr[n-1];

    for (int i = 1; i < n; i++) {
        l[i] = l[i-1] + arr[i];
    }
    for (int i = n - 2; i >= 0; i--) {
        r[i] = r[i+1] + arr[i];
    }

    long long total_max_value = -1;
    for (int i = 0; i < n; i++) {
        total[i] = l[i] + r[i];
        if (total[i] > total_max_value) total_max_value = total[i];
    }


    // 내 생각엔 3가지 구분만 지으면 될듯?
    // 1. left 끝단 + left 중 최소로 우측 꿀통 찾기
    // 2. right 끝단 + right 중 최소로 좌측 꿀통 찾기
    // 3. total 젤 큰 꿀통에 대해서 양 끝 값 빼기
    // 아무리 생각해도 이것보다 크게 나뉘는 케이스는 없을 듯 하다
    //
    long long int left_max_val = 0;
    for (int i = 1; i < n-1; i++) {
        left_max_val = max(left_max_val, (l[n-1] * 2 - l[0] - arr[i] - l[i]));
    }

    long long int right_max_val = 0;
    for (int i = n - 2; i >= 1; i--) {
        right_max_val = max(right_max_val, (r[0] * 2 - r[n-1] - arr[i] - r[i]));
    }

    long long int total_max_val = total_max_value - l[0] - r[n-1];


    // cout << left_max_val <<  " " << right_max_val << " " << total_max_val << endl;
    cout << max(max(left_max_val, right_max_val), total_max_val) << endl;
/*
    for (int i = 0; i < n; i++) {
        cout << l[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << r[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << total[i] << " ";
    }
    */
    return 0;
}
