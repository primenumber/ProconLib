// Verified: AOJ0273
// any two segments must not cross

vector<vector<int>> polygon;
vector<int> seg2p[1024][1024];
 
Graph dual_graph(const vector<L> &s, const VP &p) {
  int N = p.size();
  polygon.clear();
  REP(i,1024) REP(j,1024) seg2p[i][j].clear();
  vector<vector<tuple<ld,int,bool>>> tup(N);
  REP(i,s.size()) {
    int a = -1, b = -1;
    REP(j,N) if (abs(s[i].a - p[j]) < eps) a = j;
    REP(j,N) if (abs(s[i].b - p[j]) < eps) b = j;
    assert(a >= 0 && b >= 0);
    tup[a].emplace_back(arg(s[i].b - s[i].a), b, false);
    tup[b].emplace_back(arg(s[i].a - s[i].b), a, false);
  }
  REP(i,N) sort(ALL(tup[i]));
  REP(i,N) {
    REP(j,tup[i].size()) {
      ld angle; int pos = j, src = i, dest; bool flag;
      tie(angle, dest, flag) = tup[i][j];
      if (flag) continue;
      vector<int> ps;
      while (!flag) {
        ps.push_back(src);
        get<2>(tup[src][pos]) = true;
        seg2p[src][dest].push_back(polygon.size());
        seg2p[dest][src].push_back(polygon.size());
        angle += pi + eps;
        if (angle > pi) angle -= 2 * pi;
        auto it = lower_bound(ALL(tup[dest]), make_tuple(angle, 0, false));
        if (it == tup[dest].end()) it = tup[dest].begin();
        src = dest; tie(angle, dest, flag) = *it;
        pos = it - tup[src].begin();
      }
      polygon.push_back(ps);
    }
  }
  Graph g(polygon.size());
  REP(i,N) REP(j,i) {
    if (seg2p[i][j].size() == 2) {
      int src = seg2p[i][j][0], dest = seg2p[i][j][1];
      g[src].push_back((Edge){src, dest});
      g[dest].push_back((Edge){dest, src});
    }
  }
  return g;
}
