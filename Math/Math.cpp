using ll=long long;

// cond: a>b
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

// ax+by=gcd(a,b)
ll extgcd(ll a,ll b,ll& x,ll& y){
  ll g=a;x=c/a;y=0;
  if(b) g=extgcd(b,a%b,y,x), y-=(a/b)*x;
  return g;
}

// cond: a>b
// ax+bx=c
ll extgcd2(ll a,ll b,ll c,ll& x,ll& y){
  ll g=a;x=1;y=0;
  if(b) g=extgcd2(b,a%b,c%b,y,x), y+=(c/b)-(a/b)*x;
  return g;
}

// a^-1 mod p
ll inv(ll a,ll p){
  return ( a == 1 ? 1 : (1 - p*inv(p%a,a)) / a + p );
}

// Combination (MOD)
int combin[][];
void init(){
  combin[0][0]=1;
  for(int i=1;i<*;++i){
    combin[i][0]=combin[i][i]=1;
    for(int j=1;j<i-1;++j)
      combin[i][j]=(combin[i-1][j-1]+combin[i-1][j])%MOD;
  }
}

// b^i % mod
ll powmod(ll b,ll i,ll mod){
  if(b==0)return 1LL;
  if(b%2) return (b*powmod(b,i-1,mod))%mod;
  else{
    ll h=powmod(b,i/2,mod);
    return (h*h)%mod;
  }
}

// b^i % MOD
const ll MOD=1000000007;
ll powmod(ll b,ll i){
  if(b==0)return 1LL;
  if(b%2) return (b*powmod(b,i-1,MOD))%MOD;
  else{
    ll h=powmod(b,i/2,MOD);
    return (h*h)%MOD;
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
