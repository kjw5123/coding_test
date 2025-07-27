# 우선순위 큐 정리

```c++
struct cmp {
    bool operator() (const T& a, const T& b) {
        return a > b;  // 이러면 내림차순이 아니라 오름차순이다. sort용 cmp랑 방향 반대다...
    }

priority_queue<T, vector<T>, cmp> pq;  // 이러면 내 입맛대로 우선순위 큐 사용 가능
};
```

# 나중에 다시 풀어야 하는 문제 정리

### 2024번
- [ ] 다시 풀었나요 ?
