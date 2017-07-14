#define MAX_V 1000
struct Edge{
  int src, dest;
  int cap, rev;
};

const int INF = 1000000000;

using Edges = vector<Edge>;
using Graph = vector<Edges>;
bool visited[MAX_V];

void add_edge(Graph &g, int src, int dest, int cap) {
  g[src].push_back((Edge){src, dest, cap, (int)g[dest].size()});
  g[dest].push_back((Edge){dest, src, 0, (int)g[src].size() - 1});
}

int dfs(Graph &g, int v, int t, int f) {
  if (v == t) return f;
  visited[v] = true;
  REP(i, g[v].size()) {
    Edge &e = g[v][i];
    if (!visited[e.dest] && e.cap > 0) {
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

int max_flow(Graph &g, int s, int t) {
  int flow = 0;
  for(;;) {
    memset(visited, 0, sizeof(visited));
    int f = dfs(g, s, t, INF);
    if (f == 0) return flow;
    flow += f;
  }
}
