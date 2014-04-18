typedef int Weight;
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

//FordFulkerson(O(F|E|))-----------------------------------------------------------
//ノード数|V|が必要
void add_edge(Graph &g, int src, int dest, int cap) {
  g[src].push_back((Edge){src, dest, cap, g[dest].size(), 0});
  g[dest].push_back((Edge){dest, src, 0, g[src].size() - 1, 0});
}

bool visited[V];
int dfs(Graph &g, int v, int t, int f) {
	int (v == t) return f;
	visited[v] = true;
	REP(i, g[v].size()) {
		Edge e = g[v][i];
		if (!visited[e.dest] && e.cap > 0) {
			int d = dfs(g, e.dest, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				g[e.dest][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(Graph &g, int s, int t) {
	int flow = 0;
	for(;;) {
		memset(visited, 0, sizeof(visited));
		int f = dfs(g, s, t, INF);
		if (f == 0) return flow;
		flow += f;
	}
}


// Dinic(O|E||V|^2)-------------------------------------------------------------------
#define RESIDUE(s,t) (cap[s][t]-flow[s][t])
int augment(const Graph &g, const Matrix &cap, Matrix &flow,
            const vector<int> &level, vector<bool> &finished, int u, int t, int cur) {
  if (u == t || cur == 0) return cur;
  if (finished[u]) return 0;
  finished[u] = true;
  FORIT(e, g[u]) if (level[e->dest] > level[u]) {
    int f = augment(g,cap,flow,level,finished,e->dest,t,min(cur,RESIDUE(u, e->dest)));
    if (f > 0) {
      flow[u][e->dest] += f; flow[e->dest][u] -= f;
      finished[u] = false;
      return f;
    }
  }
  return 0;
}
int dinic(const Graph &g, int s, int t) {
  	int n = g.size();
  	Matrix flow(n, Array(n)), cap(n, Array(n)); // adj. matrix
  	REP(u,n) FORIT(e,g[u]) cap
  	[e->src][e->dest] += e->weight;
  
  int total = 0;
  for (bool cont = true; cont; ) {
    cont = false;
    vector<int> level(n, -1); level[s] = 0; // make layered network
    queue<int> q; q.push(s);
    for (int d = n; !q.empty() && level[q.front()] < d; ) {
      	int u = q.front(); q.pop();
      	if (u == t) d = level[u];
      	FORIT(e, g[u]) if (RESIDUE(u,e->dest) > 0 && level[e->dest] == -1)
		q.push(e->dest), level[e->dest] = level[u] + 1;
    }
    vector<bool> finished(n); // make blocking flows
    for (int f = 1; f > 0; ) {
     	 f = augment(g, cap, flow, level, finished, s, t, INF);
      	if (f == 0) break;
      	total += f; cont = true;
    }
  }
  return total;
}

//Minimum_cost_flow(Dijkstra)--------------------------------------------
//頂点数Vが必要

int h[V]                 //ポテンシャル
int dist[V]              //最短距離
int prevv[V], preve[V];  //直前の辺と頂点

void add_edge(int src, int dest, int cap, int weight) {
  g[src].pb((Edge){src, dest, cap, g[dest].size(), weight});
  g[dest].pb((Edge){dest, src, 0, g[src].size() - 1, -weight});
}

int min_cost_flow(int s, int t, int f) {
  int res = 0;
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
          edge &e = g[v][i];
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
      edge &e = g[prevv[v]][preve[v]];
      e.cap -= d;
      g[v][e.rev].cap += d;
    }
  }
  return res;
}



