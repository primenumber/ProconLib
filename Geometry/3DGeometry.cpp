#include <valarray>

typedef long double ld;
typedef valarray<ld> Point;

const ld eps = 1e-8;

Point make_point(ld x, ld y, ld z) {
  Point p(3);
  p[0] = x; p[1] = y; p[2] = z;
  return p;
}

ld dot(const Point &a, const Point &b) {
  return (a * b).sum();
}

Point cross(const Point &a, const Point &b) {
  return a.cshift(+1) * b.cshift(-1) - a.cshift(-1) * b.cshift(+1);
}

ld norm(const Point &a) { return dot(a, a); }
ld dist(const Point &a) { return sqrt(norm(a)); }

struct Line { Point a, b; };
struct Sphere { Point p; ld r; };

Point project_lp(Line l, Point p) {
  Point point = l.a;
  Point vec = l.b - l.a;
  return point + dot(p-point, vec) / norm(vec) * vec;
}

ld distance_lp(Line l, Point p) {
  return dist(p - project_lp(l, p));
}

ld distance_sp(Line l, Point p) {
  Point proj = project_lp(l, p);
  if (dist(l.a - proj) + dist(l.b - proj) < dist(l.b - l.a) + eps)
    return dist(p - proj);
  else
    return min(dist(p - l.a), dist(p - l.b));
}

// Verified : AOJ1331
ld distance_ll (Line l, Line m) {
  Point p1 = l.a, v1 = l.b - l.a,p2 = m.a, v2 = m.b - m.a;
  Point a = p1 - p2 - dot(p1-p2, v2) / norm(v2) * v2;
  Point b = v1 - dot(v1, v2) / norm(v2) * v2;
  if (norm(b) < eps) return dist(a); // parallel
  ld t = dot(-a, b) / norm(b);
  return dist(a + t * b);
}

// Verified : AOJ1289
vector<Point> intersect_lo(Sphere s, Line l) {
  vector<Point> res;
  Point p = project_lp(l, s.p);
  ld d = dist(p - s.p);
  if (d < s.r + eps){
    ld len = (d > s.r) ? 0.0 : sqrt(s.r * s.r - d * d);
    Point nor = (l.a - l.b) / dist(l.a - l.b);
    res.push_back(p + len * nor);
    res.push_back(p - len * nor);
  }
  return res;
}
