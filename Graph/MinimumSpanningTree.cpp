typedef int Weight;
struct Edge{
  int src, dest; Weight weight;
  bool operator < (const Edge &rhs) const {return weight > rhs.weight;}
};

typedef vector<Edge> Edges;

// Kruskal
// N, operator <
Edges kruskal(int V, Edges &es) {
  sort(es.rbegin(), es.rend());
  UnionFind uf(V);
  Edges res;
  REP(i, es.size()) {
    Edge e = es[i];
    if(uf.root(e.src) != uf.root(e.dest)) {
      uf.merge(e.src, e.dest);
      res.push_back(e);
    }
  }
  return res;
}

Edges prim(Graph &g){
  Edges res;
  vector<int> visited(g.size(), 0);
  priority_queue<Edge> q;
  q.push((Edge){-1, 0, 0});
  while (!q.empty()) {
    Edge e = q.top();
    q.pop();
    if (visited[e.dest]) continue;
    if (e.src >= 0) res.push_back(e);
    visited[e.dest] = 1;
    for (Edge i : g[e.dest]) if(visited[i.dest] == 0) q.push(i);
  }
  sort(res.rbegin(), res.rend());
  return res;
}
