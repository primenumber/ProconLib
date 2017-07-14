using Weight = int;
Weight INF = 1000000000;
struct Edge{
  int src, dest; Weight weight;
  bool operator < (const Edge &rhs) const {return weight > rhs.weight;}
};

using Edges = vector<Edge>;
using Graph = vector<Edges>;
using Array = vector<Weight>;
using Matrix = vector<Array>;

void add_edge(Graph &g, int src, int dest, Weight weight) {
  g[src].push_back((Edge){src, dest, weight});
}

// Dijkstra (Verified: AOJ2005)
void dijkstra(Graph &g, Array &d, int s) {
  d.assign(g.size(), INF);
  d[s] = 0;
  using P = pair<Weight,int>;
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
  fill(ALL(d), INF);
  d[s] = 0;
  REP(i, es.size()) {
    Edge e = es[i];
    if (d[e.dest] > d[e.src] + e.weight) {
      d[e.dest] = d[e.src] + e.weight;
      i = -1;
    }
  }
}

// BellmanFord (Negative Cycle)
bool bellman_ford(const Edges &es, Array &d, int s) {
  fill(ALL(d), INF); d[s] = 0;
  REP(i, d.size()) {
    bool updated = false;
    for (Edge e : es) {
      if (d[e.src] < INF && d[e.dest] > d[e.src] + e.weight) {
        d[e.dest] = d[e.src] + e.weight;
        if (i == d.size() - 1) return false;
        updated = true;
      }
    }
    if (!updated) return true;
  }
  return true;
}

// WarshallFloyd
void warshall_floyd(Matrix &g) {
  int n = g.size();
  REP(k,n) REP(i,n) REP(j,n)
    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}

// Shortest Path Faster Algorithm
bool SPFA(const Graph &g, Array &d, int s) {
  const int n = g.size();
  d.assign(n, INF); d[s] = 0;
  vector<int> updated(n, 0);
  vector<bool> inque(n, false);
  queue<int> que;
  que.push(s);
  while (!que.empty()) {
    int from = que.front();
    que.pop();
    inque[from] = false;
    updated[from]++;
    if (updated[from] == n) return false; // negative cycle
    for (Edge e : g[from]) {
      int to = e.dest;
      Weight cost = d[from] + e.weight;
      if (cost < d[to]) {
        d[to] = cost;
        if (!inque[to]) {
          que.push(to);
          inque[to] = true;
        }
      }
    }
  }
  return true;
}

// The costs of edges must be 0 or 1 (Verified: TCO 2014 Round 2C Medium)
void bfs01(Graph &g, vector<int> &d, int s) {
  d.assign(g.size(), INF);
  d[s] = 0;
  using P = pair<Weight,int>;
  deque<P> que;
  que.push_back(P(0, s));
  while (!que.empty()) {
    P top = que.front(); que.pop_front();
    Weight dist = top.first; int v = top.second;
    if (d[v] < dist) continue;
    REP(i, g[v].size()) {
      Edge e = g[v][i];
      if (d[e.dest] > d[v] + e.weight) {
        d[e.dest] = d[v] + e.weight;
        if (e.weight) que.push_back(P(d[e.dest], e.dest));
        else que.push_front(P(d[e.dest], e.dest));
      }
    }
  }
}
