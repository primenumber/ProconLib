struct Edge{ int src, dest; };

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

void add_edge(Graph &g, int src, int dest) {
  g[src].push_back((Edge){src, dest});
}
int update(const Graph &g, vector<int> &res, int v) {
  for (auto e: g[v]) {
    if (res[e.dest] == -1) {
      res[v] = 1;
      return 1;
    }
  }
  res[v] = -1;
  return 1e9;
}

void recession(const Graph &g, vector<int> &res) {
  assert(g.size() == res.size());
  int n = g.size();
  vector<vector<int>> rg(n);
  for (int i = 0; i < n; ++i)
    for (auto e: g[i]) rg[e.dest].push_back(i);
  vector<int> cnt(n);
  REP(i,n) cnt[i] = g[i].size();
  queue<int> que;
  REP(i,n) if (cnt[i] == 0) que.push(i);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    int c = update(g, res, v);
    for (int i: rg[v]) {
      if (res[i] != 0) continue;
      if (cnt[i] <= 0) continue;
      cnt[i] -= c;
      if (cnt[i] <= 0) que.push(i);
    }
  }
}
