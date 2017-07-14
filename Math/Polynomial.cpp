using Data = int;

struct Polynomial {
  vector<Data> c;
  Polynomial() : c(1, 1) {;}
  Polynomial(int s, Data i) : c(s, i) {;}
  Polynomial(vector<Data> v) {c = v;}
  int size() const { return c.size(); }
  void normalize() {
    int s = 1;
    for (int i = size() - 1; i >= 0; i--)
      if (c[i] != 0) { s = i + 1; break; }
    c.resize(s);
  }
  Data operator[](int index) const {
    assert(index >= 0 && index < size());
    return c[index];
  }
  Data &operator[](int index) {
    assert(index >= 0 && index < size());
    return c[index];
  }
  Polynomial operator+(const Polynomial &rhs) const {
    Polynomial ret = *this;
    ret.c.resize(max(size(), rhs.size()));
    REP(i,rhs.size()) ret[i] = ret[i] + rhs[i];
    ret.normalize();
    return ret;
  }
  Polynomial operator-() const {
    Polynomial ret = *this;
    REP(i,ret.size()) ret[i] = -ret[i];
    return ret;
  }
  Polynomial operator-(const Polynomial &rhs) const { return *this + (-rhs); }
  Polynomial operator*(const Polynomial &rhs) const {
    Polynomial ret(size() + rhs.size(), 0);
    REP(i,size()) REP(j,rhs.size()) ret[i+j] += c[i] * rhs[j];
    ret.normalize();
    return ret;
  }
  Polynomial operator/(const Polynomial &rhs) const { return divmod(rhs).first; }
  Polynomial operator%(const Polynomial &rhs) const { return divmod(rhs).second; }
  Polynomial operator+=(const Polynomial &rhs) { return *this = *this + rhs; }
  Polynomial operator-=(const Polynomial &rhs) { return *this = *this - rhs; }
  Polynomial operator*=(const Polynomial &rhs) { return *this = *this * rhs; }
  Polynomial operator/=(const Polynomial &rhs) { return *this = *this / rhs; }
  Polynomial operator%=(const Polynomial &rhs) { return *this = *this % rhs; }
  /*
  void reduce() {
    int g = abs(c.back());
    if (g > 0) {
      for (int j: c)
        if (j != 0) g = __gcd(g, abs(j));
      if (c.back() < 0) g = -g;
      for (int &j: c) j /= g;
    }
  }
  */
  pair<Polynomial, Polynomial> divmod(const Polynomial &rhs) const {
    int ls = size(), rs = rhs.size(), s = ls - rs + 1;
    if (s < 0) { return make_pair(Polynomial(1, 0), *this); }
    Polynomial div(s, 0), rest = *this;
    assert(rhs[rs-1] != 0);
    REP(i,s) {
      /*
      if (rest[ls-i-1] % rhs[rs-1] != 0)
        for (auto &j: rest.c) j *= rhs[rs-1];
      */
      Data d = rest[ls-i-1] / rhs[rs-1];
      div[s - i - 1] = d;
      REP(j,rs) rest[ls-i-j-1] -= rhs[rs-j-1] * d;
    }
    div.normalize(); rest.normalize();
    // rest.reduce();
    return make_pair(div, rest);
  }
  Polynomial pow(int power) const {
    Polynomial base = *this;
    Polynomial ret;
    while (power > 0) {
      if (power & 1) ret *= base;
      base *= base; power >>= 1;
    }
    return ret;
  }
  Polynomial differential() const {
    if (c.size() == 1) return Polynomial(1, 0);
    Polynomial ret(c.size() - 1, 0);
    for (int i = 1; i < (int)c.size(); ++i) ret[i-1] = c[i] * i;
    return ret;
  }
  Data calc(Data x) const {
    Data ans = 0;
    for (int i = c.size() - 1; i >= 0; i--) ans *= x, ans += c[i];
    return ans;
  }
};

Polynomial PolynomialGCD(Polynomial a, Polynomial b) {
  if (b.size() == 1 && b[0] == 0) { a.reduce(); return a; }
  return PolynomialGCD(b, a % b);
}
