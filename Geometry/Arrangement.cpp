void add_point(vector<P> &ps, P p) {
  for (P q : ps) if (abs(q - p) < eps) return;
  ps.push_back(p);
}

// Verified: AOJ1279
Graph segmentArrangement(const vector<L> &s, const vector<P> &p) {
  int n = p.size(), m = s.size();
  Graph g(n);
  REP(i,m) {
    vector<pair<ld,int>> vec;
    REP(j,n) if (isis_sp(s[i], p[j]))
      vec.emplace_back(abs(s[i].a - p[j]), j);
    sort(ALL(vec));
    REP(j,vec.size()-1) {
      int src = vec[j].second, dest = vec[j+1].second;
      add_edge(g, src, dest, abs(p[src] - p[dest]));
    }
  }
  return g;
}

// Not Verified Yet
Graph circleArrangement(const vector<C> &c, const vector<P> &p) {
  int n = p.size(), m = c.size();
  Graph g(n);
  REP(i,m) {
    vector<pair<ld,int>> vec;
    REP(j,n) if (abs(abs(c[i].p - p[j]) - c[i].r) < eps)
      vec.emplace_back(arg(c[i].p - p[j]), j);
    sort(ALL(vec));
    REP(j,vec.size()-1) {
      int src = vec[j].second, dest = vec[j+1].second;
      ld angle = vec[j+1].first - vec[j].first;
      add_edge(g, src, dest, angle * c[i].r);
    }
    if (vec.size() >= 2) {
      int src = vec.back().second, dest = vec.front().first;
      ld angle = vec.front().first - vec.back().first;
      add_edge(g, src, dest, angle * c[i].r);
    }
  }
  return g;
}
