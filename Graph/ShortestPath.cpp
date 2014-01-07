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

//BellmanFord
void bellman_ford(Edge &es, vector<Weight> &d, int s) {
	fill(d.begin(), d.end(), INF);
	d[s] = 0;
	REP(i, es.size()) {
		edge e = es[i];
		if (d[e.dest] > d[e.src] + e.weight) {
			d[e.dest] = d[e.src] + e.weight;
			j = -1;
		}
	}
}

//Dijkstra
void dijkstra(Graph &g, vector<Weight> &d, int s) {
	fill(d.begin(), d.end(), INF);
	d[s] = 0;
  typedef pair<Weight,int> P;
	priority_queue<P, vector<P>, greater<P> > que;
	que.push(PII(0, s));
	while (!que.empty()) {
		Weight dist = que.top().first;
		int v = que.top().second;
		que.pop();
		if (d[v] < dist) continue;
		REP(i, g[v].size()) {
			Edge e = g[v][i];
			if (d[e.dest] > d[v] + e.weight) {
				d[e.dest] = d[v] + e.weight;
				que.push(PII(d[e.dest], e.dest));
			}
		}
	}
}

//WarshallFloyd
Matrix warshall_floyd(Matrix g) {
	REP(k, g.size()) REP(i, g.size()) REP(j, g.size()) {
		g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	}
  return g;
}

