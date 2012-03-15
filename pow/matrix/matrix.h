#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "exceptions.h"
using namespace std;

template<typename Type>
class CMatrix {
public:
    CMatrix(const unsigned int n);
    CMatrix(const unsigned int x, const unsigned int y);
    CMatrix(const vector< vector<Type> >& _data);
    CMatrix(const CMatrix& another);
    ~CMatrix();
    Type trace() const;
    Type det() const;
    unsigned int width() const;
    unsigned int height() const;
    CMatrix& operator = (const CMatrix& another);
    CMatrix operator + (const CMatrix& another) const;
    CMatrix& operator += (const CMatrix& another);
    CMatrix operator - (const CMatrix& another) const;
    CMatrix& operator -= (const CMatrix& another);
    CMatrix operator * (const CMatrix& another) const;
    CMatrix& operator *= (const CMatrix& another);
    CMatrix operator * (const int another) const;
    CMatrix& operator *= (const int another);
    CMatrix operator / (const int another) const;
    CMatrix& operator /= (const int another);
    const vector<Type>& operator[] (const unsigned int x) const;
    vector<Type>& operator[] (const unsigned int x);
    bool operator == (const CMatrix& another) const;
    bool operator != (const CMatrix& another) const;

    CMatrix transposed() const;
    void transpose();
    CMatrix invert() const;

    void randomize();
private:
    Type det(const bool* rows, const bool* cols);
    CMatrix(const CMatrix& another, const unsigned int x, const unsigned int y); //Матрица another без столбца x и строки y
    bool isEmpty() const;
    bool isSquare() const;
    vector< vector<Type> > data;
};

template<typename Type>
ostream& operator<< (ostream& result, const CMatrix<Type>& matrix) {
    for(unsigned int i = 0; i < matrix.height(); i++) {
        for(unsigned int j = 0; j < matrix.width(); j++) {
            result << matrix[j][i] << "\t";
        }
        result << "\n";
    }
    return result;
}

// <begin> Конструкторы и деструкторы
template<typename Type>
bool CMatrix<Type>::isEmpty() const {
    if(data.size() == 0) return true; else return false;
}

template<typename Type>
bool CMatrix<Type>::isSquare() const {
    if(data.size() == data[0].size()) return true; else return false;
}

template<typename Type>
CMatrix<Type>::CMatrix(const unsigned int n) {
    data.resize(n, vector<Type> (n, 0));
    for(unsigned int i = 0; i < n; i++) {
	    data[i][i] = 1;
    }
}

template<typename Type>
CMatrix<Type>::CMatrix(const unsigned int x, const unsigned int y) {
    data.resize(x, vector<Type> (y, 0));
}

template<typename Type>
CMatrix<Type>::CMatrix(const CMatrix& another) {
    data = another.data;
}

template<typename Type>
CMatrix<Type>::CMatrix(const CMatrix& another, const unsigned int x, const unsigned int y) {
    if( (x >= another.width()) || (y >= another.height()) ) throw COutOfRange("There are not such rows\\cols");
    data = another.data;
    data.erase(data.begin()+x);
    for(unsigned int i = 0; i < data.size(); i++) {
        data[i].erase(data[i].begin()+y);
    }
}

template<typename Type>
CMatrix<Type>::CMatrix(const vector< vector<Type> >& _data) {
	data = _data;
}

template<typename Type>
CMatrix<Type>::~CMatrix() {}
// <end> Конструкторы и деструкторы

//След матрицы
template<typename Type>
Type CMatrix<Type>::trace() const {
    Type result = 0;
    for(int i = 0; i < data.size(); i++) {
        result += data[i][i];
    }
    return result;
}

