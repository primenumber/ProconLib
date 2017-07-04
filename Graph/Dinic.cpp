#define MAX_V 500

struct Edge{
  int src, dest;
  int cap, rev;
};

using Edges = vector<Edge>;
using Graph = vector<Edges>;

int d[MAX_V];
int iter[MAX_V];

void add_edge(Graph &g, int src, int dest, int cap) {
  g[src].push_back((Edge){src, dest, cap, (int)g[dest].size()});
  g[dest].push_back((Edge){dest, src, 0, (int)g[src].size() - 1});
}

void bfs(Graph &g, int s) {
  memset(d, -1, sizeof(d));
  queue<int> que;
  d[s] = 0;
  que.push(s);
  while(!que.empty()) {
    int v = que.front(); que.pop();
    REP(i, g[v].size()) {
      Edge &e = g[v][i];
      if (e.cap > 0 && d[e.dest] < 0) {
        d[e.dest] = d[v] + 1;
        que.push(e.dest);
      }
    }
  }
}

int dfs(Graph &g, int v, int t, int f) {
  if (v == t) return f;
  for (int &i = iter[v]; i < g[v].size(); i++) {
    Edge &e = g[v][i];
    if (e.cap > 0 && d[v] < d[e.dest]) {
      int d = dfs(g, e.dest, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        g[e.dest][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(Graph g, int s, int t) {
  int flow = 0;
  for (;;) {
    bfs(g, s);
    if (d[t] < 0) return flow;
    memset(iter, 0, sizeof(iter));
    int f;
    while ((f = dfs(g, s, t, INF)) > 0) flow += f;
  }
}
