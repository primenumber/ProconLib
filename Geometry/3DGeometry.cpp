#include <valarray>

using ld = long double;
using Point = valarray<ld>;

const ld eps = 1e-8, inf = 1e12;

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

// Line

struct Line { Point a, b; };

bool is_in_segment(Line l, Point p) {
  return abs(dist(l.a - p) + dist(l.b - p) - dist(l.a - l.b)) < eps;
}

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

// Plane

struct Plane { Point a, b, c; };

bool is_in_plane(Plane pl, Point p) {
  pl.a -= p; pl.b -= p; pl.c -= p;
  return abs(dot(pl.a, cross(pl.b, pl.c))) < eps;
}

bool parallel_pll(Plane pl, Line l) {
  Point p = (l.a - l.b) + pl.a;
  return is_in_plane(pl, p);
}

bool is_in_triangle(Plane t, Point p) {
  t.a -= p; t.b -= p; t.c -= p;
  ld a = dist(cross(t.a, t.b));
  ld b = dist(cross(t.b, t.c));
  ld c = dist(cross(t.c, t.a));
  return abs(a + b + c - dist(cross(t.c - t.a, t.b - t.a))) < eps;
}

bool is_cross_pll(Plane pl, Line l) {
  return !parallel_pll(pl, l) || is_in_plane(pl, l.a);
}

Point intersect_pll(Plane pl, Line l) {
  assert(!parallel_pll(pl, l));
  Point vec = cross(pl.b - pl.a, pl.c - pl.a);
  ld s = dot(vec, l.a - pl.a), t = dot(vec, l.b - pl.a);
  return (l.b * s - l.a * t) / (s - t);
}

// Verified : AOJ0115
bool is_cross_tl(Plane t, Line l) {
  assert(!parallel_pll(t, l)); // use distance_ll
  Point q = intersect_pll(t, l);
  return is_in_triangle(t, q);
}

ld distance_pll(Plane pl, Line l) {
  if (is_cross_pll(pl, l)) return 0.0;
  return min(distance_ll({pl.a, pl.b}, l), distance_ll({pl.b, pl.c}, l));
}

ld distance_tl(Plane t, Line l) {
  if (is_cross_tl(t, l)) return 0;
  ld res = distance_ll((Line){t.a, t.b}, l);
  res = min(res, distance_ll((Line){t.b, t.c}, l));
  res = min(res, distance_ll((Line){t.c, t.a}, l));
  return res;
}

// new Plane

struct Plane { Point p, v; };

// Verified : AOJ2562

const Point rnd = make_point(43.123984, 50.230909, 33.929898);

Line intersect_plpl (Plane a, Plane b) {
  Point p = cross(rnd, b.v), q = cross(rnd, a.v);
  ld r1 = dot(a.p, a.v) / dot(p, a.v);
  p = p * make_point(r1, r1, r1);
  ld r2 = dot(b.p, b.v) / dot(q, b.v);
  q = q * make_point(r2, r2, r2);
  Point po = p + q;
  return (Line){po, po + cross(a.v, b.v)};
}

// Sphere

// Verified : AOJ1289

struct Sphere { Point p; ld r; };

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
