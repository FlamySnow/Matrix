#include <iostream>

namespace fennec{
    struct Line{
        int n;
        int *a;
    };

    template<class Type>
    int getNum(Type &a)
    {
        std::cin >> a;
        if (!std::cin.good()){
            return -1;
        }
        return 1;
    }
    inline int isgreater(int a, int b){
        return a > b;
    }
    Line* input (int &rm);
    void output (const char *msg, Line *a, int m);
    Line* erase(Line *&matrix, int m);
    int maxItem(const Line &row);
    Line* createNewMatrix( Line *&oldMatrix,const int &n);
}