//Определитель матрицы
template<typename Type>
Type CMatrix<Type>::det() const {
    if(!((*this).isSquare())) throw CIllegalOperation("Not square!");
    if(data.size() == 1) {
        return data[0][0];
    }
    Type result = 0;
    for(unsigned int i = 0; i < data.size(); i++) {
        CMatrix tempMatrix(*this, i, 0);
        if (i % 2 == 0) {
            result =  result + (data[i][0] * tempMatrix.det());
        } else {
            result = result - (data[i][0] * tempMatrix.det());
        }
    }
    return result;
}

//Обратная матрица
template<typename Type>
CMatrix<Type> CMatrix<Type>::invert() const {
    if(!(*this).isSquare()) throw CIllegalOperation("Not square!");
    if((*this).det == 0) throw CIllegalOperation("Det is null");
    CMatrix result(data.size());
    for(unsigned int i = 0; i < data.size(); i++) {
        for(unsigned int j = 0; j < data.size(); j++) {
            CMatrix tempMatrix(*this, j, i);
            if( (i + j) % 2 == 0 )
                result[i][j] += tempMatrix.det();
            else
                result[i][j] -= tempMatrix.det();
        }
    }
    result /= result.det();
    return result;
}

//Транспонирование
template<typename Type>
CMatrix<Type> CMatrix<Type>::transposed() const {
    CMatrix temp(*this);
    for(unsigned int i = 0; i < data.size(); i++)
        for(unsigned int j = 0; j < data[0].size(); j++)
            temp[j][i] = (*this)[i][j];
    return temp;

}

template<typename Type>
void CMatrix<Type>::transpose() {
    CMatrix temp(*this);
    for(unsigned int i = 0; i < data.size(); i++)
        for(unsigned int j = 0; j < data[0].size(); j++)
            data[j][i] = temp[i][j];
}

// <begin> Операторы

template<typename Type>
CMatrix<Type>& CMatrix<Type>::operator = (const CMatrix& another) {
    if( ((*this).width() != another.width()) || ((*this).height() != another.height()) ) throw CIllegalOperation("Sizes are incorrect");
    data = another.data;
    return *this;
};

template<typename Type>
CMatrix<Type> CMatrix<Type>::operator + (const CMatrix& another) const{
    if( ((*this).width != another.width) || ((*this).height != another.height) ) throw CIllegalOperation("Sizes are incorrect");
    CMatrix tempMatrix(another.width(), another.height());
    for(unsigned int i = 0; i < another.height(); i++) {
        for(unsigned int j = 0; j < another.width(); j++) {
            tempMatrix[j][i] = data[j][i] + another[j][i];
        }
    }
    return tempMatrix;
}

template<typename Type>
CMatrix<Type>& CMatrix<Type>::operator += (const CMatrix& another) {
    if( ((*this).width != another.width) || ((*this).height != another.height) ) throw CIllegalOperation("Sizes are incorrect");
    for(unsigned int i = 0; i < another.height(); i++) {
        for(unsigned int j = 0; j < another.width(); j++) {
            data[j][i] += another[j][i];
        }
    }
    return *this;
}

template<typename Type>
CMatrix<Type> CMatrix<Type>::operator - (const CMatrix& another) const{
    if( ((*this).width != another.width) || ((*this).height != another.height) ) throw CIllegalOperation("Sizes are incorrect");
    CMatrix tempMatrix(another.width(), another.height());
    for(unsigned int i = 0; i < another.height(); i++) {
        for(unsigned int j = 0; j < another.width(); j++) {
            tempMatrix[j][i] = data[j][i] - another[j][i];
        }
    }
    return tempMatrix;
}

template<typename Type>
CMatrix<Type>& CMatrix<Type>::operator -= (const CMatrix& another) {
    if( ((*this).width != another.width) || ((*this).height != another.height) ) throw CIllegalOperation("Sizes are incorrect");
    for(unsigned int i = 0; i < another.height(); i++) {
        for(unsigned int j = 0; j < another.width(); j++) {
            data[j][i] -= another[j][i];
        }
    }
    return *this;
}

