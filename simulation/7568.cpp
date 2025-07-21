#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
pair<int,int> arr[51];
int grade[51];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    for (int i = 1; i <= n; i++) {
        int cnt = 1;
        for (int j = 1; j <= n; j++) {
            if (arr[i].first < arr[j].first && arr[i].second < arr[j].second) cnt++;
        }
        grade[i] = cnt;
    }

    for (int i = 1; i <= n; i++) cout << grade[i] << " ";
    return 0; 
}
