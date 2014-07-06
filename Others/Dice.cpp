
// Dice

class Dice{
public:
  int t, r, f;
  int top() { return t; }
  int bottom() { return 7 - t; }
  int right() { return r; }
  int left() { return 7 - r; }
  int front() { return f; }
  int back() { return 7 - f; }
  void toFront() { swap(f, t); t = 7 - t; }
  void toBack() { toFront(); toFront(); toFront(); }
  void toRight() { swap(f, r); t = 7 - t; }
  void toLeft() { toRight(); toRight(); toRight(); }
};
