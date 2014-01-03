typedef int Weight;
struct Edge{
  	int src, dest;
  	int cap, flow, rev;
  	Weight weight;
  	bool operator < (const Edge &rhs) const {return weight > rhs.weight;}
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

//FordFulkerson
//ノード数|V|が必要
void add_edge(Graph &g, int src, int dest, int cap) {
  G[src].push_back((edge){src, dest, cap, 0, G[to].size(), 0});
  G[dest].push_back((edge){dest, src, 0, 0, G[from].size() - 1, 0});
}

bool visited[V];
int dfs(Graph &g, int v, int t, int f) {
	int (v == t) return f;
	visited[v] = true;
	REP(i, g[v].size()) {
		edge e = g[v][i];
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
		int f - dfs(g, t, INF);
		if (f == 0) return flow;
		flow += f;
	}
}


// Dinic
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

// BipartiteMatching
bool augment(const Graph& g, int u, vector<int>& matchTo, vector<bool>& visited) {
  	if (u < 0) return true;
  	FOR(e, g[u]) if (!visited[e->dst]) {
    	visited[e->dst] = true;
    	if (augment(g, matchTo[e->dst], matchTo, visited)) {
      		matchTo[e->src] = e->dst;
      		matchTo[e->dst] = e->src;
      		return true;
    	}
  	}
  	return false;
}
int bipartiteMatching(const Graph& g, int L, Edges& matching) {
  const int n = g.size();
  vector<int> matchTo(n, -1);
  int match = 0;
  REP(u, L) {
    vector<bool> visited(n);
    if (augment(g, u, matchTo, visited)) ++match;
  }
  REP(u, L) if (matchTo[u] >= 0) // make explicit matching
    matching.push_back( Edge(u, matchTo[u]) );
  return match;
}

// Bipartite matching(vector)

const int INF = 9999;

void add_edge(vvi &vg, int f, int t) {
    vg[f].push_back(t);
    vg[t].push_back(f);
}

int pair_val[200], dist_val[220];
bool dfs(vvi &vg, int j, int nil) {
    if (j == nil) return true;
    FORIT(it, vg[j]) {
        if (dist_val[pair_val[*it]] == dist_val[j] + 1 &&
            dfs(vg, pair_val[*it], nil)) {
            pair_val[*it] = j, pair_val[j] = *it;
            return true;
        }
    }
    dist_val[j] = INF;
    return false;
}


