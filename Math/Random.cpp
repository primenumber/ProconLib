// xoroshiro128plus (http://xoroshiro.di.unimi.it/xoroshiro128plus.c)
// License: CC0 1.0
// See <http://creativecommons.org/publicdomain/zero/1.0/>.

// seed must not be {0, 0}
uint64_t s[2] = { 0xbeac0467eba5facb, 0xd86b048b86aa9922 };

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

uint64_t rnd(void) {
	const uint64_t s0 = s[0];
	uint64_t s1 = s[1];
	const uint64_t result = s0 + s1;

	s1 ^= s0;
	s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
	s[1] = rotl(s1, 36); // c

	return result;
}
