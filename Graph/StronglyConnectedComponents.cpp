int V;
#define MAX_V 1000

vector<int> g[MAX_V];
vector<int> rg[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];

boid add_edge(int from, int to) {
  g[from].pb(to);
  rg[to].pb(from);
}

void dfs(int v) {
  used[v] = true;
  REP(i, g[v].size()) if (!used[g[v][i]]) dfs(g[v][i]);
  vs.pb(v);
}

void rdfs(int v, int k) {
  used[v] = true;
  cmp[v] = k;
  REP(i, rg[v].size()) if (!used[g[v][i]]) rdfs(rg[v][i], k);
}

int scc(void) {
  memset(used, 0, sizeof(used));
  vs.clear();
  REP(v, V) if (!used[v]) dfs(v);
  memset(used, 0, sizeof(used));
  int k = 0;
  for (int i = vs.size() - 1; i >= 0; i--) if (!used[vs[i]]) rdfs(vs[i], k++);
  return k;
}

