#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::cerr;

static double MAX_PRECISION = 0.00000000000001;
template <typename T>
    inline bool null_compare(const T& x){
        return (x<MAX_PRECISION && x>-MAX_PRECISION);
    }
template <typename T> class Matrix;
template <typename T> istream& operator>> (istream&, Matrix<T>&);
template <typename T> ostream& operator<< (ostream&, Matrix<T> const &);
template <typename T> Matrix<T> compose (const char*, Matrix<T> const &, Matrix<T> const &);
template <typename T> const Matrix<T> operator+(Matrix<T> const &, Matrix<T> const &);
template <typename T> const Matrix<T> operator-(Matrix<T> const &, Matrix<T> const &);
template <typename T> const Matrix<T> operator*(Matrix<T> const &, Matrix<T> const &);
template <typename T> const Matrix<T> operator*(T const &, Matrix<T> const &);
template <typename T> const Matrix<T> operator*(Matrix<T> const &, T const &);

template <typename T>
class Matrix
{
private:
    int _rowcnt;
    int _colcnt;
    vector<vector<T> > elements;
public:
    Matrix() : elements(vector<vector<T> >(0)), _rowcnt(0), _colcnt(0) {};
    Matrix(int, int, T);
    Matrix(const char* flag, int, int);
    Matrix(const Matrix & copy) : _rowcnt(copy._rowcnt), _colcnt(copy._colcnt), elements(copy.elements){}

    int getRowCount() const{ return _rowcnt; }
    int getColCount() const{ return _colcnt; }

    friend istream& operator>> <>(istream&, Matrix<T>&);
    friend ostream& operator<< <>(ostream&, Matrix<T> const &);
    friend const Matrix<T> operator+ <>(Matrix<T> const &, Matrix<T> const &);
    friend const Matrix<T> operator- <>(Matrix<T> const &, Matrix<T> const &);
    friend const Matrix<T> operator* <>(Matrix<T> const &, Matrix<T> const &);
    friend const Matrix<T> operator* <>(T const &, Matrix<T> const &);
    friend const Matrix<T> operator* <>(Matrix<T> const &, T const &);
    Matrix<T>& operator-();
    vector <T>& operator[] (int);
    vector <T> operator[] (int) const;
    operator Matrix<double>();

    double getDet();
    T getTrace();
    Matrix<double> triangulate();
    Matrix<double> rtriangulate();
    Matrix<double> inverse();
    Matrix<T> transpose();
    friend Matrix<T> compose <>(const char*, Matrix<T> const &, Matrix<T> const &);
    Matrix<T> extract(int, int, int, int);
    void expand(int, int, T);
};
    ///Constructors
template <typename T>
    Matrix<T>::Matrix(const char* flag, int __rowcnt,int __colcnt) :
    elements(vector<vector<T> >(__rowcnt)), _rowcnt(__rowcnt), _colcnt(__colcnt){
        if (flag=="identity"){
            for (int i=0; i<__rowcnt; i++)
                elements[i]=vector<T>(__colcnt, T(0));
            int min;
            if (_rowcnt<_colcnt) min=_rowcnt;
            else min=_colcnt;
            for (int i=0; i<min; i++)
                elements[i][i]=T(1);
        }
    }
template <typename T>
    Matrix<T>::Matrix(int __rowcnt, int __colcnt, T const __value=T()) :
    elements(vector<vector<T> >(__rowcnt)), _rowcnt(__rowcnt), _colcnt(__colcnt) {
        for (int i=0; i<__rowcnt; i++)
            elements[i]=vector<T>(__colcnt, __value);
    }
    ///Input & Output
template <typename T>
    istream& operator>> (istream& s, Matrix<T>& m){
        for (int i=0; i<m._rowcnt; i++)
            for (int j=0; j<m._colcnt; j++)
                s>>m.elements[i][j];
        return s;
    }
template <typename T>
    ostream& operator<< (ostream& s, Matrix<T> const & m){
        for (int i=0; i<m._rowcnt; i++){
            for (int j=0; j<m._colcnt; j++)
                s<<m.elements[i][j]<<" ";
            s<<endl;
        }
        return s;
    }
    ///Operators
