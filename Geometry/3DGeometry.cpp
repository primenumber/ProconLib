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
struct Plane { Point a, b, c; };
struct Sphere { Point p; ld r; };

Point project_lp(Line l, Point p) {
  Point point = l.a, vec = l.b - l.a;
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

// Verified : AOJ2081
ld distance_ll (Line l, Line m) {
  Point v = cross(l.b - l.a, m.b - m.a), p = m.a - l.a;
  if (dist(v) < eps) return distance_lp(l, m.a);
  return abs(dot(v, p)) / dist(v);
}

bool is_in_plane(Plane pl, Point p) {
  pl.a -= p;
  pl.b -= p;
  pl.c -= p;
  return abs(dot(pl.a, cross(pl.b, pl.c))) < eps;
}

bool is_cross_pll(Plane pl, Line l) {
  Point p = (l.a - l.b) + pl.a;
  return !is_in_plane(pl, p) || is_in_plane(pl, l.a);
}

bool is_cross_tl(Plane t, Line l) {
  Point p = (l.a - l.b) + pl.a;
  return !is_in_plane(pl, p) || is_in_plane(pl, l.a);
}

ld distance_pll(Plane pl, Line l) {
  if (is_cross_pll(pl, l)) return 0.0;
  return min(distance_ll({pl.a,pl.b}, l), distance_ll({pl.b, pl.c}, l));
}

ld distance_tl(Plane t, Line l) {
  return 0;
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
