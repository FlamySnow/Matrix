#include <iostream>
#include "pointed_fennec.h"

namespace fennec {
    Line* input (int &rm) {
        const char *err = "";
        Line *matrix = nullptr;
        int m = 0;
        do {
            std::cout << err << std::endl;
            std::cout << "Please, enter number of lines: --> ";
            err = "You are wrong, please, repeat.";
            if (getNum(m) < 0)
                return nullptr;
        } while (m < 1);
        try {
            matrix = new Line[m];
        }
        catch (std::bad_alloc &ba){
            std::cout << "Too many rows in matrix: " << ba.what() << std::endl;
            return nullptr;
        }
        Line* p = matrix;
        for (int i = 0; i < m; i++, p++){
            err = "";
            do{
                std::cout << err << std::endl;
                std::cout << "Enter number of items in line #" << i + 1 << " --> ";
                err = "You are wrong, please, repeat.";
                if (getNum(p->n) < 0) {
                    erase(matrix, i);
                    return nullptr;
                }
            } while (p->n < 1);
            try {
                p->a = new int[p->n];
            }
            catch (std::bad_alloc &ba) {
                std::cout << "Too many items in line: " << ba.what() << std::endl;
                erase(matrix, i);
                return nullptr;
            }
            int *ptr = p->a;
            std::cout << "Please, enter items for matrix line #" << i + 1 << ":" << std::endl;
            for (int j = 0; j < p->n; j++, ptr++){
                if (getNum(*ptr) < 0){
                    erase(matrix, i + 1);
                    return nullptr;
                }
            }
        }
        rm = m;
        return matrix;
    }
    void output (const char *msg, Line *a, int m){
        int i, j;
        std::cout << msg << ":" << std::endl;
        Line* ptr = a;
        for (i = 0; i < m; i++, ptr++){
            int* p = ptr->a;
            for (j = 0; j < ptr->n; j++, p++)
                std::cout << *p << " ";
            std::cout << std::endl;
        }
    }
    Line* erase(Line *&matrix, int m){
        Line* p = matrix;
        for (int i = 0; i < m; i++, p++)
            delete[] p->a;
        delete[] matrix;
        return nullptr;
    }
    Line* createNewMatrix( Line *&oldMatrix,const int &n){
        Line *newMatrix = nullptr;
        int max;
        try {
            newMatrix = new Line[n];
        }
        catch (std::bad_alloc &ba){
            std:: cout << "Too many rows in matrix:" << ba.what() << std::endl;
            return nullptr;
        }
        Line* pold = oldMatrix;
        Line* pnew = newMatrix;
        for (int i = 0; i < n; i++, pold++, pnew++){
            max = maxItem(*pold);
            pnew->n = max;
            try {
                pnew->a = new int[max];
            }
            catch (std::bad_alloc &ba) {
                std::cout << "Too many items in line: " << ba.what() << std::endl;
                erase(newMatrix, max);
                return nullptr;
            }
            int* ptrnew = pnew->a;
            int* ptrold = pold->a;
            for (int j = 0; j < max; j++, ptrnew++, ptrold++){
                *ptrnew = *ptrold;
            }
        }
        return newMatrix;
    }
    int maxItem(const Line &row){
        int res = row.a[0];
        int j = 0;
        for (int i = 0; i < row.n; i++){
            if (isgreater(row.a[i], res)) {
                res = row.a[i];
                j = i;
            }
        }
        return j + 1;
    }
}