#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int n;                                  // 테스트 케이스 개수
int alphabet[26];                       // a ~ z까지 호출된 개수 정리
int str_len = 0;                        // 이번에 입력된 문자열 길이 

string result;                          // 진행 상황 따라서 출력할 결과 문자열

void dfs(int depth) {                   // 파라미터는 현재 dfs 호출에 따른 문자열 길이 정보 저장 
    if (depth == str_len) {             // (종료 조건) 입력된 문자열과 동일한 개수일 경우 
        cout << result << '\n';         // 어쨌든 완성 됐으니 출력 
        return;
    }

    for (int i = 0; i < 26; i++) {      // 사전순으로 모든 경우를 출력 해야하니 a ~ z 배열 다 탐색
        if (alphabet[i] != 0) {         // 출력할 게 남이있을 경우 
            result.push_back(i + 'a');  // 문자열에 추가 
            alphabet[i]--;              // 임시로 빼둠 
            dfs(depth+1);               // 재귀 호출
            result.pop_back();          // (위 재귀에서 확인할거 다 했으니) 다시 문자열에서 제거 
            alphabet[i]++;              // 사용한거 다시 채워놓기
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        memset(alphabet, 0x00, sizeof(alphabet));  // 혹시 모르니 매 테스트케이스 시작마다 초기화
        result = "";                               // 얘도 할 필요 없긴 한데 그냥 초기화

        string str;                                // 문자열 입력 받기
        cin >> str;
        str_len = str.length();                    // 문자열 길이 저장 (종료 조건 확인을 위해)

        for (int j = 0; j < str_len; j++) {
            alphabet[str[j]-'a']++;                // a ~ z 호출 개수 정보 저장
        }
        
        dfs(0);                                    // 이번 문자열에 대한 재귀 실시
    }
    return 0;
}