template <typename T>
    const Matrix<T> operator+(Matrix<T> const & left, Matrix<T> const & right){
        int maxcol;
        int maxrow;
        if (left._colcnt>right._colcnt) maxcol=left._colcnt;
        else maxcol=right._colcnt;
        if (left._rowcnt>right._rowcnt) maxrow=left._rowcnt;
        else maxrow=right._rowcnt;
        Matrix<T> res(maxrow, maxcol);
        for(int i=0; i<maxrow; i++)
            for (int j=0; j<maxcol; j++){
                if ((i>=left._rowcnt && j>=right._colcnt) || (i>=right._rowcnt && j>=left._colcnt))
                    res.elements[i][j]=0;
                else
                if (i>=left._rowcnt || j>=left._colcnt)
                    res.elements[i][j]=right.elements[i][j];
                else
                if (i>=right._rowcnt || j>=right._colcnt)
                    res.elements[i][j]=left.elements[i][j];
                else
                res.elements[i][j]=right.elements[i][j]+left.elements[i][j];
            }
        return res;
    }

template <typename T>
    const Matrix<T> operator-(Matrix<T> const & left, Matrix<T> const & right){
        return (left+(-Matrix<T>(right)));
    }
template <typename T>
    const Matrix<T> operator*(Matrix<T> const & left, Matrix<T> const & right){
        if (left._colcnt==right._rowcnt){
            Matrix<T> res(left._rowcnt, right._colcnt);
            for (int i=0; i<left._rowcnt; i++)
                for (int j=0; j<right._colcnt; j++)
                    for (int k=0; k<left._colcnt; k++)
                        res.elements[i][j]+=(left.elements[i][k]*right.elements[k][j]);
            return res;
        }
        else{
            cerr<<"Operator* logic conditions error. Standart Matrix returned."<<endl;
            return (Matrix<T>(0,0));
        }
    }
template <typename T>
    const Matrix<T> operator* (T const & digit, Matrix<T> const & obj){
        Matrix<T> res(obj._rowcnt, obj._colcnt);
        for (int i=0; i<obj._rowcnt; i++)
            for (int j=0; j<obj._colcnt; j++)
                res.elements[i][j]=digit*obj.elements[i][j];
        return res;
    }
template <typename T>
    const Matrix<T> operator* (Matrix<T> const & obj, T const & digit){
        Matrix<T> res(obj._rowcnt, obj._colcnt);
        for (int i=0; i<obj._rowcnt; i++)
            for (int j=0; j<obj._colcnt; j++)
                res.elements[i][j]=digit*obj.elements[i][j];
        return res;
    }
template <typename T>
    Matrix<T>& Matrix<T>::operator-(){
        for (int i=0; i<_rowcnt; i++)
            for (int j=0; j<_colcnt; j++)
                elements[i][j]=-elements[i][j];
        return (*this);
    }
template <typename T>
    vector<T>& Matrix<T>::operator[] (int __x) { return (elements[__x]);}
template <typename T>
    vector<T> Matrix<T>::operator[] (int __x) const{ return (elements[__x]);}
template <typename T>
    Matrix<T>::operator Matrix<double>(){
        Matrix<double> res(_rowcnt, _colcnt);
        for (int i=0; i<_rowcnt; i++)
            for (int j=0; j<_colcnt; j++)
                res[i][j]=(double)elements[i][j];
        return res;
    }
    ///Special functions
template <typename T>
    Matrix<double> Matrix<T>::triangulate(){
        Matrix<double> res=(Matrix<double>)(*this);
        for (int i=0; i<res.getColCount(); i++){
            if (i<res.getRowCount()){
                bool is_null;
                if (null_compare<double>(res[i][i])) is_null=1;
                else is_null=0;
                int j=i+1;
                while (is_null==1 && j!=res.getRowCount()){
                    if (!null_compare<double>(res[j++][i])) is_null=0;
                }
                if (j!=res.getRowCount()){
                    vector<double> temp(getColCount());
                    temp=res[j-1];
                    res[j-1]=res[i];
                    res[i]=temp;
                }
                if (!null_compare<double>(res[i][i]))
                for (int k=i+1; k<res.getRowCount(); k++){
                    double frac=res[k][i]/res[i][i];
                    for (int z=i; z<res.getColCount(); z++){
                        res[k][z]-=frac*res[i][z];
                        if (null_compare<double>(res[k][z])) res[k][z]=0;
                    }
                }
            }
        }
        return res;
    }
