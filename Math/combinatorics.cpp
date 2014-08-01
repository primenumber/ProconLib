// zeta
REP(i,n) REP(j,1<<n) if (!(j & (1 << i))) f[j] += f[j | (1 << i)];

// mobius
REP(i,n) REP(j,1<<n) if(j & (1 << i)) f[j] -= f[j ^ (1 << i)];
