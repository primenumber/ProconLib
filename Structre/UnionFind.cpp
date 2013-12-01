/*
  UnionFind u(100);  // 100要素作る
  parent(x)          // xの親のid (xが根である場合は-1)
  root(x)            // xの根のid
*/

struct UnionFind {
  vector<int> parent;
  UnionFind (int n) { parent.assign(n, -1); }
  int root(int x) { return parent[x] < 0 ? x : parent[x] = root(parent[x]); }
  bool union(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) { return false; }
    if (parent[y] < parent[x]) { swap(x, y); }
    parent[x] += parent[y];
    parent[y] = x;
    return true;
  }
};
