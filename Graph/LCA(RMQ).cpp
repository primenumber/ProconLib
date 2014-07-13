#define MAX_V 100
int root, V;

vector<int> g[MAX_V];
int vs[2 * MAX_V - 1];
int depth[2 * MAX_V - 1];
int id[MAX_V];

void dfs(int v, int p, int d, int &k) {
  id[v] = k;
  vs[k] = v;
  depth[k++] = d;
  REP(i, g.size()) {
    if (g[v][i] != p) {
      dfs(g[v][i], v, d + 1, k);
      vs[k] = v;
      depth[k++] = d;
    }
  }
}

void init(void) {
  int k = 0;
  dfs(root, -1, 0, k);
  rmq_init(depth, 2 * V - 1);
}

int lca(int u, int v) {
  return vs[query(min(id[u], id[v]) , max(id[u], id[v]) + 1)];
}
