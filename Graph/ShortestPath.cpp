typedef int Weight;
struct Edge{
  int src, dest; Weight weight;
  bool operator < (const Edge &rhs) const {return weight > rhs.weight;}
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

// Dijkstra (Verified: AOJ2005)
void dijkstra(Graph &g, Array &d, int s) {
  d.assign(g.size(), INF);
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

// Dijkstra (build path version)
vector<Weight> dijkstra(Graph &g, int s, vector<int> &prev) {
  vector<Weight> dist(g.size(), INF); dist[s]=0;
  prev.assign(g.size(), -1);
  priority_queue<Edge> q;
  for(q.push(Edge{-1, s, 0}); !q.empty();) {
    Edge e = q.top(); q.pop();
    if (prev[e.dest] != -1) continue;
    prev[e.dest] = e.src;
    for(Edge f : g[e.dest]) {
      if(dist[f.dest] > e.weight + f.weight) {
        dist[f.dest] = e.weight + f.weight;
        q.push((Edge){f.src, f.dest, e.weight + f.weight});
      }
    }
  }
  return dist;
}

vector<int> buildPath(const vector<int> &prev, int t) {
  vector<int> path;
  for(int u=t;u>=0;u=prev[u]) path.push_back(u);
  reverse(path.begin(), path.end());
  return path;
}

// BellmanFord (Verified: AOJ2005)
void bellman_ford(const Edges &es, Array &d, int s) {
  d.assign(g.size(), INF);
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

// The costs of edges must be 0 or 1 (Verified: TCO 2014 Round 2C Medium)
void bfs01(Graph &g, vector<int> &d, int s) {
  fill(d.begin(), d.end(), INF);
  d[s] = 0;
  typedef pair<Weight,int> P;
  queue<P> que, zero;
  que.push(P(0, s));
  while (!zero.empty() || !que.empty()) {
    P top = zero.empty() ? que.front() : zero.front();
    if (zero.empty()) que.pop(); else zero.pop();
    Weight dist = top.first; int v = top.second;
    if (d[v] < dist) continue;
    REP(i, g[v].size()) {
      Edge e = g[v][i];
      if (d[e.dest] > d[v] + e.weight) {
        d[e.dest] = d[v] + e.weight;
        if (e.weight) que.push(P(d[e.dest], e.dest));
        else zero.push(P(d[e.dest], e.dest));
      }
    }
  }
}
