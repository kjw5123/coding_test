#include <iostream>
#include <cmath>
#include <string>

using namespace std;


int main() {
    // M = 1, K = 5
    // MM = 10, MK = 50
    // MMM = 100, MMK = 500
    string str;
    cin >> str;
    // 변환 시 가장 큰 수와 가장 작은 수 출력하기
    // 가장 큰 수가 되려면 앞자리가 어쨌든 5가 돼야함
    // M 스택 쌓다가 K 나왔을 때 싹 다 500... 때려박게끔 하기
    // K가 안나왔으면 다 자릿수만큼 100....으로 채워넣기
    
    // 작은건 뭐 작정하고 매 숫자마다 끊어서 처리하면 될듯
    // string parsed_str;
    int m_cnt = 0;
    string big;
    string small;
    // 1. k가 나오면 m_cnt 개수 확인하고 to_string(5 * (long long int)pow(10, m_cnt))
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'M') m_cnt++;
        else {
            big.push_back('5');
            for (int j = 0; j < m_cnt; j++) {
                big.push_back('0');
            }
            m_cnt = 0;
        }
    }
    if (m_cnt != 0) {
        for (int i = 0; i < m_cnt; i++) {
            big.push_back('1');
        }
    }
    
    // 2. 짧게 짤라치기
    // 단, M류는 m_cnt보고 묶는게 더 싸게 먹힌다
    m_cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'K') {
            if (m_cnt != 0) {
                small.push_back('1');
                for (int j = 0; j < m_cnt-1; j++) small.push_back('0');
            }
            m_cnt = 0;
            small.push_back('5');
        }
        else m_cnt++;
    }
    if (m_cnt != 0) {
        small.push_back('1');
        for (int i = 0; i < m_cnt - 1; i++) {
            small.push_back('0');
        }
    }
    cout << big << '\n' << small << endl;
    return 0;
}
