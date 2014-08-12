#define MAX_V 1024

vector<int> g[MAX_V], rg[MAX_V], vs;
bool used[MAX_V];
int cmp[MAX_V];

void add_edge(int from, int to) {
  g[from].push_back(to);
  rg[to].push_back(from);
}

void dfs(int v) {
  used[v] = true;
  for (int i : g[v]) if (!used[i]) dfs(i);
  vs.push_back(v);
}

void rdfs(int v, int k) {
  used[v] = true; cmp[v] = k;
  for (int i : rg[v]) if (!used[i]) rdfs(i, k);
}

int scc(int V) {
  memset(used, 0, sizeof(used));
  vs.clear();
  REP(v, V) if (!used[v]) dfs(v);
  memset(used, 0, sizeof(used));
  reverse(ALL(vs));
  int k = 0;
  for (int i : vs) if (!used[i]) rdfs(i, k++);
  return k;
}

vector<vector<int>> buildGraph(int V, int K) {
  vector<set<int>> s(K);
  vector<vector<int>> res(K);
  REP(i,V) for (int j : g[i]) s[cmp[i]].insert(cmp[j]);
  REP(i,K) for (int j : s[i]) if (i != j) res[i].push_back(j);
  return res;
}
