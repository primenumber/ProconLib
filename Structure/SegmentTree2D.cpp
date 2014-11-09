struct Seg2D{
  static const int STsize = 1 << 10;
  int n;
  SegmentTree data[STsize];
  Seg2D() : n(STsize / 2) {}
  void update (int posi, int posj, Data value) {
    data[posi].update(posj, value);
    while (posi < 2*n-1) {
      int l = posi, r = posi^1;
      posi = posi / 2 + n;
      data[posi].update(posj, Merge(data[posi].data[l], data[posi].data[r]));
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
