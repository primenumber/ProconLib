// Verified: Codeforces Round 673 Div1 D

struct UnionFindPP {
  // current time point
  int now;
  // (updated_time, parent)
  vector<pair<int,int>> parent;
  // (updated_time, size, new_child)
  vector<vector<tuple<int,int,int>>> size_his;
  UnionFindPP (int n) : now(0), parent(n, make_pair(INF, -1)), size_his(n, vector(1, make_tuple(0, 1, -1))) {}
  // root of set at time point t
  // O(log n)
  int root(int x, int t) { return t < parent[x].first ? x : root(parent[x].second, t); }
  // size of set at time point t
  // O(log n)
  int size(int x, int t) {
    x = root(x, t);
    auto itr = prev(upper_bound(begin(size_his[x]), end(size_his[x]), make_tuple(t, INF, INF)));
    return get<1>(*itr);
  }
  // merge two sets
  // O(log n)
  // return value:
  //   first: whether x and y is newly merged or not
  //   second: new time point
  pair<bool, int> merge(int x, int y) {
    ++now;
    x = root(x, now); y = root(y, now);
    if (x == y) return make_pair(false, now);
    int size_x = get<1>(size_his[x].back());
    int size_y = get<1>(size_his[y].back());
    if (size_y > size_x) {
      swap(x, y);
      swap(size_x, size_y);
    }
    size_his[x].emplace_back(now, size_x+size_y, y);
    parent[y] = make_pair(now, x);
    return make_pair(true, now);
  }
  // walk all descendants at time point t
  // O(subset_size)
  template <typename F>
  void walk_all(int x, int t, F func) {
    func(x);
    for (auto&& [ti, _, child] : size_his[x]) {
      if (ti == 0) continue;
      if (ti > t) break;
      walk_all(child, t, func);
    }
  }
};
