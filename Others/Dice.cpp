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
