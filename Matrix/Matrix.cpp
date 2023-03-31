#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    nr_lines = nrLines;
    nr_cols = nrCols;
    cols = new int(nrCols + 1);
    lines = new int(capacity);
    values = new int(capacity);
}


int Matrix::nrLines() const {
	return nr_lines;
}


int Matrix::nrColumns() const {

	return nr_cols;
}


TElem Matrix::element(int i, int j) const {
    if(i>=nr_lines || j>=nr_cols)
        throw exception();
	for(int index=cols[j];index<cols[j+1];index++)
        if(lines[index] == i)
            return values[index];
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
    if(i>=nr_lines || j>=nr_cols)
        throw exception();
    int pred_i = nr_cols ;
    int succ_i = 0;
    TElem old = NULL_TELEM;
    for(int index=cols[j];index<cols[j+1];index++) {
        if (lines[index] == i && e != 0) {
            old = values[index];
            values[index] = e;
            return old;
        }
        if (pred_i > lines[index])
            pred_i = lines[index];
        if (succ_i < lines[index])
            succ_i = lines[index];
    }
    if(length + 1 > capacity && e !=0)
        //resize
        return 0;
    for(int index = length -1 ; index >= succ_i ; index --)
        X[i+1] = X[i];
    X[p] = val;
    n ++;



	return old;
}


