typedef int Weight;
struct Edge { int src, dest; };
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

void add_edge(Graph &g, int src, int dest) {
  g[src].push_back((Edge){src, dest});
  g[dest].push_back((Edge){dest, src});
}

struct LCA {
  int V, LOG_V;
  vector<vector<int>> parent;
  vector<int> depth;
  void dfs(const Graph &g, int v, int p, int d) {
    parent[0][v] = p; depth[v] = d;
    for (Edge e: g[v]) if (e.dest != p) dfs(g, e.dest, v, d + 1);
  }
  LCA(const Graph &g, int root) : V(g.size()), LOG_V(0), depth(V, 0) {
    for (int v = V; v > 0; v >>= 1) ++LOG_V;
    parent.assign(LOG_V, vector<int>(V, 0));
    dfs(g, root, -1, 0);
    REP(k, LOG_V - 1) REP(v, V) {
      if (parent[k][v] < 0) parent[k + 1][v] = -1;
      else parent[k + 1][v] = parent[k][parent[k][v]];
    }
  }
  int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    REP(k, LOG_V) if (((depth[v] - depth[u]) >> k) & 1) v = parent[k][v];
    if (u == v) return u;
    for (int k = LOG_V - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }
};
