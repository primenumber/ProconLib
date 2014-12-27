P centroid(VP tri) {
  return (tri[0] + tri[1] + tri[2]) / (ld)3.0;
}

P incenter(VP tri) {
  ld l[3];
  REP(i,3) l[i] = abs(tri[(i+1)%3] - tri[(i+2)%3]);
  ld p = l[0]+l[1]+l[2];
  P ic;
  REP(i,3) ic += l[i]/p*tri[i];
  return ic;
}

P circumcenter(VP tri) {
  P a=tri[1]-tri[0], b=tri[2]-tri[0];
  ld sncab = cross(a,b)*cross(a,b);
  return ((norm(a)*b-norm(b)*a)*cross(a,b))/(2*sncab) + tri[0];
}


ld area(const VP &p) {
  ld res = 0;
  int n = p.size();
  REP(j,n) res += cross(p[j], p[(j+1)%n]);
  return res / 2;
}

bool is_polygon(L l, VP &g) {
  int n = g.size();
  for (int i = 0; i < n; i++) {
    P a = g[i];
    P b = g[(i+1)%n];
    if (isis_ss(l, (L){a, b})) return true;
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
    if (abs(cross(a, b)) < eps && dot(a, b) < eps) return 0; // on
  }
  if(in) return 1; // in
  return -1; // out
}
