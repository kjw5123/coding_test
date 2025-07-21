#include <iostream>

using namespace std;

int arr[11] = {0};

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

   // 문제에서 아주 명확하게 '배수' 관계임을 명시했으므로,
   // 큰 값이면 무조건 아래 값으로 표현 되기에, 그냥 큰값부터 순서대로 쭉 빼면 된다...고 생각한다
   //
   int result = 0;
   for (int i = n-1; i >= 0; i--)  {
       if (k / arr[i] != 0) {
           result += k / arr[i];
           k %= arr[i];
       }
   }
   cout << result << endl;
    return 0;
}
