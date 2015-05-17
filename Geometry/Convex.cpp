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
    if (ccw(l.a, l.b, A) * ccw(l.a, l.b, B) < 0)
      Q.push_back(is_ll((L){A, B}, l));
  }
  return Q;
}

// line expression of ax+by+c<0
L make_line(ld a, ld b, ld c) {
  P p1, p2;
  if (abs(a) < eps) {
    if (abs(b) < eps) {
      if (c < 0) return (L){P(1e9, 0), P(1e9, 1e9)};
      return (L){P(1e9, 1e9), P(1e9, 0)};
    }
    p1 = P(0, -c/b); p2 = P(1, -c/b);
  }
  else {
    p1 = P(-c/a, 0); p2 = P((-b-c)/a, 1);
  }
  P p = (p2 - p1) * P(0, 1) + p1;
  ld x = real(p), y = imag(p);
  if (a * x + b * y + c < 0) return (L){p1, p2};
  else return (L){p2, p1};
}
