#include <iostream>
#include <cmath>
using namespace std;

long long int power(long long int A, long long int B, long long C) {
    if (B == 0) return 1;
    long long int half = power(A, B/2, C);
    long long int result = ((half) * (half)) % C;
    if (B % 2 == 1) result = (result * A) % C;
    return result;
}

int main() {
    long long int A, B, C;
    cin >> A >> B >> C;
    
    // 10을 11번 곱한 수를 12로 나눠보자...
    // 10       0 
    // 100      96
    // 1000     960 36
    // 10000    9600 360 36
    // 100000   96000 3600 360 36 ...
    //
    // 11 11 13
    // 11       0     11
    // 121      117   (4)
    // 1331     1287 39 (5)
    // 14641    14157 429 52 (3)
    // 161051   7
    // 1771561  12
    //          2
    //          9
    //          8
    //          10
    //          6
    //          1
    //
    //          4
    //          ...
    //
    
    // 1 1 1 1 1 
    // 2 4 8 16 32 64 
    //
    // 제곱 수야 뭐 어찌됐든 자기 자신 곱하는거이고 
    // 나누는 수는 
    // 아니 근데 전부 다 랜덤이면 어캐 일반화하지? 
    // 걍 math 관련 문제는 어지간히 시간 오래걸린다 싶으면 재귀로 좀 할 수 있으면 해보자 
    long long int result = power(A, B, C);
    cout << result << endl;
    return 0;
}
