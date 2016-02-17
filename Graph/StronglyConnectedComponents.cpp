struct Edge{ int src, dest; };

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

void add_edge(Graph &g, int from, int to) {
  g[from].push_back((Edge){from, to});
}

int scc(Graph &graph, vector<int> &cmp) {
  int V = graph.size();
  vector<vector<int>> g(V), rg(V);
  vector<int> vs;
  vector<bool> used(V, false);
  cmp.resize(V);
  REP(i,V) {
    for (Edge e: graph[i]) {
      g[i].push_back(e.dest);
      rg[e.dest].push_back(i);
    }
  }
  function<void(int)> dfs = [&g, &vs, &used, &dfs](int v) {
    used[v] = true;
    for (int i: g[v]) if (!used[i]) dfs(i);
    vs.push_back(v);
  };
  function<void(int,int)> rdfs = [&rg, &cmp, &used, &rdfs](int v, int k) {
    used[v] = true; cmp[v] = k;
    for (int i: rg[v]) if (!used[i]) rdfs(i, k);
  };
  REP(v,V) if (!used[v]) dfs(v);
  used = vector<bool>(V, false);
  reverse(ALL(vs));
  int k = 0;
  for(int i: vs) if (!used[i]) rdfs(i, k++);
  return k;
}

vector<vector<int>> buildGraph(const Graph &g, const vector<int> &cmp, int K) {
  int V = g.size();
  vector<set<int>> s(K);
  vector<vector<int>> res(K);
  REP(i,V) for (Edge e: g[i]) s[cmp[i]].insert(cmp[e.dest]);
  REP(i,K) for (int j: s[i]) if (i != j) res[i].push_back(j);
  return res;
}
