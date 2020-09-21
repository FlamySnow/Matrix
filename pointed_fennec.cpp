#include <iostream>
#include "tricky_fennec.h"

namespace fennec {
    Matrix* input (int &m, int &n){
        Matrix *matrix;
        const char* err = "";
        m = n = -1;
        do {
            std::cout << err << std::endl;
            std::cout << "Please, enter size of matrix (m x n): --> ";
            if (getNum(m) < 0){
                return nullptr;
            }
            if (getNum(n) < 0){
                return nullptr;
            }
        } while ((m < 1) ||(n < 1));
        try {
            matrix = new Matrix;
            matrix->line = new Line *[m];
        }
        catch (std::bad_alloc &ba){
            std::cout << "Sorry, memory allocation error: " << ba.what() << std::endl;
            return nullptr;
        }
        for (int i = 0; i < m; i++){
            matrix->line[i] = nullptr;
        }
        Data* tmp;
        std::cout << "If you want to stop, please, enter indexes below 1 above matrix size." << std::endl;
        do {
            tmp = new Data;
            std::cout << "Please, enter the first index: --> ";
            if (getNum(tmp->i) < 0){
                erase(matrix, m);
                delete tmp;
                return nullptr;
            }
            std::cout << "Please, enter the second index: --> ";
            if (getNum(tmp->j) < 0){
                erase(matrix, m);
                delete tmp;
                return nullptr;
            }
            std::cout << "Please, enter a value of the element: -->";
            if (getNum(tmp->a) < 0){
                erase(matrix, m);
                delete tmp;
                return nullptr;
            }
            if (tmp->i >= 1 && tmp->i <= m && tmp->j >= 1 && tmp->j <= n){
                matrix = insert(matrix, tmp, m);
                if (!matrix){
                    std::cout << "Sorry, memory allocation error: " << std::endl;
                    return nullptr;
                }
            }
        } while (tmp->i >= 1 && tmp->i <= m && tmp->j >= 1 && tmp->j <= n);
        delete tmp;
        return matrix;
    }
    Matrix* insert(Matrix* matrix, Data* tmp, int m){
        Line* first = matrix->line[tmp->i - 1];
        if (!first){ //если в строке нет элементов
            try {
                first = new Line;
                first->item = tmp;
                first->ptr = nullptr;
                matrix->line[tmp->i - 1] = first;
            }
            catch(std::bad_alloc &ba){
                erase(matrix, m);
                return nullptr;
            }
            return matrix;
        }
        if (first->item->j > tmp->j){ //если индекс j первого элемента больше индекса вставляемого
            try {
                matrix->line[tmp->i - 1] = new Line;
                matrix->line[tmp->i - 1]->item = tmp;
                matrix->line[tmp->i - 1]->ptr = first;
            }
            catch (std::bad_alloc &ba){
                erase(matrix, m);
                return nullptr;
            }
            return matrix;
        }
        while (first && first->ptr){
            if (first->item->j == tmp->j){//индексы равны
                delete first->item;
                first->item = tmp;
                return matrix;
            }
            if (first->item->j < tmp->j && first->ptr->item->j > tmp->j){
                Line* next = first->ptr;
                try {
                    next = new Line;
                    next->item = tmp;
                    next->ptr = first->ptr;
                    first->ptr = next;
                    first = nullptr;
                    return matrix;
                }
                catch (std::bad_alloc &ba){
                    erase(matrix, m);
                    return nullptr;
                }
            }
            first = first->ptr;
        }
        if (first){ //дошли до конца списка
            try {
                first->ptr = new Line;
                first->ptr->item = tmp;
                first->ptr->ptr = nullptr;
            }
            catch (std::bad_alloc &ba){
                erase(matrix, m);
                return nullptr;
            }
        }
        return matrix;
    }
    void erase (Matrix* matrix, int m) {
        for (int i = 0; i < m; ++i) {
            Line *first = matrix->line[i];
            while (first) {
                Line *temp;
                temp = first->ptr;
                delete first;
                first = temp;
            }
        }
        delete[] matrix->line;
        delete matrix;
    }
    void output (Matrix* matrix, int m){
        for (int i = 0; i < m; i++){
            Line* ptr = matrix->line[i];
            while (ptr){
                std::cout << ptr->item->a << " ";
                ptr = ptr->ptr;
            }
            std::cout << std::endl;
        }
    }
    int check(Line* row, int n){
        Line* ptr = row;
        int sz = 0;
        while (ptr){
            sz++;
            ptr = ptr->ptr;
        }
        if (sz != n)
            return 0;
        return 1;
    }
    int maxItem(Line* row){
        Line* ptr = row;
        int max = ptr->item->a;
        while (ptr){
            if (ptr->item->a > max){
                max = ptr->item->a;
            }
            ptr = ptr->ptr;
        }
        return max;
    }
    Matrix* createNewMatrix(Matrix* matrix, int m, int n){
        int max;
        Matrix* newMatrix;
        try {
            newMatrix = new Matrix;
            newMatrix->line = new Line *[m];
        }
        catch (std::bad_alloc &ba){
            std::cout << "Sorry, memory allocation error: " << ba.what() << std::endl;
            return nullptr;
        }
        for (int i = 0; i < m; i++){
            newMatrix->line[i] = nullptr;
        }
        for (int i = 0; i < m; i++){
            Line* ptr = matrix->line[i];
            if (!ptr)
                continue;
            max = maxItem(ptr);
            if (max < 0 && !check(ptr, n)){
                while (ptr){
                    try {
                        Data* tmp = new Data;
                        tmp->a = ptr->item->a;
                        tmp->i = ptr->item->i;
                        tmp->j = ptr->item->j;
                        insert(newMatrix, tmp, m);
                    }
                    catch (std::bad_alloc &ba){
                        std::cout << "Sorry, memory allocation error: " << ba.what() << std::endl;
                        erase(newMatrix, m);
                        return nullptr;
                    }
                    ptr = ptr->ptr;
                }
            }
            while (ptr) {
                try {
                    Data *tmp = new Data;
                    tmp->a = ptr->item->a;
                    tmp->i = ptr->item->i;
                    tmp->j = ptr->item->j;
                    insert(newMatrix, tmp, m);
                }
                catch (std::bad_alloc &ba){
                    std::cout << "Sorry, memory allocation error: " << ba.what() << std::endl;
                    erase(newMatrix, m);
                    return nullptr;
                }
                if (ptr->item->a == max)
                    break;
                ptr = ptr->ptr;
            }
        }
        return newMatrix;
    }
}
