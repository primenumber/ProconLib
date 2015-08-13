// verified: AOJ DSL_2 A

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
  void update (int pos, Data value) {
    data[pos] = value;
    while (pos < 2*n-1) {
      int l = pos, r = pos^1;
      if (l > r) swap(l, r);
      pos = pos / 2 + n;
      data[pos] = Merge(data[l], data[r]);
    }
  }
  Data sub(int fr, int to, int node, int la, int ra) {
    if (ra<=fr || to<=la) return Data();
    if (fr<=la && ra<=to) return data[node];
    Data vl = sub(fr, to, (node-n)*2+0, la, (la+ra)/2);
    Data vr = sub(fr, to, (node-n)*2+1, (la+ra)/2, ra);
    return Merge(vl, vr);
  }
  Data query(int fr, int to) { return sub(fr, to, 2*n-2, 0, n); }
};
