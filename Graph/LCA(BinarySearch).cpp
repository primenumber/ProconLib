//==============================
#define MAX_V 100000
#define LOG_V 17
int root, V;
vector<int> g[MAX_V];
//==============================
int parent[LOG_V][MAX_V];
int depth[MAX_V];

void dfs(int v, int p, int d) {
  parent[0][v] = p;
  depth[v] = d;
  REP(i, g[v].size()) if (g[v][i] != p) dfs(g[v][i], v, d + 1);
}

void init(void) {
  dfs(root, -1, 0);
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