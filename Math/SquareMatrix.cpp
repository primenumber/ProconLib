struct SqMat {
  static const int width = 2;
  Data data[width][width];
  SqMat() {
    for(int i=0;i<width;++i)
      for(int j=0;j<width;++j)
        data[i][j] = 0;
  }
  SqMat(Data scalar) {
    for(int i=0;i<width;++i)
      for(int j=0;j<width;++j){
        if(i==j)
          data[i][j] = scalar;
        else
          data[i][j] = 0;
      }
  }
  SqMat(const SqMat&) = default;
  SqMat(SqMat&&) = default;
  SqMat& operator=(const SqMat&) = default;
  SqMat& operator=(SqMat&&) = default;
  SqMat operator-() const {
    SqMat copy;
    for(int i=0;i<width;++i)
      for(int j=0;j<width;++j)
        copy.data[i][j] = -data[i][j];
    return copy;
  }
};

SqMat operator+(const SqMat& lhs, const SqMat& rhs) {
  SqMat copy;
  for(int i=0;i<SqMat::width;++i)
    for(int j=0;j<SqMat::width;++j)
      copy.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
  return copy;
}

// Light version
SqMat operator*(const SqMat& lhs, const SqMat& rhs) {
  SqMat copy;
  for(int i=0;i<SqMat::width;++i)
    for(int j=0;j<SqMat::width;++j)
      for(int k=0;k<SqMat::width;++k)
        copy.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
  return copy;
}

// Faster version
SqMat operator*(const SqMat& lhs, const SqMat& rhs) {
  vector<vector<Data>> rhs_cp(SqMat::width,vector<Data>(SqMat::width));
  for(int i=0;i<SqMat::width;++i)
    for(int j=0;j<SqMat::width;++j)
      rhs_cp[i][j]=rhs.data[j][i];
  SqMat copy;
  for(int i=0;i<SqMat::width;++i)
    for(int j=0;j<SqMat::width;++j)
      for(int k=0;k<SqMat::width;++k)
        copy.data[i][j] += lhs.data[i][k] * rhs_cp[j][k];
  return copy;
}

SqMat operator^(const SqMat& lhs, const ll index) {
  if(index == 0) 
    return SqMat(Data(1));
  else if(index == 1)
    return lhs;
  else {
    SqMat half=lhs^(index/2);
    if((index%2)==0)
      return half*half;
    else
      return half*half*lhs;
  }
}
