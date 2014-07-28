#define MAX_V 10000
int V;

typedef int Weight;
const Weight INF = 1000000000;

struct Edge{
  int src, dest;
  int cap, rev;
  Weight weight;
  bool operator < (const Edge &rhs) const {return weight > rhs.weight;}
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

Weight h[MAX_V];                // potential
Weight dist[MAX_V];             // minimum distance
int prevv[MAX_V], preve[MAX_V]; // previous vertex and edge

void add_edge(Graph &g, int src, int dest, int cap, int weight) {
  g[src].push_back((Edge){src, dest, cap, (int)g[dest].size(), weight});
  g[dest].push_back((Edge){dest, src, 0, (int)g[src].size() - 1, -weight});
}

Weight min_cost_flow(Graph &g, int s, int t, int f) {
  Weight res = 0; V = g.size();
  memset(h, 0, sizeof(h));
  typedef pair<Weight, int> P;
  while (f > 0) {
    priority_queue<P, vector<P>, greater<P> > que;
    fill(dist, dist + V, INF);
    dist[s] = 0;
    que.push(P(0, s));
    while (!que.empty()) {
      P p = que.top(); que.pop();
      int v = p.second; 
      if (dist[v] < p.first) continue;
      REP(i, g[v].size()) {
        Edge &e = g[v][i];
        if (e.cap > 0 && dist[e.dest] > dist[v] + e.weight + h[v] - h[e.dest]) {
          dist[e.dest] = dist[v] + e.weight + h[v] - h[e.dest];
          prevv[e.dest] = v;
          preve[e.dest] = i;
          que.push(P(dist[e.dest], e.dest));
        }
      }
    }
    if (dist[t] == INF) return -1;
    REP(v, V) h[v] += dist[v];

    int d = f;
    for (int v = t; v != s; v = prevv[v]) d = min(d, g[prevv[v]][preve[v]].cap);
    f -= d;
    res += d * h[t];
    for (int v = t; v != s; v = prevv[v]) {
      Edge &e = g[prevv[v]][preve[v]];
      e.cap -= d;
      g[v][e.rev].cap += d;
    }
  }
  return res;
}
