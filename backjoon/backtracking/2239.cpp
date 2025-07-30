 #include <iostream>
 #include <vector>
 #include <set>
 #include <algorithm>
 #include <utility>
 #include <cstdlib> // ㅎ;;
 using namespace std;

 /* [문제]
  * 스도쿠 할것이다
  * 행, 열, 3x3 격자 내에 1 ~ 9 없게끔 잘 채워보자
  *
  * [사견]
  *
  * 예전에 풀려다가 포기한 기억이 있는데
  * 침착하게, dfs를 한다 쳐보자
  * 0인 경우에 대한걸 vector<pair<int,int>> 에다가 저장해두고
  * 모든 좌표에 대해 dfs를 진행하게끔 할까?
  *
  * */
 int arr[10][10];
 vector<pair<int,int> > zeros;
 set<int> sy[10];  // 행에서 사용 불가능한거 저장하기
 set<int> sx[10];  // 열에서 사용 불가능한거 저장하기
 set<int> sq[10];  // 네모박스에서 사용 불가능한거 저장하기

 void print_arr() {
     for (int i = 1; i <= 9; i++) {
         for (int j = 1; j <= 9; j++) {
             cout << arr[i][j];
         }
         cout << endl;
     }
     cout << endl;
 }

 int get_sq_idx(int i, int j) {
     if ( 1 <= i && i <= 3 && 1 <= j && j <= 3 ) return 1;
     else if (1 <= i && i <= 3 && 4 <= j && j <= 6) return 2;
     else if (1 <= i && i <= 3 && 7 <= j && j <= 9) return 3;
     else if (4 <= i && i <= 6 && 1 <= j && j <= 3) return 4;
     else if (4 <= i && i <= 6 && 4 <= j && j <= 6) return 5;
     else if (4 <= i && i <= 6 && 7 <= j && j <= 9) return 6;
     else if (7 <= i && i <= 9 && 1 <= j && j <= 3) return 7;
     else if (7 <= i && i <= 9 && 4 <= j && j <= 6) return 8;
     else if (7 <= i && i <= 9 && 7 <= j && j <= 9) return 9;
     return -1;
 }

 void dfs(int idx, int depth) {
     if (depth == (int)zeros.size()) {
         print_arr();
         exit(0);  // 어짜피 되는 경우에만 삽입하는거라 이래도 될듯?
         // return;
     }

     int cy = zeros[idx].first;
     int cx = zeros[idx].second;
     int sq_idx = get_sq_idx(cy, cx);

     for (int i = 1; i <= 9; i++) {
         if (sy[cy].count(i) || sx[cx].count(i) || sq[sq_idx].count(i)) continue;
         sy[cy].insert(i);
         sx[cx].insert(i);
         sq[sq_idx].insert(i);
         arr[cy][cx] = i;
         dfs(idx+1,depth+1);
         sy[cy].erase(i);
         sx[cx].erase(i);
         sq[sq_idx].erase(i);
         arr[cy][cx] = 0;

     }
 }

 int main() {
     ios::sync_with_stdio(false);
     cin.tie(NULL);

     char val;
     for (int i = 1; i <= 9; i++) {
         for (int j = 1; j <= 9; j++) {
             cin >> val;
             arr[i][j] = int(val - '0');
             if (int(val-'0') == 0) zeros.push_back({i,j});
             else {
                 sy[i].insert(arr[i][j]);
                 sx[j].insert(arr[i][j]);
                 if ( 1 <= i && i <= 3 && 1 <= j && j <= 3 ) sq[1].insert(arr[i][j]);
                 else if (1 <= i && i <= 3 && 4 <= j && j <= 6) sq[2].insert(arr[i][j]);
                 else if (1 <= i && i <= 3 && 7 <= j && j <= 9) sq[3].insert(arr[i][j]);
                 else if (4 <= i && i <= 6 && 1 <= j && j <= 3) sq[4].insert(arr[i][j]);
                 else if (4 <= i && i <= 6 && 4 <= j && j <= 6) sq[5].insert(arr[i][j]);
                 else if (4 <= i && i <= 6 && 7 <= j && j <= 9) sq[6].insert(arr[i][j]);
                 else if (7 <= i && i <= 9 && 1 <= j && j <= 3) sq[7].insert(arr[i][j]);
                 else if (7 <= i && i <= 9 && 4 <= j && j <= 6) sq[8].insert(arr[i][j]);
                 else if (7 <= i && i <= 9 && 7 <= j && j <= 9) sq[9].insert(arr[i][j]);
             }
         }
     }

     dfs(0,0);
     return 0;
 }
