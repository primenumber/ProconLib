//SCCのコード

V = 2 * N; //Nは論理変数の数


//(X_0 + ~X_1)(X_1 + X_2)(~X_2 + ~X_0)の場合

//(X_0 + ~X_1) <=> (~X_0 => ~X_1 && X_1 => X_0)
add_edge(N + 0, N + 1);
add_edge(1, 0);

//(X_1 + X_2) <=> (~X_1 => X_2 && ~X_2 => X_1)
add_edge(N + 1, 2);
add_edge(N + 2, 1);

//(~X_2 + ~X_0) <=> (X_2 => ~X_0 && X_0 => ~X_2)
add_edge(2, N + 0);
add_edge(0, N + 2);

//充足判定
REP(i, N) if (cmp[i] == cmp[i + N]) cout << "充足不可能" << endl;

//解の復元
REP(i, N) {
  if (cmp[i] > cmp[i + N]) cout << "X_i : true";
  else cout << "X_i : false";
}