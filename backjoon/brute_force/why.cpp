#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, h, d, k;
int sy, sx, ey, ex;
bool arr[501][501][11];
bool visited[501][501][11];

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

struct man{int y,x,mh,uh,used_um,t;};

void bfs(){
    queue<man> q;
    if(arr[sy][sx][0]){ q.push({sy,sx,h,d,1,0}); visited[sy][sx][1]=true; }
    else               { q.push({sy,sx,h,0,0,0}); visited[sy][sx][0]=true; }

    while(!q.empty()){
        int cy=q.front().y , cx=q.front().x;
        int cmh=q.front().mh, cuh=q.front().uh;
        int cuu=q.front().used_um, ct=q.front().t; q.pop();

        if(cy==ey && cx==ex){ cout<<ct<<'\n'; return; }

        for(int dir=0;dir<4;++dir){
            int ny=cy+dy[dir], nx=cx+dx[dir];
            if(ny<=0||ny>n||nx<=0||nx>n) continue;

            int nmh=cmh, nuh=cuh, nuu=cuu, nt=ct+1;

            /* ① 먼저 우산 교체 */
            if(ny == ey && nx == ex){ cout << nt << '\n'; return; }
            if(arr[ny][nx][nuu]){ ++nuu; nuh=d; }

            /* ② 그다음 비 맞기 */
            if(nuh>0) --nuh;
            else      --nmh;

            /* ③ 사망·조건 체크 */
            if(nmh<=0)        continue;
            if(nuu>k)         continue;
            if(visited[ny][nx][nuu]) continue;

            visited[ny][nx][nuu]=true;
            q.push({ny,nx,nmh,nuh,nuu,nt});
        }
    }
    cout<<-1<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>h>>d;
    char val;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cin>>val;
            if(val=='.') continue;
            else if(val=='S'){ sy=i; sx=j; }
            else if(val=='E'){ ey=i; ex=j; }
            else if(val=='U'){ for(int t=0;t<=10;++t) arr[i][j][t]=true; ++k; }
        }
    }
    bfs();
    return 0;
}

