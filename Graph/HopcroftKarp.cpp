//計算用に１つ頂点が余分に必要(NIL)なことに注意
#define MAX_V 100001
vector<int> g[MAX_V];
int V1, V2, NIL, match[MAX_V], d[MAX_V];
 
void add_edge(int u, int v) {
  g[u].push_back(v);
  g[v].push_back(u);
}
 
bool bfs() {
  queue<int> que;
  fill(d, d + V1, INF);
  REP(i, V1) if(match[i] == NIL) {
    d[i] = 0;
    que.push(i);
  }
  d[NIL] = INF;
  while(!que.empty()) {
    int u = que.front(); que.pop();
    if(u != NIL) {
      for (int v : g[u]) {
	if(d[match[v]] == INF) {
	  d[match[v]] = d[u] + 1;
	  que.push(match[v]);
	}
      }
    }
  }
  return (d[NIL] != INF);
}

bool dfs(int u) {
  if(u != NIL) {
    for (int v : g[u]) {
      if(d[match[v]] == d[u] + 1) {
	if(dfs(match[v])) {
	  match[v] = u;
	  match[u] = v;
	  return true;
	}
      }
    }
    d[u] = INF;
    return false;
  }
  return true;
}

int bipartite_matching(int v1, int v2) {
    int matching = 0;
    V1 = v1, V2 = v2, NIL = V1 + V2;
    REP(i, V1 + V2) match[i] = NIL;
    while(bfs()) REP(i, V1) if(match[i] == NIL && dfs(i)) matching++;
    return matching;
}
