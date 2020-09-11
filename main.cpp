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
#include "pointed_fennec.h"

using namespace fennec;

int main() {
    Line *arr;
    Line *res;
    int m = 0;
    arr = input(m);
    if (!arr){
        std::cout << "incorrect data" << std::endl;
        return 1;
    }
    res = createNewMatrix(arr, m);
    if (!res){
        std::cout << "Error in allocate memory" << std::endl;
        erase(arr, m);
        return 1;
    }
    output("Sourced matrix", arr, m);
    output("Resulted matrix", res, m);
    erase(arr, m);
    erase(res, m);
    return 0;
}