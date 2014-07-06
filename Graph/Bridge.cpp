
// Bridge

struct Edge{ int src, dest; };

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

Edges edges;
vector<vector<int> > connect;
vector<int> roots, st, order;
int cnt;

void bridgeDfs(const Graph &g, int from, int parent) {
  order[from] = cnt++;
  st.push_back(from);
  roots.push_back(from);
  for (Edge e : g[from]) {
    int to = e.dest;
    if (to == parent) continue;
    if (order[to] == -1) {
      bridgeDfs(g, to, from);
    }
    else {
      while (order[roots.back()] > order[to]) roots.pop_back();
    }
  }
  if (from == roots.back()) {
    edges.push_back(Edge{parent, from});
    connect.push_back(vector<int>());
    while (true) {
      int w = st.back();
      st.pop_back();
      connect.back().push_back(w);
      if (from == w) break;
    }
    roots.pop_back();
  }
}

Edges bridge(const Graph &g) {
  const int n = g.size();
  edges.clear(); connect.clear();
  roots.clear(); st.clear(); order.assign(n, -1);
  cnt = 0;
  for (int i = 0; i < n; i++) {
    if (order[i] != -1) continue;
    bridgeDfs(g, i, i);
    edges.pop_back();
  }
  return edges;
}
