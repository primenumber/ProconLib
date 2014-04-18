#define MAX_V 1000000
int V;

vector<int> g[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void add_edge(int u, int v) {
  g[u].pb(v);
  g[v].pb(u);
}

bool dfs(int v) {
  used[v] = true;
  REP(i, g[v].size()) {
    int u = g[v][i], w = match[u];
    if (w < 0 || (!used[w] && dfs(w))) {
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

int bipartite_matching(void) {
  int res = 0;
  memset(match, -1, sizeof(match));
  REP(v, V) {
    if (match[v] < 0) {
      memset(used, 0, sizeof(used));
      if (dfs(v)) res++;
    }
  }
  return res;
}