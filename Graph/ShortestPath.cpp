typedef int Weight;
struct Edge{
  int src, dest; Weight weight;
  //bool operator < (const Edge &rhs) const {return weight > rhs.weight;}
};
//(Edge){src, dest, weight}でインスタンス化できる

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

// Dijkstra (Verified: AOJ2005)
// dの要素数は頂点数と等しくあるべき．
void dijkstra(Graph &g, Array &d, int s) {
  fill(d.begin(), d.end(), INF);
  d[s] = 0;
  typedef pair<Weight,int> P;
  priority_queue<P, vector<P>, greater<P> > que;
  que.push(P(0, s));
  while (!que.empty()) {
    Weight dist = que.top().first;
    int v = que.top().second;
    que.pop();
    if (d[v] < dist) continue;
    REP(i, g[v].size()) {
      Edge e = g[v][i];
      if (d[e.dest] > d[v] + e.weight) {
        d[e.dest] = d[v] + e.weight;
        que.push(P(d[e.dest], e.dest));
      }
    }
  }
}

// BellmanFord (Verified: AOJ2005)
// esは辺集合．dの要素数は頂点数と等しくあるべき．
void bellman_ford(const Edges &es, Array &d, int s) {
  fill(d.begin(), d.end(), INF);
  d[s] = 0;
  REP(i, es.size()) {
    Edge e = es[i];
    if (d[e.dest] > d[e.src] + e.weight) {
      d[e.dest] = d[e.src] + e.weight;
      i = -1;
    }
  }
}

// WarshallFloyd
void warshall_floyd(Matrix &g) {
  int n = g.size();
  REP(k,n) REP(i,n) REP(j,n)
    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}
