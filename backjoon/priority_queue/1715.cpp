#include <iostream>
#include <vector>
#include <queue>

using namespace std;
// min heap 정렬하고 
// 2개 빼고 1개 만들고 삽입해서
// size() 1이면 시마이치면 되지 않을까?
typedef long long ll;
struct cmp{
    bool operator() (ll a, ll b) {
        return a > b;
    }
};

int n;
priority_queue<ll, vector<ll>, cmp> pq;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    ll val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        pq.push(val);
    }
    
    // if (n == 1) cout << 0 << endl;  // 문제에서 두 묶음이라는데 입력에 1이 있으면 뭐 어떻게 처리해야해;;
    ll result = 0;
    while(pq.size() != 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        pq.push(a + b);
        result += a + b;
    }
    cout << result << endl;

    return 0;
}
