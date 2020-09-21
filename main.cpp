/*Вариант 23
 * Из входного потока вводится прямоугольная сильно разреженная матрица целых чисел
 * [aij], i = 1, …, m, j = 1, …, n.  Значения m и n заранее не известны и вводятся из входного
 * потока.
 * Сформировать новую матрицу, поместив в ее i-ую строку элементы из i-ой строки исходной
 * матрицы, начиная с первого элемента и до (включая) максимального элемента строки.
 * В дополнительных функциях доступ к элементам массивов реализовать с помощью указателей.
 * Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.
*/

#include <iostream>
#include "tricky_fennec.h"

using namespace fennec;

int main () {
    Matrix *arr;
    int m = 0, n = 0;
    arr = input(m, n);
    if (!arr){
        std::cout << "Incorrect data." << std::endl;
        return 1;
    }
    std::cout << "Sourced matrix:" << std::endl;
    output(arr, m);
    Matrix *res;
    res = createNewMatrix(arr, m, n);
    if (!res){
        std::cout << "Incorrect data." << std::endl;
        erase(arr, m);
        return 1;
    }
    std::cout << "Result matrix:" << std::endl;
    output(res, m);
    erase(arr, m);
    erase(res, m);
    return 0;
}
