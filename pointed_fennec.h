namespace fennec{
    struct Data{
        int a;
        int i;
        int j;
    };
    struct Line{
        Data *item; //указатель на элемент
        Line *ptr; //указатель на следующий элемент
    };
    struct Matrix {
        Line **line;
    };
    template <class Type>
    int getNum(Type &a)
    {
        std::cin >> a;
        if (!std::cin.good()){
            return -1;
        }
        return 1;
    }
    int check(Line* row, int n);
    Matrix* createNewMatrix(Matrix* matrix, int m, int n);
    int maxItem(Line* row);
    void output (Matrix* matrix, int m);
    Matrix* input (int &m, int &n);
    Matrix* insert(Matrix* matrix, Data* tmp);
    void erase (Matrix* matrix, int m);
}
