#include "Matrix.h"
#include <stdexcept>
#include <algorithm>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    //Θ(1)
    if(nrLines <= 0 || nrCols <= 0)
        throw invalid_argument("Invalid nr of lines or column");
    nr_lines = nrLines;
    nr_cols = nrCols;
    cols = new int[nrCols + 1];
    fill(cols, cols + nrCols + 1, 0);
    lines = new int[capacity];
    values = new int[capacity];
}


int Matrix::nrLines() const {
    //Θ(1)
	return nr_lines;
}


int Matrix::nrColumns() const {
    //Θ(1)
	return nr_cols;
}


TElem Matrix::element(int i, int j) const {
    //Θ(nr_lines)
    if(i>=nr_lines || j>=nr_cols || i < 0 || j < 0)
        throw invalid_argument("Invalid indexes");
	for(int index=cols[j];index<cols[j+1];index++)
        if(lines[index] == i)
            return values[index];
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
    /*
     * Best case: M[i][j] != 0 and e!=0 -> Θ(nr_lines)
     *            M[i][j] == 0 and e == 0 -> same complexity
     *
     * Worst case: M[i][j] == 0 and e!= 0 and resize required -> Θ(nr_lines + nr_cols + length)
     *             M[i][j] != 0 and e == 0 and downsize required -> same complexity
     *
     * Average case:
     * -4 cases: M[i][j] != 0 and e!=0 or M[i][j] == 0 and e == 0 or M[i][j] == 0 and e!= 0 or M[i][j] != 0 and e == 0
     *
     * The likelihood of each scenario occurring in the algorithm depends on the sparsity of the matrix and the distribution
     * of the (i,j) positions being accessed. However, on average, we can assume that the update operation will occur more frequently
     * than the insert operation.
     *
     * T(N) = 1/2(Θ(nr_lines)) + 1/2(Θ(nr_lines + nr_cols + length)) = O(nr_lines + nr_cols + length)
     *
     */
    if(i>=nr_lines || j>=nr_cols || i < 0 || j < 0)
        throw exception();
    int succ_i = 100000000;
    TElem old = NULL_TELEM;
    for(int index=cols[j];index<cols[j+1];index++) {
        if (lines[index] == i) {
            old = values[index];
            if(e !=0)
                values[index] = e;
            else{
                for(int position = j + 1; position <= nr_cols; position ++)
                        cols[position] --;
                for(int position = index ; position < length ; position ++)
                {
                    values[position] = values[position+1];
                    lines[position] = lines[position+1];
                }
                length --;
                if (length > 0 && length == capacity / 4)
                    downsize();
            }
            return old;
        }
        if (lines[index] > i && index < succ_i )
            succ_i = index;
    }
    if(e != 0) {
        if (length == capacity)
            resize();
        if(succ_i == 100000000)
            succ_i = cols[j+1];
        for(int position = j + 1; position <= nr_cols; position++)
            cols[position]++;
        for (int index = length - 1; index >= succ_i; index--){
            values[index + 1] = values[index];
            lines[index + 1] = lines[index];
        }
        lines[succ_i] = i;
        values[succ_i] = e;
        length++;
    }
	return old;
}

void Matrix::resize(int factor) {
    //Θ(length)
    capacity *= factor;

    auto* lines_resize = new TElem[capacity];
    auto* values_resize = new TElem[capacity];
    for (int i = 0; i < length; i++)
        {
        lines_resize[i] = lines[i];
        values_resize[i] = values[i];
        }

    delete[] lines;
    lines = lines_resize;
    delete[] values;
    values = values_resize;
}

void Matrix::downsize(int factor){
    //Θ(length)
    capacity /= factor;

    auto* lines_resize = new TElem[capacity];
    auto* values_resize = new TElem[capacity];
    for (int i = 0; i < length; i++)
    {
        lines_resize[i] = lines[i];
        values_resize[i] = values[i];
    }

    delete[] lines;
    lines = lines_resize;
    delete[] values;
    values = values_resize;
}


