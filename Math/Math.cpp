using ll=long long;

ll gcd(ll a,ll b){if(a<b)swap(a,b);return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

// ax+by=gcd(a,b)
// |x|+|y| -> min
// x <= y
ll extgcd(ll a, ll b, ll& x, ll& y) {
  ll g = a; x = 1; y = 0;
  if (b) g = extgcd(b, a%b, y, x), y -= (a / b) * x;
  return g;
}

// cond: a>b
// ax+by=c
ll extgcd2(ll a, ll b, ll c, ll& x, ll& y) {
  ll g = a; x = c / a; y = 0;
  if (b) g = extgcd2(b, a%b, c%b, y, x), y += (c / b) - (a / b) * x;
  return g;
}

// a^-1 mod p
ll inv(ll a,ll p){
  return ( a == 1 ? 1 : (1 - p*inv(p%a,a)) / a + p );
}

// A[i] * x = B (mod M[i])
pair<ll,ll> linear_congruence(const vector<ll>& A, const vector<ll>& B, const vector<ll>& M) {
  ll x = 0, m = 1;
  for(ll i = 0; i < (int)M.size(); i++){
    ll a = A[i] * m, b = B[i] - A[i] * x, d = __gcd(M[i], a);
    if (b % d != 0) return make_pair(0, -1);
    ll t = b / d * inv(a / d, M[i] / d) % (M[i] / d);
    x = x + m * t;
    m *= M[i] / d;
  }
  return make_pair(x % m, m);
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
