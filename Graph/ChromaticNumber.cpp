using Weight = int;
Weight INF = 1000000000;

using Array = vector<Weight>;
using Matrix = vector<Array>;

int chromaticNumber(const Matrix &g) {
  int N = g.size();
  Array dp(1<<N, INF);
  vector<bool> ok(1<<N, true);
  dp[0] = 0;
  REP(i,1<<N) REP(k,N) if(i & 1<<k)
    REP(j,k) if((i & 1<<j) && g[j][k]) ok[i] = false;
  REP(i,1<<N) for(int j = i; j; j = (j - 1) & i)
    if(ok[j]) dp[i] = min(dp[i], dp[i^j] + 1);
  return dp[(1<<N)-1];
}
