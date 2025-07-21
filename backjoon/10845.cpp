#include <iostream>
#include <string>

using namespace std;

int arr[100001] = {0};
int front = 0;
int back = -1;

int main() {
    int order = 0;
    cin >> order;
    string str;
    int val;
    for (int i = 0; i < order; i++) {
        cin >> str;
        if (str == "push") {
            cin >> val;
            arr[++back] = val;
        } else if (str == "front") {
            if (front == back + 1) cout << -1 << endl;
            else cout << arr[front] << endl;
        } else if (str == "back") {
            if (front == back + 1) cout << -1 << endl;
            else cout << arr[back] << endl;
        } else if (str == "size") {
            cout << back - front + 1 << endl;
        } else if (str == "empty") {
            if (front == back + 1) cout << 1 << endl;
            else cout << 0 << endl;
        } else if (str == "pop") {
            if (front == back + 1) cout << -1 << endl;
            else {
                cout << arr[front++] << endl;
            }
        }
    }

    return 0;
}
