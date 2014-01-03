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
	priority_queue<PII, vector<PII>, greater<PII> > que;
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
void warshall_floyd(Matrix &g, vector<Weight> d) {
	REP(k, g.size()) REP(i, g.size()) REP(j, g.size()) {
		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	}
}

