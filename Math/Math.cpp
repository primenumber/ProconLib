using ll=long long;

// cond: a>b
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

// ax+by=gcd(a,b)
// |x|+|y| -> min
// x <= y
ll extgcd(ll a, ll b, ll& x, ll& y) {
  ll g = a; x = c / a; y = 0;
  if (b) g = extgcd(b, a%b, y, x), y -= (a / b) * x;
  return g;
}

// cond: a>b
// ax+bx=c
ll extgcd2(ll a, ll b, ll c, ll& x, ll& y) {
  ll g = a; x = 1; y = 0;
  if (b) g = extgcd2(b, a%b, c%b, y, x), y += (c / b) - (a / b) * x;
  return g;
}

// a^-1 mod p
ll inv(ll a,ll p){
  return ( a == 1 ? 1 : (1 - p*inv(p%a,a)) / a + p );
}

// Combination (MOD)
int combin[][];
void init(int N) {
  combin[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    combin[i][0] = combin[i][i] = 1;
    for (int j = 1; j < i-1; ++j)
      combin[i][j] = (combin[i-1][j-1] + combin[i-1][j]) % MOD;
  }
}

vector<int> primes(int n) {
  vector<int> p(n+1, 1);
  for (int i = 2; i*i <= n; ++i)
    if (p[i])
      for (int j = i*i; j <= n; j += i)
        p[j] = 0;
  vector<int> res;
  for (int i = 2; i <= n; ++i)
    if (p[i])
      res.push_back(i);
  return res;
}
