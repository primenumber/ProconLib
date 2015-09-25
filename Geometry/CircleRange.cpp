typedef vector<pair<ld,ld>> Range;

Range make_range(ld from, ld to) {
  Range v;
  if (to < from) swap(from , to);
  if (to - from > pi) {
    v.emplace_back(0, from);
    v.emplace_back(to, 2*pi);
  }
  else {
    v.emplace_back(from, to);
  }
  return v;
}

void print_range(const Range &r) {
  for (auto p: r)
    cout << "(" << p.first << ", " << p.second << ")";
  cout << endl;
}

Range operator*(const Range &lhs, const Range &rhs) {
  Range res;
  for (auto x: lhs) {
    for (auto y: rhs) {
      ld l = max(x.first, y.first);
      ld r = min(x.second, y.second);
      if (l < r - eps) res.emplace_back(l, r);
    }
  }
  sort(ALL(res));
  return res;
}

Range operator+(const Range &lhs, const Range &rhs) {
  Range v = lhs;
  v.insert(begin(v), ALL(rhs));
  if (v.empty()) return v;
  Range res;
  sort(ALL(v));
  auto x = v.front();
  for (int i = 1; i < (int)v.size(); ++i) {
    if (x.second < v[i].first - eps) {
      res.push_back(x);
      x = v[i];
    }
    else {
      x.second = max(x.second, v[i].second);
    }
  }
  res.push_back(x);
  return res;
}

Range operator-(const Range &r) {
  Range res;
  ld x = 0;
  for (auto p: r) {
    if (p.first > eps) res.emplace_back(x, p.first);
    x = p.second;
  }
  if (x < 2 * pi - eps) res.emplace_back(x, 2 * pi);
  return res;
}

Range operator-(const Range &lhs, const Range &rhs) { return lhs * (-rhs); }
