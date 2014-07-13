struct UnionFind {
  vector<int> parent;
  UnionFind (int n) { parent.assign(n, -1); }
  int root(int x) { return parent[x] < 0 ? x : parent[x] = root(parent[x]); }
  bool merge(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return false;
    if (parent[y] < parent[x]) swap(x, y);
    if (parent[x] == parent[y]) --parent[x];
    parent[y] = x;
    return true;
  }
};

// Light version

struct UnionFind {
  vector<int> p;
  UnionFind (int n) { p.assign(n, -1); }
  int root(int x) { return p[x] < 0 ? x : p[x] = root(p[x]); }
  void merge(int x, int y) { if (root(x) != root(y)) p[root(y)] = x; }
};