template<typename Type>
CMatrix<Type> CMatrix<Type>::operator * (const CMatrix& another) const {
    if( ((*this).height() != another.width()) ) {
	    throw CIllegalOperation("Sizes are incorrect");
    }

    CMatrix tempMatrix(another.width(), data[0].size());
    for(unsigned int i = 0; i < data[0].size(); i++) {
        for(unsigned int j = 0; j < another.width(); j++) {
            for(unsigned int k = 0; k < another.height(); k++) {
                tempMatrix[j][i] += another[j][k] * data[k][i];
            }
        }
    }
    return tempMatrix;
}


template<typename Type>
CMatrix<Type>& CMatrix<Type>::operator *= (const CMatrix& another) {
    if( ((*this).height() != another.width()) ) throw CIllegalOperation("Sizes are incorrect");
    CMatrix<Type> tempMatrix(*this);
    for(unsigned int i = 0; i < tempMatrix.height(); i++) {
        for(unsigned int j = 0; j < another.width(); j++) {
            data[j][i] = 0;
            for(unsigned int k = 0; k < another.height(); k++) {
                data[j][i] += another[j][k] * tempMatrix[k][i];
            }
        }
    }
    return *this;
}


template<typename Type>
CMatrix<Type> CMatrix<Type>::operator * (const int another) const {
    CMatrix tempMatrix(data.size(), data[0].size());
    for(unsigned int i = 0; i < data[0].size(); i++) {
        for(unsigned int j = 0; j < data.size(); j++) {
            tempMatrix[j][i] = data[j][i] * another;
        }
    }
    return tempMatrix;
}

template<typename Type>
CMatrix<Type>& CMatrix<Type>::operator *= (const int another) {
    for(unsigned int i = 0; i < data[0].size(); i++) {
        for(unsigned int j = 0; j < data.size(); j++) {
            data[j][i] *= another;
        }
    }
    return *this;
}

template<typename Type>
CMatrix<Type> CMatrix<Type>::operator / (const int another) const {
    CMatrix tempMatrix(data.size(), data[0].size());
    for(unsigned int i = 0; i < data[0].size(); i++) {
        for(unsigned int j = 0; j < data.size(); j++) {
            tempMatrix[j][i] = data[j][i] / another;
        }
    }
    return tempMatrix;
}

template<typename Type>
CMatrix<Type>& CMatrix<Type>::operator /= (const int another) {
    for(unsigned int i = 0; i < data[0].size(); i++) {
        for(unsigned int j = 0; j < data.size(); j++) {
            data[j][i] /= another;
        }
    }
    return *this;
}

template<typename Type>
const vector<Type>& CMatrix<Type>::operator[] (const unsigned int x) const {
    if(x >= (*this).width()) throw COutOfRange("Sizes are incorrect");
    return data[x];
}

template<typename Type>
vector<Type>& CMatrix<Type>::operator[] (const unsigned int x) {
    if( ( x >= (*this).width()) ) throw COutOfRange("Sizes are incorrect");
    return data[x];
}

template<typename Type>
bool CMatrix<Type>::operator == (const CMatrix& another) const {
    if( (data.size() != another.width()) || (data[0].size() != another.height()) ) return false;
    for(unsigned int i = 0; i < data.size(); i++)
        for(unsigned int j = 0; j < data[0].size(); j++)
            if(data[i][j] != another[i][j]) return false;
    return true;
}

template<typename Type>
bool CMatrix<Type>::operator != (const CMatrix& another) const {
    return !(*this == another);
}
// <end> Операторы

// Прочая ересь
template<typename Type>
unsigned int CMatrix<Type>::width() const {
    return data.size();
}

template<typename Type>
unsigned int CMatrix<Type>::height() const {
    return data[0].size();
}

template<typename Type>
void CMatrix<Type>::randomize() {
    srand((unsigned)time(0));
    for(unsigned int i = 0; i < data.size(); i++) {
        for(unsigned int j = 0; j < data[i].size(); j++)
            data[i][j] = rand() % 2;
    }
}
