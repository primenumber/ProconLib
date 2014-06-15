
struct Data {
  int num;
  Data() : num(0x7FFFFFFF) {;}
  Data(int n) : num(n) {;}
};

inline Data Merge(Data left, Data right) {
  return Data(left.num < right.num ? left.num : right.num);
}

struct SegmentTree {
  static const int STsize = 1 << 18;
  Data data[STsize]; int n;
  SegmentTree(void) : n(STsize / 2) {}
  void update (int pos, Data value) {
    data[pos] = value;
    while (pos < 2*n-1) {
      int l = pos, r = pos^1;
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

// 遅延評価付き
// 区間への加算と区間の和
struct SegTreeLazy {
  static const int MAX_DEPTH = 18;
  static const int STsize = 1 << MAX_DEPTH;
  Data data[STsize];
  Data lazy[STsize]; int n;
  void add (int left, int right, Data value);
  Data sum (int left, int right);
 private:
  Data update_node (int depth, int index) {
    data[index] += lazy[index] << depth;
    lazy[index * 2] += value;
    lazy[index * 2 + 1] += value;
  }
  Data add_impl(int depth, int node, int left, int right, Data value) {
    int width = 1 << (MAX_DEPTH - depth);
    int index = node - (1 << depth);
    int node_left = index * width;
    int node_mid = node_left + (width >> 1);
    Data added;
    if (right - left + 1 == width && left == node_left) {
      lazy[node] += value;
      return value * width;
    } else if (right < node_mid) {
      added = add_impl(depth + 1, node * 2, left, right, value);
    } else if (left >= node_mid) {
      added = add_impl(depth + 1, node * 2 + 1, left, right, value);
    } else {
      added = add_impl(depth + 1, node * 2, left, right, value) +
              add_impl(depth + 2, node * 2 + 1, left, right, value);
    }
    data[node] += added;
    return added;
  }
};

// 2次元SegmentTree
Seg2D{
  static const STsize = 1 << 10;
  int n;
  SegmentTree data[STsize];
  Seg2D() : n(STsize / 2) {}
  Data sub(
  Data query(int T, int B, int L, int R) {
  }
};

/*
int main() {
  int n, q, a, b;
  cin >> n >> q;
  SegmentTree rmq;
  for (int i = 0; i < n; i++) {
    cin >> a;
    rmq.update(i, Data(a));
  }
  for (int i = 0; i < q; i++){
    cin >> a >> b;
    cout << rmq.query(a, b).num << endl;
  }
  return 0;
}
*/
