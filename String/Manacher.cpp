// 奇数長の回文のみ検出(偶数長もほしい場合, ダミー文字を挟むこと)
vector<int> manacher(const string &s) {
  int n = s.size();
  vector<int> rad(n);
  int i = 0, j = 0;
  while (i < n) {
    while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) ++j;
    rad[i] = j;
    int k = 1;
    while (i - k >= 0 && i + k < n && k + rad[i - k] < j) rad[i + k] = rad[i - k], ++k;
    i += k;
    j -= k;
  }
  return rad;
}
