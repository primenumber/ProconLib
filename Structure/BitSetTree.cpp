#include <bits/stdc++.h>

#if __cplusplus == 202002L
#include <bit>
template <typename T>
constexpr int count_tailing_zero_constexpr(T x) noexcept {
  return std::countr_zero(x);
}
#else
constexpr int popcount_constexpr(uint64_t x) noexcept {
  x = (x & 0x5555'5555'5555'5555) + ((x >>  1) & 0x5555'5555'5555'5555);
  x = (x & 0x3333'3333'3333'3333) + ((x >>  2) & 0x3333'3333'3333'3333);
  x = (x & 0x0F0F'0F0F'0F0F'0F0F) + ((x >>  4) & 0x0F0F'0F0F'0F0F'0F0F);
  x = (x & 0x00FF'00FF'00FF'00FF) + ((x >>  8) & 0x00FF'00FF'00FF'00FF);
  x = (x & 0x0000'FFFF'0000'FFFF) + ((x >> 16) & 0x0000'FFFF'0000'FFFF);
  return (x & 0x0000'0000'FFFF'FFFF) + ((x >> 32) & 0x0000'0000'FFFF'FFFF);
}

template <typename T>
constexpr int count_tailing_zero_constexpr(T x) noexcept {
  return popcount_constexpr(~x&(x-1));
}
#endif

using namespace std;

template <size_t key_bits, typename word = uint64_t, typename Enable = void>
class BitSetTree {};

template <size_t key_bits, typename word>
class BitSetTree<key_bits, word, enable_if_t<(key_bits > count_tailing_zero_constexpr(numeric_limits<uint64_t>::digits))>> {
 public:
  static constexpr size_t word_bits = numeric_limits<word>::digits;
  static constexpr size_t key_reduce = count_tailing_zero_constexpr(word_bits);
  BitSetTree() : ary(), parent() {}
  bool insert(const size_t index) {
    const size_t offset = index >> key_reduce;
    const size_t digit = index & (word_bits - 1);
    if (((ary[offset] >> digit) & 1) == 1) {
      return false;
    }
    ary[offset] |= word(1) << digit;
    parent.insert(offset);
    return true;
  }
  bool has_key(const size_t index) const {
    const size_t offset = index >> key_reduce;
    const size_t digit = index & (word_bits - 1);
    return ((ary[offset] >> digit) & 1) == 1;
  }
  bool erase(const size_t index) {
    const size_t offset = index >> key_reduce;
    const size_t digit = index & (word_bits - 1);
    if (((ary[offset] >> digit) & 1) == 0) {
      return false;
    }
    ary[offset] ^= word(1) << digit;
    if (ary[offset] == 0) parent.erase(offset);
    return true;
  }
  size_t lower_bound(const size_t index) const {
    size_t offset = index >> key_reduce;
    if (offset >= size(ary)) return index;
    const size_t digit = index & (word_bits - 1);
    const word mask = ~word(0) << digit;
    word masked_data = ary[offset] & mask;
    if (!masked_data) {
      offset = parent.upper_bound(offset);
      if (offset >= size(ary)) return offset << key_reduce;
      masked_data = ary[offset];
    }
    return (offset << key_reduce) | __builtin_ctzl(masked_data);
  }
  size_t upper_bound(const size_t index) const {
    return lower_bound(index+1);
  }
  size_t max() const {
    const size_t offset = parent.max();
    return (offset << key_reduce) | (word_bits - 1 - __builtin_clzl(ary[offset]));
  }
 private:
  BitSetTree<key_bits - key_reduce> parent;
  array<word, (1 << (key_bits - key_reduce))> ary;
};

template <size_t key_bits, typename word>
class BitSetTree<key_bits, word, enable_if_t<(key_bits <= count_tailing_zero_constexpr(numeric_limits<uint64_t>::digits))>> {
 public:
  static constexpr size_t word_bits = numeric_limits<word>::digits;
  static constexpr size_t key_reduce = key_bits;
  BitSetTree() : data(0) {}
  bool insert(const size_t index) {
    if (((data >> index) & 1) == 1) return false;
    data |= word(1) << index;
    return true;
  }
  bool has_key(const size_t index) const {
    return ((data >> index) & 1) == 1;
  }
  bool erase(const size_t index) {
    if (((data >> index) & 1) == 0) return false;
    data ^= word(1) << index;
    return true;
  }
  size_t lower_bound(const size_t index) const {
    const size_t digit = index & (word_bits - 1);
    const word mask = ~word(0) << digit;
    const word masked_data = data & mask;
    if (masked_data == 0) return size_t(1) << key_bits;
    return __builtin_ctzl(masked_data);
  }
  size_t upper_bound(const size_t index) const {
    return lower_bound(index+1);
  }
  size_t max() const {
    if (data == 0) throw runtime_error("emtpy");
    return word_bits - 1 - __builtin_clzl(data);
  }
 private:
  word data;
};

// Verified: AOJ ALDS1_9_C
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  using i32 = int32_t;
  using u32 = uint32_t;
  vector<tuple<i32,i32>> vq;
  vector<u32> vidx;
  vq.reserve(2000000);
  vidx.reserve(2000000);
  string type;
  while (true) {
    cin>>type;
    if (type[2] == 's') {
      u32 k;
      cin>>k;
      vq.emplace_back(0, k);
      vidx.push_back(k);
    } else if (type[2] == 't') {
      vq.emplace_back(1, 0);
    } else {
      break;
    }
  }
  sort(begin(vidx),end(vidx));
  vidx.erase(unique(begin(vidx),end(vidx)), end(vidx));
  vector<i32> cnt(size(vidx));
  BitSetTree<21> bst;
  for (auto&& [x, y] : vq) {
    if (x == 0) {
      u32 j = lower_bound(begin(vidx),end(vidx),y) - begin(vidx);
      if (cnt[j] == 0) {
        bst.insert(j);
      }
      ++cnt[j];
    } else {
      u32 j = bst.max();
      cout<<vidx[j]<<'\n';
      --cnt[j];
      if (cnt[j] == 0) {
        bst.erase(j);
      }
    }
  }
  return 0;
}
