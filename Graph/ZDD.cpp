/*
#include <bits/stdc++.h>

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(),(x).end()

using namespace std;

using Mod = long long;
*/

struct Edge{ int src, dest; };

using Edges = vector<Edge>;
using Graph = vector<Edges>;

void add_edge(Graph &g, int src, int dest) {
  g[src].push_back((Edge){src, dest});
  g[dest].push_back((Edge){dest, src});
}

Mod zdd(const Graph &g, int s, int t) {
  int N = g.size();
  vector<vector<int>> tr(N);
  vector<int> pos(N, -1);
  queue<int> que;
  pos[s] = 0; que.push(s);
  int cnt = 0;
  while (!que.empty()) {
    int v = que.front(); que.pop();
    for (Edge e: g[v]) {
      int w = e.dest;
      if (pos[w] != -1) continue;
      que.push(w);
      ++cnt; pos[w] = cnt;
    }
  }
  REP(i,N) assert(pos[i] != -1); // assert
  REP(i,N) for (Edge e: g[i])
    if (pos[e.src] < pos[e.dest])
      tr[pos[e.src]].push_back(pos[e.dest]);
  Mod res = 0;
  map<pair<int,vector<int>>,Mod> memo;
  for (int i: tr[0]) {
    vector<int> init(N, -1);
    init[0] = i; init[i] = 0;
    memo[make_pair(1, init)] = Mod(1);
  }
  for (auto it = memo.begin(); (it->first).first < N; ++it) {
    int v = (it->first).first;
    vector<int> mate = (it->first).second;
    Mod cnt = it->second;
    if (mate[v] == -2) {
      memo[make_pair(v+1, mate)] += cnt;
    }
    else if (mate[v] == -1) {
      mate[v] = -2;
      memo[make_pair(v+1, mate)] += cnt;
      for(int a: tr[v]) {
        for (int b: tr[v]) {
          if (a == b) break;
          if (mate[a] == -2 || mate[b] == -2 || mate[a] == b) continue;
          vector<int> nx = mate;
          nx[v] = -2;
          if (nx[a] == -1) {
            if (nx[b] == -1) { nx[a] = b; nx[b] = a; }
            else { nx[a] = nx[b]; nx[nx[b]] = a; nx[b] = -2; }
          }
          else {
            if (nx[b] == -1) { nx[b] = nx[a]; nx[nx[a]] = b; nx[a] = -2; }
            else { swap(nx[nx[a]], nx[nx[b]]); nx[a] = -2; nx[b] = -2; }
          }
          memo[make_pair(v+1, nx)] += cnt;
        }
      }
    }
    else {
      if (v == pos[t]) res += cnt;
      for(int a: tr[v]) {
        if (mate[a] == -2) continue;
        if (mate[a] == -1) {
          vector<int> nx = mate;
          nx[nx[v]] = a; nx[a] = nx[v]; nx[v] = -2;
          memo[make_pair(v+1, nx)] += cnt;
        }
        else {
          if (mate[v] == a) continue;
          vector<int> nx = mate;
          nx[nx[a]] = nx[v]; nx[nx[v]] = nx[a];
          nx[a] = -2; nx[v] = -2;
          memo[make_pair(v+1, nx)] += cnt;
        }
      }
    }
  }
  return res;
}

/*
int main() {
  for (int n = 1; n <= 8; ++n) {
    int N = n + 1;
    Graph g(N * N);
    REP(i,N) REP(j,N-1) add_edge(g, i*N+j, i*N+j+1);
    REP(i,N-1) REP(j,N) add_edge(g, i*N+j, (i+1)*N+j);
    Mod res = zdd(g, 0, N*N-1);
    cout << n << " x " << n << " : " << res << endl;
  }
  return 0;
}
*/

