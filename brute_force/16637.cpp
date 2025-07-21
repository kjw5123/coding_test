#include<iostream>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

int n, maxVal;
string str;

int cal(int a, int b, char oper) {
	int result = a;
	switch (oper) {
	case '+':
        result += b;
        break;
	case '*':
        result *= b;
        break;
	case '-':
        result -= b;
        break;
	}
	return result;
}

void dfs(int idx, int cur)
{
	if (idx > n - 1) {
		maxVal = max(maxVal, cur);
		return;
	}
	char oper;
    if (idx == 0) oper = '+';
    else oper = str[idx-1];

	if (idx + 2 < n) {
		int bracket = cal(str[idx] - 48, str[idx + 2] - 48, str[idx + 1]);
		dfs(idx + 4, cal(cur, bracket, oper));
	}
	dfs(idx + 2, cal(cur, str[idx] - 48, oper));
}

int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >> n >> str;

	maxVal = INT_MIN;
	dfs(0, 0);
	cout << maxVal;
	return 0;
}
