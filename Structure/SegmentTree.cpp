// verified: AOJ DSL_2 A

struct Monoid {
  int num;
  Monoid() : num(0x7FFFFFFF) {;}
  Monoid(int n) : num(n) {;}
};

const auto Merge = [](Monoid left, Monoid right) {
  return Monoid(left.num < right.num ? left.num : right.num);
};

template <typename Data, typename F>
struct SegmentTree {
  int n; vector<Data> data;
  F merge;
  SegmentTree(int N, F f) : n(1 << N), data(n * 2), merge(f) {}
  void update (int pos, Data value) {
    data[pos] = value;
    while (pos < 2*n-1) {
      int l = pos, r = pos^1;
      if (l > r) swap(l, r);
      pos = pos / 2 + n;
      data[pos] = merge(data[l], data[r]);
    }
  }
  Data sub(int fr, int to, int node, int la, int ra) {
    if (ra<=fr || to<=la) return Data();
    if (fr<=la && ra<=to) return data[node];
    Data vl = sub(fr, to, (node-n)*2+0, la, (la+ra)/2);
    Data vr = sub(fr, to, (node-n)*2+1, (la+ra)/2, ra);
    return merge(vl, vr);
  }
  Data query(int fr, int to) { return sub(fr, to, 2*n-2, 0, n); }
};
