template <typename Data, typename BinaryOperation>
vector<Data> sum_over_supersets(const vector<Data>& v, const size_t N, BinaryOperation op) {
  auto ans = v;
  for (size_t i = 0; i < N; ++i) {
		for (size_t T = 0; T < (size_t(1) << N); ++T) {
			if (((T >> i) & 1) == 0) {
				ans[T] = op(ans[T], ans[T | (1 << i)]);
			}
		}
	}
  return ans;
}

template <typename Data, typename BinaryOperation>
vector<Data> sum_over_subsets(const vector<Data>& v, const size_t N, BinaryOperation op) {
  auto ans = v;
  for (size_t i = 0; i < N; ++i) {
		for (size_t T = 0; T < (size_t(1) << N); ++T) {
			if (((T >> i) & 1) == 1) {
				ans[T] = op(ans[T], ans[T ^ (1 << i)]);
			}
		}
	}
  return ans;
}

template <typename Data, typename BinaryOperation>
vector<Data> inverse_sum_over_supersets(const vector<Data>& v, const size_t N, BinaryOperation op) {
	return sum_over_supersets(v, N, [&] (const auto& lhs, const auto &rhs) {
		return op(lhs, -rhs);
	});
}

template <typename Data, typename BinaryOperation>
vector<Data> inverse_sum_over_subsets(const vector<Data>& v, const size_t N, BinaryOperation op) {
	return sum_over_subsets(v, N, [&] (const auto& lhs, const auto &rhs) {
		return op(lhs, -rhs);
	});
}

size_t pop_count(size_t x) {
  // GCC builtins: 
  // return __builtin_popcount(x);

  // Intel intrinsics (need to include x86intrin.h)
  // return _mm_popcnt_u64(x);

  // C++20 standard
  // retrun std::popcount(x);

  // Generic implementation for 64bit integer
  x = ((x >> 1) & 0x5555'5555'5555'5555) + (x & 0x5555'5555'5555'5555);
  x = ((x >> 2) & 0x3333'3333'3333'3333) + (x & 0x3333'3333'3333'3333);
  x = ((x >> 4) & 0x0f0f'0f0f'0f0f'0f0f) + (x & 0x0f0f'0f0f'0f0f'0f0f);
  x = ((x >> 8) & 0x00ff'00ff'00ff'00ff) + (x & 0x00ff'00ff'00ff'00ff);
  x = ((x >> 16) & 0x0000'ffff'0000'ffff) + (x & 0x0000'ffff'0000'ffff);
  x = ((x >> 32) & 0x0000'0000'ffff'ffff) + (x & 0x0000'0000'ffff'ffff);
  return x;
}

template <typename Data, typename BinaryOperation>
vector<vector<Data>> ranked_sum_over_subsets(const vector<Data>& v, const size_t N, BinaryOperation op) {
  vector ans(N+1, vector<Data>(1<<N));
  for (size_t i = 0; i < (size_t(1) << N); ++i) {
    ans[pop_count(i)][i] = v[i];
  }
  for (size_t k = 0; k <= N; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t T = 0; T < (size_t(1) << N); ++T) {
        if (((T >> i) & 1) == 1) {
          ans[k][T] = op(ans[k][T], ans[k][T ^ (1 << i)]);
        }
      }
    }
  }
  return ans;
}

template <typename Data, typename BinaryOperation>
vector<Data> inverse_ranked_sum_over_subsets(const vector<vector<Data>>& v, const size_t N, BinaryOperation op) {
  auto tmp = v;
  for (size_t k = 0; k <= N; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t T = 0; T < (size_t(1) << N); ++T) {
        if (((T >> i) & 1) == 1) {
          tmp[k][T] = op(tmp[k][T], -tmp[k][T ^ (1 << i)]);
        }
      }
    }
  }
  vector<Data> ans(1 << N);
  for (size_t i = 0; i < (size_t(1) << N); ++i) {
    ans[i] = tmp[pop_count(i)][i];
  }
  return ans;
}

template <typename Data, typename RingAdd, typename RingMul>
vector<Data> subset_conv(const vector<Data>& f, const vector<Data>& g, const size_t N, RingAdd op_add, RingMul op_mul) {
  auto f_hat = ranked_sum_over_subsets(f, N, op_add);
  auto g_hat = ranked_sum_over_subsets(g, N, op_add);
  vector tmp(N+1, vector<Data>(1 << N));
  for (size_t k = 0; k <= N; ++k) {
    for (size_t i = 0; i < (size_t(1) << N); ++i) {
      for (size_t j = 0; j <= k; ++j) {
        tmp[k][i] = op_add(tmp[k][i], op_mul(f_hat[j][i], g_hat[k-j][i]));
      }
    }
  }
  return inverse_ranked_sum_over_subsets(tmp, N, op_add);
}

// test code
//
//#include <vector>
//#include <iostream>
//#include <random>
//
//using namespace std;
//
//int main() {
//	size_t N = 18;
//  size_t len = 1 << N;
//  random_device rd;
//  mt19937 mt(rd());
//  uniform_int_distribution<> dis(-1024, 1023);
//  vector<int64_t> u(len);
//  vector<int64_t> v(len);
//  for(size_t i = 0; i < len; ++i) {
//    u[i] = dis(mt);
//    v[i] = dis(mt);
//  }
//  auto sosup = sum_over_supersets(v, N, std::plus<>());
//  auto sosub = sum_over_subsets(v, N, std::plus<>());
//  auto inv_sup = inverse_sum_over_supersets(sosup, N, std::plus<>());
//  cout << (inv_sup == v) << endl;
//  auto inv_sub = inverse_sum_over_subsets(sosub, N, std::plus<>());
//  cout << (inv_sub == v) << endl;
//  auto conv_uv = subset_conv(u, v, N, std::plus<>(), std::multiplies<>());
//  bool ok = true;
//  //for (size_t i = 0; i < len; ++i) {
//  //  int64_t sum = 0;
//  //  for (int U = (1 << N) - 1; U >= 0; --U) {
//  //    U &= i;
//  //    sum += u[U] * v[i^U];
//  //  }
//  //  if (sum != conv_uv[i]) ok = false;
//  //}
//  cout << ok << endl;
//  return 0;
//}
