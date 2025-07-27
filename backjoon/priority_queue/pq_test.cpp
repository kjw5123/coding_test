#include <iostream>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

struct cmp {
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.first > p2.first;
    }
};

int main() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
    pq.push({123, 1});
    pq.push({456, 2});
    pq.push({1, 3});
    while(!pq.empty()) {cout << pq.top().first << " "; pq.pop();}
    return 0;
}
