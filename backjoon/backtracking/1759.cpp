#include <iostream>

using namespace std;

/* [문제]
 *
 * 누가 열쇠 들고가서 문을 못여는 상황이 됐기에
 * 예방적 차원에서 열쇠 방식이 아닌 암호방식으로 잠금시스템을 변경할 계획임
 *
 * 암호는 L개의 소문자 알파벳으로 구성됐고
 * 최소 1개 모음 (a e i u o) 와 최소 2개 자음으로 구성 됨 
 * 정렬된 문자열을 사랑함 
 *
 * abc는 가능한데 bac는 고려할 필요가 없음 (dfs에 idx 넣어주자)
 *
 * 사용함직한 문자 종류는 c가지가 있다
 * 
 *
 *
 *
 * */ 
int l, c;
int m_cnt, j_cnt; // 모음 수, 자음 수
int alphabet[26];

string result;
bool isMoum(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o') return true;
    return false;
}


void dfs(int idx, int depth) {
    if (depth == l) {
        // cout << "no?" << endl;
        // cout << m_cnt << " " << j_cnt << endl;
        // cout << result << endl;
        if (m_cnt >= 1 && j_cnt >= 2) {
            cout << result << '\n';
            return;

        } else return;
    }

    for (int i = idx+1; i < 26; i++) {
        if(alphabet[i] != 0) {
            char c = char(i + 'a');

            if (isMoum(c)) m_cnt++;
            else j_cnt++;
            result.push_back(c); alphabet[i]--;

            dfs(i, depth+1);

            if (isMoum(c)) m_cnt--;
            else j_cnt--;
            result.pop_back(); alphabet[i]++;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> l >> c;
    char val;
    for (int i = 0; i < c; i++) {
        cin >> val;
        alphabet[val - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        cout << alphabet[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 26; i++) {
        if (alphabet[i] != 0) {
            char c = char(i + 'a');

            if (isMoum(c)) m_cnt++;
            else j_cnt++;
            // cout << "I insert " << c << endl;
            result.push_back(c); alphabet[i]--;

            dfs(i, 1);

            if (isMoum(c)) m_cnt--;
            else j_cnt--;
            result.pop_back(); alphabet[i]++;
        }
    }

    return 0;
}
