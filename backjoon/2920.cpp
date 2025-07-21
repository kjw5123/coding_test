#include <iostream>
using namespace std;

int main() {
    int arr[8];
    for (int i = 0; i < 8; i++) {
        cin >> arr[i];
    }

    bool isAscending = true;
    bool isDescending = true;

    for (int i = 0; i < 7; i++) {
        if (arr[i] < arr[i+1]) isDescending = false;
        else if (arr[i] > arr[i+1]) isAscending = false;
    }

    if (isAscending) cout << "ascending" << endl;
    else if (isDescending) cout << "descending" << endl;
    else cout << "mixed" << endl;

    return 0;
}
