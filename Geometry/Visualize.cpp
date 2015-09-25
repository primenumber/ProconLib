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
