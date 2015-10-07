//Verified(Code Forces Round 295 Div.1 C)
class UndirectedEulerPath {
public:
  int N;
  vector<int> path;
  vector<multiset<int> > g;

  UndirectedEulerPath(int n) : N(n), g(n) {}
  void add_edge(int x, int y) { g[x].insert(y); g[y].insert(x); }
	
  void dfs(int v) {
    while(g[v].size()) {
      int nv = *g[v].begin();
      g[v].erase(g[v].begin());
      g[nv].erase(g[nv].find(v));
      dfs(nv);
    }
    path.push_back(v);
  }
	
  vector<int> GetPath() {
    int start = 0, odd = 0, cnt = 0;
    REP(i, N) {
      cnt += g[i].size();
      if(g[i].size() % 2) {
	odd++;
	start = i;
      }
    }
    if(odd != 0 && odd != 2) return vector<int>();
    dfs(start);
    reverse(path.begin(), path.end());
    return path.size() == cnt / 2 + 1 ? path : vector<int>();
  }
};

//Not Verified
class DirectedEulerPath {
public:
  int N;
  vector<int> path;
  vector<vector<int> > g;

  DirectedEulerPath(int n) : N(n), g(n) {}
  void add_edge(int x, int y) { g[x].push_back(y); }
	
  void dfs(int v) {
    while(g[v].size()) {
      int nv = g[v].back();
      g[v].pop_back();
      dfs(nv);
    }
    path.push_back(v);
  }
	
  vector<int> GetPath() {
    int start = 0, odd = 0, cnt = 0;
    REP(i, N) {
      cnt += g[i].size();
      if(g[i].size() % 2) {
	odd++;
	start = i;
      }
    }
    if(odd != 0 && odd != 2) return vector<int>();
    dfs(start);
    reverse(path.begin(), path.end());
    return path.size() == cnt + 1 ? path : vector<int>();
  }
};
