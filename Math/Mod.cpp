const int mod = 1000000007;

struct Mod {
  int num;
  Mod () : num(0) {;}
  Mod (int n) : num(n) {;}
  operator int() { return num; }
};

Mod operator+(Mod a, Mod b) { return Mod((a.num + b.num) % mod); }
Mod operator-(Mod a, Mod b) { return Mod((mod + a.num - b.num) % mod); }
Mod operator*(Mod a, Mod b) { return Mod(((long long)a.num * b.num) % mod); }
Mod operator+=(Mod &a, Mod b) { return a = a + b; }
Mod operator-=(Mod &a, Mod b) { return a = a - b; }
Mod operator^(Mod a, int n) {
  if (n == 0) return Mod(1);
  Mod res = (a * a) ^ (n / 2);
  if (n % 2) res = res * a;
  return res;
}
Mod inv(Mod a) { return a ^ (mod - 2); }
Mod operator/(Mod a, Mod b) { return a * inv(b); }
