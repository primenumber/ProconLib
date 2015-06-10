// verified: ATC001 C

typedef long long ll;
typedef long double ld;
typedef complex<ld> P;

const ld pi = acos(-1.0);

vector<P> FFT(ld theta, const vector<P> &a) {
  const int n = a.size();
  vector<P> ret = a;
  for (int m = n; m >= 2; m >>= 1, theta *= 2) {
    REP(i,m/2) {
      for (int j = i; j < n; j += m) {
        int k = j + m / 2;
        P x = ret[j] - ret[k];
        ret[j] += ret[k];
        ret[k] = exp(i * theta * P(0, 1)) * x;
      }
    }
  }
  for (int i = 0, j = 1; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1) {;}
    if (j < i) swap(ret[i], ret[j]);
  }
  return ret;
}

vector<ll> convolution(const vector<ll> &lhs, const vector<ll> &rhs) {
  int n = 1, a = lhs.size(), b = rhs.size();
  while (n < max(a, b) * 2) n <<= 1;
  vector<P> temp1(n), temp2(n);
  REP(i,n/2) {
    if (i < a) temp1[i] = P(lhs[i], 0);
    if (i < b) temp2[i] = P(rhs[i], 0);
  }
  temp1 = FFT(2.0 * pi / n, temp1);
  temp2 = FFT(2.0 * pi / n, temp2);
  REP(i,n) temp1[i] *= temp2[i];
  temp1 = FFT(-2.0 * pi / n, temp1);
  vector<ll> ret(n);
  REP(i,n) ret[i] = temp1[i].real() / n + 0.5;
  return ret;
}
