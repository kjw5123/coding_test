#include <iostream>
#include <utility>

using namespace std;
char l , r;
int dist = 0;
pair<int, int> l_idx, r_idx;

char arr[3][10] = {{'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
                   {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0},
                   {'z', 'x', 'c', 'v', 'b', 'n', 'm',  0,   0,  0}
                  };

void findIdx(char c) {
    pair<int, int> p;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (c == arr[i][j]) {
                p.first = i; 
                p.second = j;
                break;
            }
        }
    }

    if (l_idx == p || r_idx == p) {
        dist += 1; return;
    } 

    if (p.first == 0) {
        if (p.second <= 4) {
            dist += abs(l_idx.first - p.first) + abs(l_idx.second - p.second) + 1;
            l_idx = p;
        } else {
            dist += abs(r_idx.first - p.first) + abs(r_idx.second - p.second) + 1;
            r_idx = p;

        }

    } else if (p.first == 1) {
        if (p.second <= 4) {
            dist += abs(l_idx.first - p.first) + abs(l_idx.second - p.second) + 1;
            l_idx = p;
        } else {
            dist += abs(r_idx.first - p.first) + abs(r_idx.second - p.second) + 1;
            r_idx = p;

        }

    } else if (p.first == 2) {
        if (p.second <= 3) {
            dist += abs(l_idx.first - p.first) + abs(l_idx.second - p.second) + 1;
            l_idx = p;

        } else {
            dist += abs(r_idx.first - p.first) + abs(r_idx.second - p.second) + 1;
            r_idx = p;

        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    cin >> l >> r;
    cin >> str;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (arr[i][j] == l) l_idx = {i, j};
            else if (arr[i][j] == r) r_idx = {i, j};
        }
    }
    // i = 0일 때 0~4가 자음
    // i = 1일 때 0~4가 자음
    // i = 2일 때 0~3가 자음
    int idx = 0;
    while(idx < (int)str.length()) {
        findIdx(str[idx++]);
    }

    cout << dist << endl;
    return 0;
}
