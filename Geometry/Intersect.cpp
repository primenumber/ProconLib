/*
  LINE
*/

// 直線lと直線mが交点を持つか
bool isis_ll(L l, L m) {
  return abs(cross(l.b - l.a, m.b - m.a)) > eps ||
    abs(cross(l.b - l.a, m.a - l.a)) < eps;
}

// 直線lと線分mが交点を持つか
bool isis_ls(L l, L s) {
  return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < eps;
}

// 点pが直線l上に存在するか
bool isis_lp(L l, P p) {
  return abs(cross(l.b - p, l.a - p)) < eps;
}

// 直線lと線分mが交点を持つか
bool isis_ss(L s, L t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
    ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

// 点pが線分s上に存在するか
bool isis_sp(L s, P p) {
  return abs(s.a - p) + abs(s.b - p) - abs(s.b - s.a) < eps;
}

// 点pから直線lに下ろした垂線の足
P proj(L l, P p) {
  ld t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + t * (l.a - l.b);
}

// 直線lを軸として点pと対称な点
P mirror(L l, P p) {
  return (ld)2 * proj(l, p) - p;
}

// 直線sと直線lの交点
VP is_ll(L s, L t){
  VP v;
  P sv = s.b - s.a, tv = t.b - t.a;
  if (abs(cross(sv,tv) > 0))
    v.push_back(s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv));
  return v;
}

// 直線lと点pの距離
ld dist_lp(L l, P p) {
  return abs(p - proj(l, p));
}

// 直線lと直線mの距離
ld dist_ll(L l, L m) {
  return isis_ll(l, m) ? 0 : dist_lp(l, m.a);
}

// 直線lと線分sの距離
ld dist_ls(L l, L s) {
  if (isis_ls(l, s)) return 0;
  return min(dist_lp(l, s.a), dist_lp(l, s.b));
}

// 線分sと点pの距離
ld dist_sp(L s, P p) {
  P r = proj(s, p);
  if (isis_sp(s, r)) return abs(r - p);
  return min(abs(s.a - p), abs(s.b - p));
}

// 線分sと線分tの距離
ld dist_ss(L s, L t) {
  if (isis_ss(s, t)) return 0;
  return min(min(dist_sp(s, t.a), dist_sp(s, t.b)), min(dist_sp(t, s.a), dist_sp(t, s.b)));
}

/*
  CIRCLE
*/

// 円c1と円c2の交点
VP is_cc(C c1, C c2){
  VP res;
  ld d = abs(c1.p - c2.p);
  ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
  ld dfr = c1.r * c1.r - rc * rc;
  if (abs(dfr) < eps) dfr = 0.0;
  else if (dfr < 0.0) return res; // no intersection
  ld rs = sqrt(dfr);
  P diff = (c2.p-c1.p)/d;
  res.push_back(c1.p + diff * P(rc, rs));
  if (dfr != 0.0) res.push_back(c1.p + diff * P(rc, -rs));
  return res;
}

// 円cと直線lの交点
VP is_lc(C c, L l){
  VP res;
  ld d = dist_lp(l, c.p);
  if (d < c.r + eps){
    ld len = (d > c.r) ? 0.0 : sqrt(c.r * c.r - d * d); //safety;
    P nor = (l.a - l.b) / abs(l.a - l.b);
    res.push_back(proj(l, c.p) + len * nor);
    res.push_back(proj(l, c.p) - len * nor);
  }
  return res;
}

// 円cと線分lの交点
VP is_sc(C c, L l){
  VP v = is_lc(c, l), res;
  for (int k = 0; k < v.size(); k++)
    if (ccw(l.a, v[k], l.b) == -2) res.push_back(v[k]);
  return res;
}

/*
  Polygon
*/

// 直線lと多角形Pが交差するかどうか
bool is_polygon(L l, VP &g) {
  int n = g.size();
  for (int i = 0; i < n; i++) {
    P a = g[i];
    P b = g[(i+1)%n];
    if (isis_ss(l, L(a, b))) return true;
  }
  return false;
}

// 点pが多角形P内にあるかどうか
int is_in_Polygon(const VP &g, P p) {
  bool in = false;
  int n = g.size();
  for (int i = 0; i < n; i++) {
    P a = g[i] - p, b = g[(i+1)%n] - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (imag(a) <= 0 && 0 < imag(b))
      if (cross(a, b) < 0) in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0) return 0; // on
  }
  if(in) return 1; // in
  return -1; // out
}
