
struct Matrix{
  static const int width = 2;
  static const int height = 2;
  Data data[width][height];
  Matrix() {
    for(int i=0;i<width;++i)
      for(int j=0;j<height;++j)
        data[i][j] = 0;
  }
  Matrix(Data scalar) {
    for(int i=0;i<width;++i)
      for(int j=0;j<height;++j){
        if(i==j)
          data[i][j] = scalar;
        else
          data[i][j] = 0;
      }
  }
  Matrix(const Matrix&) = default;
  Matrix(Matrix&&) = default;
  Matrix& operator=(const Matrix&) = default;
  Matrix& operator=(Matrix&&) = default;
  Matrix operator-() const {
    Matrix copy;
    for(int i=0;i<width;++i)
      for(int j=0;j<height;++j)
        copy.data[i][j] = -data[i][j];
    return copy;
  }
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  Matrix copy;
  for(int i=0;i<Matrix::width;++i)
    for(int j=0;j<Matrix::height;++j)
      copy.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
  return copy;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  Matrix copy;
  for(int i=0;i<Matrix::width;++i)
    for(int j=0;j<Matrix::height;++j)
      for(int k=0;k<Matrix::height;++k)
        copy.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
  return copy;
}
