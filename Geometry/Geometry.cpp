#include <complex>

using ld = long double;
using P = complex<ld>;
using VP = vector<P>;
const ld eps = 1e-8, pi = acos(-1.0);

#define EQ(a,b) (abs((a)-(b))<eps)

ld dot (P a, P b) { return real(conj(a) * b); }
ld cross (P a, P b) { return imag(conj(a) * b); }

namespace std {
  bool operator<(const P &lhs, const P &rhs) {
    return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag()
                                    : lhs.real() < rhs.real();
  }
}

struct L{ P a, b; };
struct C { P p; ld r; };

// counter clockwise
int ccw (P a, P b, P c) {
  b -= a; c -= a;
  if (cross(b, c) > eps) return 1;   // counter clockwise
  if (cross(b, c) < -eps) return -1; // clockwise
  if (dot(b, c) < 0) return 2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;  // a--b--c on line
  return 0;                          // a--c--b on line
}
