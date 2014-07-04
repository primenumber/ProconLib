
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
  SegTreeLazy(void) : n(STsize / 2) {
    REP(i,STsize){
      data[i]=lazy[i]=0;
    }
  }
  void add(int fr, int to, Data val) { upd_sub(fr, to, 2*n-2, 0, n, val); }
  Data sum(int fr, int to) { sum_sub(fr, to, 2*n-2, 0, n); }
 private:
  void update (int pos, Data value) {
    data[pos] += value;
    while (pos < 2*n-1) {
      pos = pos / 2 + n;
      data[pos] += value;
    }
  }
  void upd_sub(int fr, int to, int node, int la, int ra, Data val) {
    if (ra<=fr || to<=la) return;
    if (fr<=la && ra<=to) {
      update(node, val*(ra-la));
      if(node>=n){
        lazy[(node-n)*2+0] += val;
        lazy[(node-n)*2+1] += val;
      }
      return;
    }
    upd_sub(fr, to, (node-n)*2+0, la, (la+ra)/2, val);
    upd_sub(fr, to, (node-n)*2+1, (la+ra)/2, ra, val);
  }
  Data sum_sub(int fr, int to, int node, int la, int ra) {
    if (ra<=fr || to<=la) return Data();
    if (fr<=la && ra<=to) return data[node] + lazy[node]*(ra-la);
    lazy[(node-n)*2+0] += lazy[node];
    lazy[(node-n)*2+1] += lazy[node];
    data[node] += lazy[node]*(ra-la);
    lazy[node] = 0;
    Data vl = sum_sub(fr, to, (node-n)*2+0, la, (la+ra)/2);
    Data vr = sum_sub(fr, to, (node-n)*2+1, (la+ra)/2, ra);
    return vl+vr;
  }
};

// 2次元SegmentTree
Seg2D{
  static const STsize = 1 << 10;
  int n;
  SegmentTree data[STsize];
  Seg2D() : n(STsize / 2) {}
  void update (int posi, int posj, Data value) {
    data[posi].update(posj.value);
    while (posi < 2*n-1) {
      int l = posi, r = posi^1;
      posi = posi / 2 + n;
      data[posi].update(posj,Merge(data[l], data[r]));
    }
  }
  Data sub(int T, int B, int L, int R, int node, int la, int ra){
    if (ra<=T || B<=la) return Data();
    if (T<=la && ra<=B) return data[node].query(L,R);
    Data vl = sub(T, B, L, R, (node-n)*2+0, la, (la+ra)/2);
    Data vr = sub(T, B, L, R, (node-n)*2+1, (la+ra)/2, ra);
    return Merge(vl, vr);
  }
  Data query(int T, int B, int L, int R) {
    return sub(T,B,L,R,2*n-2,0,n);
  }
};
