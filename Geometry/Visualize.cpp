// {filename}.out 2> data.js

ld zoom = 1;

const int OFFSET = 400;

void ChangeColor(int r, int g, int b) {
  fprintf(stderr, "c.strokeStyle = 'rgb(%d, %d, %d)';\n", r, g, b);
}
void DrawPoint(const P &p) {
  fprintf(stderr, "circle(%d, %d, %d)\n",
          (int)(OFFSET+zoom*p.real()), 800-OFFSET-(int)(zoom*p.imag()), 2);
}
void DrawLine(const L &l) {
  fprintf(stderr, "line(%d, %d, %d, %d)\n",
          (int)(OFFSET+zoom*l.a.real()), 800-OFFSET-(int)(zoom*l.a.imag()),
          (int)(OFFSET+zoom*l.b.real()), 800-OFFSET-(int)(zoom*l.b.imag()));
}
void DrawPolygon(const vector<P> &p) {
  const int n = p.size();
  REP(i,n) DrawLine((L){p[i], p[(i + 1) % n]});
}
void DrawCircle(const C &c) {
  fprintf(stderr, "circle(%d, %d, %d)\n",
          (int)(OFFSET + zoom * c.p.real()),
          800 - OFFSET - (int)(zoom * c.p.imag()), (int)(zoom * c.r));
}

// new version

const int COL = 8;

class Visualizer {
  // 0: Gray, 1: Yellow, 2: Cyan, 3: Green, 4: Magenta, 5: Blue, 6: Black, 7:Red
  const int r[COL] = {160, 255, 160, 160, 255,   0, 0, 255};
  const int g[COL] = {160, 255, 255, 255, 160,   0, 0,   0};
  const int b[COL] = {160,   0, 255, 160, 255, 255, 0,   0};
  vector<P> points[COL];
  vector<L> lines[COL];
  vector<C> circles[COL];
  vector<VP> polygons[COL];
  P center;
  int ax, ay, bx, by, offset;
  ld left, right, bottom, top, zoom;
  P f(P p) { return conj(p-center) * zoom + P((ax+bx)/2, (ay+by)/2); };
  void drawCircle (P p, int r) {
    fprintf(stderr, "circle(%d, %d, %d)\n", (int)f(p).real(), (int)f(p).imag(), r);
  }
  void drawLine (L l) {
    fprintf(stderr, "line(%d, %d, %d, %d)\n",
            (int)f(l.a).real(), (int)f(l.a).imag(),
            (int)f(l.b).real(), (int)f(l.b).imag());
  }
  void update (P p, ld r) {
    left   = min(left,   p.real() - r);
    right  = max(right,  p.real() + r);
    bottom = min(bottom, p.imag() - r);
    top    = max(top,    p.imag() + r);
  }

public:
  P draw(P p, int i) {
    if (i >= 0) points[i].push_back(p);
    update(p, 0); return p;
  }
  L draw(L l, int i) {
    if (i >= 0) lines[i].push_back(l);
    update(l.a, 0); update(l.b, 0); return l;
  }
  C draw(C c, int i) {
    if (i >= 0) circles[i].push_back(c);
    update(c.p, c.r); return c;
  }
  VP draw(VP p, int i) {
    int n = p.size();
    REP(j,n) draw((L){p[j], p[(j+1)%n]}, i);
    return p;
  }

  Visualizer (int ax = 0, int ay = 0, int bx = 800, int by = 800, int offset = 50) :
    ax(ax), ay(ay), bx(bx), by(by), offset(offset),
    left(1e9), right(-1e9), bottom(1e9), top(-1e9) {}
  ~Visualizer () {
    center = P((left + right) / 2, (bottom + top) / 2);
    zoom = min((bx - ax - offset * 2) / (right - left),
               (by - ay - offset * 2) / (top - bottom));
    for (int i = 0; i < COL; ++i) {
      fprintf(stderr, "c.strokeStyle = 'rgb(%d, %d, %d)';\n", r[i], g[i], b[i]);
      for (P p: points[i]) drawCircle(p, 2);
      for (L l: lines[i]) drawLine(l);
      for (C c: circles[i]) drawCircle(c.p, (int)(c.r * zoom));
      for (VP p: polygons[i]) {
        int n = p.size();
        REP(i,n) drawLine((L){p[i], p[(i+1)%n]});
      }
    }
  }
};
