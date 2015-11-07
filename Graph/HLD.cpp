struct HeavyLightDecomposition {
  struct Chain {
    int depth;
    pair<int, int> parent;         // chain number, index
    vector<pair<int, int> > child; // child chain number, parent index
    vector<int> mapfrom;
    // SegmentTree stree;
    Chain() {;}
    // Chain (int N) : stree(N) {;}
  };
  Graph baseG;
  vector<Chain> chains;
  vector<pair<int,int>> mapto; // raw index -> chain number & index
  vector<vector<int>> mapfrom;  // chain number & index -> raw index

  HeavyLightDecomposition() {;}
  HeavyLightDecomposition(const Graph &g) {
    baseG = g;
    const int n = baseG.size();
    mapto = vector<pair<int,int>>(n, make_pair(-1, -1));
    mapfrom.clear();
    vector<int> size(n, 0);
    int start = -1;
    REP(i,n) if (baseG[i].size() <= 1) { start = i; break; }
    assert(start != -1);
    size_check_bfs(start, size);
    decomposition(start, start, 0, 0, 0, size);
  }

  /*
  int depth(int t) {
    return chains[mapto[t].first].depth;
  }
  */

private:
  int decomposition(int from, int parent, int depth, int pnumber, int pindex, const vector<int> &size) {
    vector<int> seq;
    bfs(from, parent, seq, size);
    const int c = chains.size();
    // chains.push_back(Chain((int)seq.size()));
    chains.push_back(Chain());
    chains[c].depth = depth;
    chains[c].parent = make_pair(pnumber, pindex);
    REP(i,seq.size()) {
      mapto[seq[i]] = make_pair(c, i);
      chains[c].mapfrom.push_back(seq[i]);
    }
    mapfrom.push_back(chains[c].mapfrom);
    REP(i,seq.size()) {
      for (Edge e: baseG[seq[i]]) {
        if (mapto[e.dest].first != -1) continue;
        int nc = decomposition(e.dest, seq[i], depth + 1, c, i, size);
        chains[c].child.push_back(make_pair(nc, i));
      }
    }
    return c;
  }
  void size_check_bfs(int start, vector<int> &size) {
    const int n = baseG.size();
    queue<pair<int,int>> que;
    que.push(make_pair(start, start));
    int cnt = 0;
    vector<int> order(n, -1);
    while (!que.empty()) {
      int from, parent; tie(from, parent) = que.front(); que.pop();
      order[cnt++] = from;
      for (Edge e: baseG[from]) {
        if (e.dest == parent) continue;
        que.push(make_pair(e.dest, from));
      }
    }
    assert(cnt == n);
    reverse(ALL(order));
    REP(i,n) {
      int from = order[i];
      size[from] = 1;
      for (Edge e: baseG[from]) size[from] += size[e.dest];
    }
  }
  void bfs(int from, int parent, vector<int> &seq, const vector<int> &size) {
    for (;;) {
      seq.push_back(from);
      int best = -1, next = -1;
      for (Edge e: baseG[from]) {
        if (e.dest == parent) continue;
        if (best < size[e.dest]) { best = size[e.dest]; next = e.dest; }
      }
      if (next == -1) break;
      parent = from; from = next;
    }
  }
};
