VP ConvexHull(VP ps) {
  int n = ps.size();
  int k = 0;
  sort(ps.begin(), ps.end());
  VP ch(2 * n);
  for (int i = 0; i < n; ch[k++] = ps[i++])
    while (k >= 2 && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
  for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--])
    while (k >= t && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
  ch.resize(k - 1);
  return ch;
}

VP ConvexCut(const VP &ps, L l) {
  VP Q;
  for (int i = 0; i < (int)ps.size(); i++) {
    P A = ps[i], B = ps[(i+1)%ps.size()];
    if (ccw(l.a, l.b, A) != -1) Q.push_back(A);
    if (ccw(l.a, l.b, A) * ccw(l.a, l.b, B) < 0) {
      Q.push_back(is_ll(L(A, B), l)[0]);
    }
  }
  return Q;
}

ld area(const VP &p) {
  ld res = 0;
  int n = p.size();
  REP(j,n) res += cross(p[j], p[(j+1)%n]);
  return res / 2;
}
