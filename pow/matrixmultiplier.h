#include "matrix/matrix.h"

template <class T>
class MatrixMultiplier {
public:
	MatrixMultiplier(const CMatrix<T>& matrix) {
		dimension = matrix.width(); //add check if matrix is not square?
	}
	CMatrix<T> operator()(const CMatrix<T>& a, const CMatrix<T>& b) const {
		return a * b;
	}
	CMatrix<T> unity() const {
		return CMatrix<T>(dimension);
	}
private:
	int dimension;
};


