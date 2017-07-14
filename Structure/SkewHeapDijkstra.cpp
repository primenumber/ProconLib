using Weight = int;
using Data = pair<Weight,int>;

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
  g[dest].push_back((Edge){dest, src, weight});
}

//O(V)-space dijkstra
//G: function object
template<typename G>
void dijkstra(G &g, Array &d, int s) {
  int n=g.size();
  d.assign(n, INF);
  d[s] = 0;
  shared_ptr<Heap> que;
  vector<shared_ptr<Heap>> nodes(n);
  auto p = push(que, Data(0, s));
  que = p.first;
  nodes[s] = p.second;
  while (que) {
    Weight dist = que->top().first;
    int v = que->top().second;
    que = pop(que);
    nodes[v].reset();
    if (d[v] < dist) continue;
    REP(i, g(v).size()) {
      Edge e = g(v)[i];
      if (d[e.dest] > d[v] + e.weight) {
        d[e.dest] = d[v] + e.weight;
        if (!nodes[e.dest]) {
          auto p = push(que, Data(d[e.dest], e.dest));
          que = p.first;
          nodes[e.dest] = p.second;
        } else {
          que = reduce(nodes[e.dest], que, Data(d[e.dest], e.dest));
        }
      }
    }
  }
}
