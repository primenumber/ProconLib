void clearScc() {
  REP(i,MAX_V) g[i].clear();
  REP(i,MAX_V) rg[i].clear();
}

Weight MinimumArborescence(const Graph &g, int root) {
  const int n = g.size();
  Weight res = 0;
  vector<Weight> c(n, INF);
  vector<int> p(n, -1);
  for (int from = 0; from < n; from++) {
    for (Edge e : g[from]) {
      if (e.dest == from) continue;
      if (e.weight < c[e.dest]) p[e.dest] = from, c[e.dest] = e.weight;
      c[e.dest] = min(c[e.dest], e.weight);
    }
  }
  Graph ng(n);
  clearScc();
  for (int i = 0; i < n; i++) {
    if (i == root) continue;
    if (p[i] == -1) return INF;
    ng[p[i]].push_back((Edge){p[i], i, 0});
    add_edge(p[i], i);
    res += c[i];
  }
  int V = scc(n);
  vector<vector<int>> connect(V);
  REP(i,n) connect[cmp[i]].push_back(i);
  int m = connect.size();
  if (m == n) return res;
  vector<int> mapto(n, -1);
  vector<int> cycle(n, 0);
  res = 0;
  REP(i,m) {
    REP(j,connect[i].size()) {
      mapto[connect[i][j]] = i;
      if (connect[i].size() != 1)
        cycle[connect[i][j]] = 1, res += c[connect[i][j]];
    }
  }
  ng = Graph(m);
  for (int from = 0; from < n; from++) {
    for (Edge e : g[from]) {
      Weight cost = e.weight;
      if (e.dest == root || mapto[from] == mapto[e.dest]) continue;
      if (cycle[e.dest]) cost -= c[e.dest];
      ng[mapto[from]].push_back((Edge){mapto[from], mapto[e.dest], cost});
    }
  }
  return min(INF, res + MinimumArborescence(ng, mapto[root]));
}
