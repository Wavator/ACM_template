#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct edge {
        int v, w;
        edge (int v = 0, int w = 0): v(v), w(w) {}
};

vector<edge> G[N];

int dist[N];

void spfa(int s, int V) {
    static const int INF = 0x3f3f3f3f;
    static bool inque[N];
    fill(dist,dist+V + 1,INF);
    fill(inque,inque+V + 1,false);
    dist[s]=0;
    static queue<int> que;
    while(!que.empty()) que.pop();
    que.push(s);
    inque[s]=true;
    while(!que.empty()) {
        int u=que.front();
        que.pop();
        for(auto &e: G[u]) {
            if(dist[u]+e.w<dist[e.v]) {
                dist[e.v]=dist[u]+e.w;
                if(!inque[e.v]) {
                    inque[e.v]=true;
                    que.push(e.v);
                }
            }
        }
        inque[u]=false;
    }
}
