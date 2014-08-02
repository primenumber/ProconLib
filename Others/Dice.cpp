struct Dice{
  int t, r, f;
  int top() { return t; }
  int bottom() { return 7 - t; }
  int right() { return r; }
  int left() { return 7 - r; }
  int front() { return f; }
  int back() { return 7 - f; }
  void toFront() { swap(f, t); t = 7 - t; }
  void toBack() { toFront(); toFront(); toFront(); }
  void toRight() { swap(t, r); t = 7 - t; }
  void toLeft() { toRight(); toRight(); toRight(); }
  void toClock() { swap(f, r); r = 7 - r; }
  void toConter() { toClock(); toClock(); toClock(); }
  int roll(int tt, int ff) {
    REP(i,30) {
      if (i % 10 == 0) toRight();
      else if (i % 10 == 5) toFront();
      else toClock();
      if (tt == t && ff == f) return r;
    }
    return 0;
  }
};

struct Dice{
  int t, f, r, face[6];
  Dice(void) { t = 0; f = 1; r = 2; }
  int top() { return face[t]; }
  int bottom() { return face[5 - t]; }
  int right() { return face[r]; }
  int left() { return face[5 - r]; }
  int front() { return face[f]; }
  int back() { return face[5 - f]; }
  void toFront() { swap(f, t); t = 5 - t; }
  void toBack()  { swap(f, t); f = 5 - f; }
  void toRight() { swap(t, r); t = 5 - t; }
  void toLeft()  { swap(t, r); r = 5 - r; }
  void toClock() { swap(f, r); r = 5 - r; }
  void toConter(){ swap(f, r); f = 5 - f; }
  vector<int> toVector() {
    return {face[t], face[f], face[r], face[5-r], face[5-f], face[5-t]};
  }
  vector<int> toVector2() {
    vector<int> res = {999};
    REP(i,30) {
      if (i % 10 == 0) toRight();
      else if (i % 10 == 5) toFront();
      else toClock();
      res = min(res, toVector());
    }
    return res;
  }
};
