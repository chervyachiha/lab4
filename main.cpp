#include <iostream>

template<typename I, int P, int Q>
struct Struct
{
    I** matrix;
};

template<typename T, int N, int M>
class Matrix
{
private:
    T** m_matrix;
    int n = 0;
    int m = 0;

    friend std::istream& operator>>(std::istream& in, Matrix<T, N, M>& other);
    friend std::ostream& operator<<(std::ostream& out, Matrix<T, N, M>& other);

public:

    //Базовый конструктор
    Matrix() {
        n = N;
        m = M;
        m_matrix = new T*[n];

        for (int i = 0; i < n; i++) {
            m_matrix[i] = new T[m];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                m_matrix[i][j] = 0;
            }
        }
    }

    //конструктор копирования
    Matrix(const Matrix& other)
    {
        for (int i = 0; i < n; i++)
            delete[] m_matrix[i];
        delete[] m_matrix;
        m_matrix = new T* [other.n];
        for (int i = 0; i < other.n; i++)
            m_matrix[i] = new T[m];
        n = other.n;
        m = other.m;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                m_matrix[i][j] = other.m_matrix[i][j];
    }

    //деструктор
    ~Matrix() {}

    //оператор присваивания копированием
    Matrix& operator= (const Matrix& other)
    {
        if (n == other.n && m == other.m)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    m_matrix[i][j] = other.m_matrix[i][j];
        else
            std::cout << "operation cannot be performed" << std::endl;
        return *this;
    }

    //оператор +=
    Matrix& operator += (const Matrix& other)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                m_matrix[i][j] = m_matrix[i][j] + other.m_matrix[i][j];
        return *this;
    }

    //оператор +
    Matrix operator + (Matrix& other)
    {
        Matrix m3(*this);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                m3.m_matrix[i][j] += other.m_matrix[i][j];
        return m3;
    }

    //оператор *=
    template<typename I, int P, int Q>
    Matrix& operator*= (Matrix<I, P, Q> & other)
    {
        Matrix<int,N, Q> m3;
        if (M == P) {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < Q; j++)
                    for (int k = 0; k < M; k++)
                        m3[i][j] += m_matrix[i][k] * other[k][j];
        }

        for (int i = 0; i < n; i++)
            delete[] m_matrix[i];
        delete[] m_matrix;
        m_matrix = new int* [N];

        for (int i = 0; i < N; i++)
            m_matrix[i] = new int[Q];
        n = N;
        m = Q;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                m_matrix[i][j] = m3[i][j];
        return *this;
    }


    //оператор *
    template<typename I, int P, int Q>
    Matrix operator* (const Matrix<I, P, Q>& other)
    {
        Matrix<int, N, Q> m3;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < Q; j++)
                for (int k = 0; k < M; k++)
                    m3.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
        return m3;
    }

    //оператор ++
    Matrix& operator++ (T)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                m_matrix[i][j]++;
        return *this;
    }

    //метод вычисления определителя
    T determinant()
    {
        if (n == 1 && m == 1)
            return m_matrix[0][0];
        if (n == 2 && m == 2)
            return m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
        if (n == 3 && m == 3)
            return (m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2] + m_matrix[1][0] * m_matrix[2][1] * m_matrix[0][2] + m_matrix[0][1] * m_matrix[1][2] * m_matrix[2][0] - m_matrix[0][2] * m_matrix[1][1] * m_matrix[2][0] - m_matrix[0][0] * m_matrix[1][2] * m_matrix[2][1] - m_matrix[2][2] * m_matrix[0][1] * m_matrix[1][0]);
    }

    //оператор для получения и изменения элемента матрицы по индексу
    T* operator[](int n)
    {
        return m_matrix[n];
    }

//оператор ввода
    friend std::istream& operator>>(std::istream& in, Matrix<T, N, M>& other)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                in >> other.m_matrix[i][j];
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, Matrix<T, N, M>& other)
    {
        for (int i = 0; i < other.n; i++) {
            for (int j = 0; j < other.m; j++) {
                out << other.m_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return out;
    }
};


//template<typename T, int N, int M>


//оператор вывода
//template<typename T, int N, int M>

int main()
{
    Matrix<int, 2, 1> m1;
    Matrix<int, 1, 3 > m2;


    std::cin >> m1;
    std::cin >> m2;

    m1 *= m2;
    std::cout << m1;
    return 0;
}