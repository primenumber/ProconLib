// Intersect

bool isis_ll(L l, L m) {
  return abs(cross(l.b - l.a, m.b - m.a)) > eps;
}

bool isis_ls(L l, L s) {
  ld a = cross(l.b - l.a, s.a - l.a);
  ld b = cross(l.b - l.a, s.b - l.a);
  return (a * b < eps);
}

bool isis_lp(L l, P p) {
  return abs(cross(l.b - p, l.a - p)) < eps;
}

bool isis_ss(L s, L t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
         ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

bool isis_sp(L s, P p) {
  return abs(s.a - p) + abs(s.b - p) - abs(s.b - s.a) < eps;
}

P proj(L l, P p) {
  ld t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + t * (l.a - l.b);
}

P mirror(L l, P p) {
  return (ld)2 * proj(l, p) - p;
}

P is_ll(L s, L t){
  P sv = s.b - s.a, tv = t.b - t.a;
  return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);
}

ld dist_lp(L l, P p) {
  return abs(p - proj(l, p));
}

ld dist_ll(L l, L m) {
  return isis_ll(l, m) ? 0 : dist_lp(l, m.a);
}

ld dist_ls(L l, L s) {
  if (isis_ls(l, s)) return 0;
  return min(dist_lp(l, s.a), dist_lp(l, s.b));
}

ld dist_sp(L s, P p) {
  P r = proj(s, p);
  if (isis_sp(s, r)) return abs(r - p);
  return min(abs(s.a - p), abs(s.b - p));
}

ld dist_ss(L s, L t) {
  if (isis_ss(s, t)) return 0;
  ld a = min(dist_sp(s, t.a), dist_sp(t, s.a));
  ld b = min(dist_sp(s, t.b), dist_sp(t, s.b));
  return min(a, b);
}

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

bool isis_vc(vector<C> vc) {
  VP crs;
  int n=vc.size();
  REP(i,n)REP(j,i)
    for(P p:is_cc(vc[i],vc[j]))
      crs.push_back(p);
  REP(i,n)
    crs.push_back(vc[i].p);
  for(P p:crs){
    bool valid=true;
    REP(i,n)
      if(abs(p-vc[i].p)>vc[i].r+eps)
        valid=false;
    if(valid) return true;
  }
  return false;
}

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

VP is_sc(C c, L l){
  VP v = is_lc(c, l), res;
  for (int k = 0; k < v.size(); k++)
    if (ccw(l.a, v[k], l.b) == -2) res.push_back(v[k]);
  return res;
}

vector<L> tangent_cp(C c, P p) {
  vector<L> ret;
  P v = c.p - p;
  ld d = abs(v);
  ld l = sqrt(norm(v) - c.r * c.r);
  if (isnan(l)) { return ret; }
  P v1 = v * P(l / d,  c.r / d);
  P v2 = v * P(l / d, -c.r / d);
  ret.push_back(L(p, p + v1));
  if (l < eps) return ret;
  ret.push_back(L(p, p + v2));
  return ret;
}

vector<L> tangent_cc(C c1, C c2) {
  vector<L> ret;
  if (abs(c1.p - c2.p) - (c1.r + c2.r) > -eps) {
    P center = (c1.p * c2.r + c2.p * c1.r) / (c1.r + c2.r);
    ret = tangent_cp(c1, center);
  }
  if (abs(c1.r - c2.r) > eps) {
    P out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);
    vector<L> nret = tangent_cp(c1, out);
    ret.insert(ret.end(), ALL(nret));
  }
  else {
    P v = c2.p - c1.p;
    v /= abs(v);
    P q1 = c1.p + v * P(0,  1) * c1.r;
    P q2 = c1.p + v * P(0, -1) * c1.r;
    ret.push_back(L(q1, q1 + v));
    ret.push_back(L(q2, q2 + v));
  }
  return ret;
}

bool is_polygon(L l, VP &g) {
  int n = g.size();
  for (int i = 0; i < n; i++) {
    P a = g[i];
    P b = g[(i+1)%n];
    if (isis_ss(l, L(a, b))) return true;
  }
  return false;
}

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
