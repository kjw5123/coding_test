#include <iostream>

using namespace std;

int return_val(char c) {
    if (65 <= c && c <= 67) {
        return 2;
    } else if (68 <= c && c <= 70) {
        return 3;
    } else if (71 <= c && c <= 73) {
        return 4;
    } else if (74 <= c && c <= 76) {
        return 5;
    } else if (77 <= c && c <= 79) {
        return 6;
    } else if (80 <= c && c <= 83) {
        return 7;
    } else if (84 <= c && c <= 86) {
        return 8;
    } else if (87 <= c && c <= 90) {
        return 9;
    }
    return -1;
}

int main() {
    string str;
    cin >> str;

    string num_str;
    
    for (int i = 0; i < str.length(); i++) {
        num_str.push_back(return_val(str[i]) + 48);  // string == vector<char> 라고 하네요잉
    }
    
    int time = 0;
    for (int i = 0; i < num_str.length(); i++) {
        int now_num = num_str[i] - 48;
        time += now_num + 1;
    }

    cout << time << endl;
    
    return 0;
}