template <typename T>
    Matrix<double> Matrix<T>::rtriangulate(){
        Matrix<double> res=(Matrix<double>)(*this);
        for (int i=res.getColCount()-1; i>=0; i--){
            if (i<res.getRowCount()){
                bool is_null;
                if (null_compare<double>(res[i][i])) is_null=1;
                else is_null=0;
                int j=i-1;
                while (is_null==1 && j>=0){
                    if (!null_compare<double>(res[j--][i])) is_null=0;
                }
                if (j<res.getRowCount() && j>=0){
                    vector<double> temp(res.getColCount());
                    temp=res[j+1];
                    res[j+1]=res[i];
                    res[i]=temp;
                }
                if (!null_compare<double>(res[i][i]))
                for (int k=i-1; k>=0; k--){
                    double frac=res[k][i]/res[i][i];
                    for (int z=res.getColCount()-1; z>=0; z--){
                        res[k][z]-=frac*res[i][z];
                        if (null_compare<double>(res[k][z])) res[k][z]=0;
                    }
                }
            }
        }
        return res;
    }
template <typename T>
    double Matrix<T>::getDet(){
        if (_rowcnt==_colcnt){
            Matrix<double> a=Matrix<double>(*this);
            a=a.triangulate();
            double res=1;
            for (int i=0; i<_colcnt; i++)
                res=res*a[i][i];
            return res;
        }
    }
template <typename T>
    T Matrix<T>::getTrace(){
        if (_rowcnt==_colcnt){
            T res=0;
            for (int i=0; i<_rowcnt; i++)
                res+=elements[i][i];
            return res;
        }
    }
template <typename T>
    Matrix<T> Matrix<T>::transpose(){
        Matrix<T> copy=Matrix(_colcnt, _rowcnt);
        for (int i=0; i<_rowcnt; i++)
            for (int j=0; j<_colcnt; j++)
                copy.elements[j][i]=elements[i][j];
        return copy;
    }
template <typename T>
    Matrix<T> compose(const char* flag, Matrix<T> const & first, const Matrix<T> & second){
        Matrix<T> res;
        if (flag=="right"){
            res=Matrix<T>(first._rowcnt,first._colcnt+second._colcnt, 0);
            for (int i=0; i<res._rowcnt; i++){
                for (int j=0; j<first._colcnt; j++)
                    res.elements[i][j]=first.elements[i][j];
                if (i<second._rowcnt)
                for (int j=first._colcnt; j<res._colcnt; j++)
                    res.elements[i][j]=second.elements[i][j-first._colcnt];
            }
        }
        return res;
    }
template <typename T>
    Matrix<T> Matrix<T>::extract(int posx0, int posy0, int posx1, int posy1){
        Matrix<T> res;
        if (posx0<=posx1 && posy0<posy1 && posy1<_rowcnt && posx1<_colcnt){
            res=Matrix<T>( posy1-posy0+1,posx1-posx0+1);
            for (int i=posy0; i<=posy1; i++)
                for (int j=posx0; j<=posx1; j++)
                    res.elements[i-posy0][j-posx0]=elements[i][j];
        }
        return res;
    }
template <typename T>
    Matrix<double> Matrix<T>::inverse(){
        try{
            if (_colcnt==_rowcnt && !((*this).getDet()<=MAX_PRECISION && (*this).getDet()>=-MAX_PRECISION )){
                Matrix<double> res;
                res=(Matrix<double>)(*this);
                res=compose("right", res, Matrix<double>("identity", _rowcnt, _colcnt));
                res=res.triangulate();
                res=res.rtriangulate();
                for (int i=0; i<res.getRowCount(); i++){
                    double temp=res[i][i];
                    for (int j=0; j<res.getColCount(); j++){
                        res[i][j]/=temp;
                        if (res[i][j]<MAX_PRECISION && res[i][j]>-MAX_PRECISION) res[i][j]=0;
                    }
                }
                res=res.extract(getColCount(), 0, res.getColCount()-1, res.getRowCount()-1);
                return res;
            }
            else
                throw std::logic_error("Inverse logic conditions error. Standart Matrix returned.");
        }
        catch (std::logic_error l) { cout<<l.what()<<endl; return (Matrix<T>(0,0)); }
    }
template <typename T>
    void Matrix<T>::expand(int x, int y, T const __value=T()){
        if (x>_rowcnt){
            _rowcnt=x;
            elements.resize(_rowcnt, vector<T>(_colcnt));
        }
        if (y>_colcnt){
            _colcnt=y;
            for (int i=0; i<_rowcnt; i++)
                elements[i].resize(_colcnt, __value);
        }
    }


#endif // MATRIX_H_INCLUDED
