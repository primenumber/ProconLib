// Range Update, Point Get
// verified: AtCoder ABC179 F

struct Data {
  int num;
  Data() : num(0x7FFFFFFF) {;}
  Data(int n) : num(n) {;}
};

inline Data Merge(Data left, Data right) {
  return Data(left.num < right.num ? left.num : right.num);
}

struct SegmentTree {
  int n; vector<Data> data;
  SegmentTree(int N) : n(1 << N), data(n * 2) {}
  Data get(int pos) {
    auto value = data[pos];
    while (pos < 2*n-1) {
      pos = pos / 2 + n;
      value = Merge(value, data[pos]);
    }
    return value;
  }
  void sub(int fr, int to, int node, int la, int ra, Data value) {
    if (ra<=fr || to<=la) return;
    if (fr<=la && ra<=to) {
      data[node] = Merge(data[node], value);
      return;
    }
    sub(fr, to, (node-n)*2+0, la, (la+ra)/2, value);
    sub(fr, to, (node-n)*2+1, (la+ra)/2, ra, value);
  }
  void update(int fr, int to, Data value) { sub(fr, to, 2*n-2, 0, n, value); }
};
