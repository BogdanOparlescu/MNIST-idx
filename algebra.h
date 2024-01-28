#include <iostream>
#include <math.h>
#include <time.h>

class Vector
{
public:
    int length;
    float *data;

    Vector() : length(0), data(nullptr) {}

    Vector(int length)
    {
        this->length = length;
        this->data = (float *)malloc(sizeof(float) * length);
    }

    Vector(float *data, int length) : Vector(length)
    {
        this->assign(data);
    }

    Vector(const std::initializer_list<float> &values) : Vector(values.size())
    {
        int i = 0;
        for (float value : values)
            this->data[i++] = value;
    }

    float& operator[](int i)
    {
        return data[i];
    }

    void copy(Vector v)
    {
        for (int i = 0; i < length; i++)
            data[i] = v.data[i];
    }

    void assign(const int c)
    {
        assign((float)c);
    }

    void assign(const float c)
    {
        for (int i = 0; i < length; i++)
            this->data[i] = c;
    }

    void assign(float *data)
    {
        for (int i = 0; i < length; i++)
            this->data[i] = data[i];
    }
    
    static void concat(Vector &v, Vector c)
    {
        Vector concat = Vector(v.length + c.length);
        for (int i = 0; i < v.length; i++)
            concat.data[i] = v.data[i];
        for (int i = 0; i < c.length; i++)
            concat.data[i + v.length] = c.data[i];
        v = concat;
    }

    static void precat(Vector &v, Vector c)
    {
        Vector concat = Vector(v.length + c.length);
        for (int i = 0; i < c.length; i++)
            concat.data[i] = c.data[i];
        for (int i = 0; i < v.length; i++)
            concat.data[i + c.length] = v.data[i];
        v = concat;
    }

    friend std::ostream &operator<<(std::ostream &os, Vector v)
    {
        for (int i = 0; i < v.length; i++)
            os << v.data[i] << ' ';
        os << '\n';
        return os;
    }

    void Save(FILE *file)
    {
        fwrite(&length, sizeof(int), 1, file);
        fwrite(data, sizeof(float), length, file);
    }

    static Vector Load(FILE *file)
    {
        int length = 0;
        fread(&length, sizeof(int), 1, file);
        Vector v = Vector(length);
        fread(v.data, sizeof(float), length, file);
        return v;
    }
};

class Matrix
{
public:
    int rows, cols;
    float **data;

    Matrix():rows(0),cols(0),data(nullptr){}

    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        this->data = (float **)malloc(sizeof(float *) * rows);
        for (int i = 0; i < rows; i++)
            this->data[i] = (float *)malloc(sizeof(float) * cols);
    }

    Matrix(const std::initializer_list<std::initializer_list<float>> &values): Matrix(values.size(), values.begin()->size())
    {
        int i = 0, j = 0;
        for (const auto &row : values)
        {
            for (float value : row)
                this->data[i][j++] = value;
            j = 0;
            ++i;
        }
    }

    Matrix(Vector v):Matrix(v.length,1)
    {
        for(int i=0;i<v.length;i++)
            data[i][0]=v.data[i];
    }

    static Matrix fromArray(Vector vector)
    {
        Matrix m = Matrix(vector.length, 1);
        for (int i = 0; i < vector.length; i++)
            m.data[i][0] = vector.data[i];
        return m;
    }

    Vector toVector()
    {
        Vector v = Vector(rows * cols);
        int k = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                v.data[k++] = data[i][j];
        return v;
    }

    float* operator[](int i) 
    {
        return data[i];
    }

    void copy(Matrix m)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = m.data[i][j];
    }

    void assign(float **data)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                this->data[i][j] = data[i][j];
    }

    static void assign(Matrix matrix, float **data)
    {
        for (int i = 0; i < matrix.rows; i++)
            for (int j = 0; j < matrix.cols; j++)
                matrix.data[i][j] = data[i][j];
    }

    void assign(const int c)
    {
        assign((float)c);
    }

    void assign(const float c)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                this->data[i][j] = c;
    }

    static void assign(Matrix matrix, const float c)
    {
        for (int i = 0; i < matrix.rows; i++)
            for (int j = 0; j < matrix.cols; j++)
                matrix.data[i][j] = c;
    }

    void assign(std::initializer_list<std::initializer_list<float>> values)
    {
        int i = 0, j = 0;
        for (const auto &row : values)
        {
            for (float value : row)
                this->data[i][j++] = value;
            j = 0;
            ++i;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, Matrix m)
    {
        for (int i = 0; i < m.rows; i++)
        {
            for (int j = 0; j < m.cols; j++)
                os << m.data[i][j] << ' ';
            os << '\n';
        }
        return os;
    }

    void add(Matrix m)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] += m.data[i][j];
    }

    void add(float n)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] += n;
    }

    static Matrix add(Matrix m1, Matrix m2)
    {
        Matrix s = Matrix(m1.rows, m1.cols);
        for (int i = 0; i < m1.rows; i++)
            for (int j = 0; j < m1.cols; j++)
                s.data[i][j] = m1.data[i][j] + m2.data[i][j];
        return s;
    }

    void sub(Matrix m)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] += m.data[i][j];
    }

    static Matrix sub(Matrix m1, Matrix m2)
    {
        Matrix s = Matrix(m1.rows, m1.cols);
        for (int i = 0; i < m1.rows; i++)
            for (int j = 0; j < m1.cols; j++)
                s.data[i][j] = m1.data[i][j] - m2.data[i][j];
        return s;
    }

    void multiply(float n)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] *= n;
    }

    static Matrix multiply(Matrix m, float n)
    {
        Matrix x = Matrix(m.rows, m.cols);
        for (int i = 0; i < m.rows; i++)
            for (int j = 0; j < m.cols; j++)
                x.data[i][j] *= n;
        return x;
    }

    void multiply(Matrix m)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < m.cols; j++)
            {
                float s = 0;
                for (int k = 0; k < cols; k++)
                    s += (data[i][k] * m.data[k][j]);
                data[i][j] = s;
            }
    }

    static Matrix multiply(Matrix m1, Matrix m2)
    {
        Matrix x = Matrix(m1.rows, m2.cols);
        for (int i = 0; i < m1.rows; i++)
            for (int j = 0; j < m2.cols; j++)
            {
                float s = 0;
                for (int k = 0; k < m1.cols; k++)
                    s += (m1.data[i][k] * m2.data[k][j]);
                x.data[i][j] = s;
            }
        return x;
    }

    Matrix transpose()
    {
        Matrix t = Matrix(cols, rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                t.data[i][j] = data[j][i];
        return t;
    }

    static Matrix transpose(Matrix matrix)
    {
        Matrix t = Matrix(matrix.cols, matrix.rows);
        for (int i = 0; i < matrix.cols; i++)
            for (int j = 0; j < matrix.rows; j++)
                t.data[i][j] = matrix.data[j][i];
        return t;
    }

    void map(float f(float))
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = f(data[i][j]);
    }

    static Matrix map(Matrix matrix, float f(float))
    {
        Matrix m=Matrix(matrix.rows,matrix.cols);
        for (int i = 0; i < matrix.rows; i++)
            for (int j = 0; j < matrix.cols; j++)
                m.data[i][j] = f(matrix.data[i][j]);
        return m;
    }

    void randomize()
    {
        srand(static_cast<unsigned>(time(0)));

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = ((float)rand() / RAND_MAX)-0.5; // ((float)rand() / RAND_MAX) * 0.1 - 0.05;
    }

    static void Save(Matrix matrix, FILE *file)
    {
        fwrite(&(matrix.rows), sizeof(int), 1, file);
        fwrite(&(matrix.cols), sizeof(int), 1, file);

        for (int i = 0; i < matrix.rows; ++i)
            fwrite(matrix.data[i], sizeof(float), matrix.cols, file);
    }

    static Matrix Load(FILE *file)
    {
        int rows, cols;
        fread(&rows, sizeof(int), 1, file);
        fread(&cols, sizeof(int), 1, file);

        Matrix matrix = Matrix(rows, cols);

        for (int i = 0; i < matrix.rows; ++i)
            fread(matrix.data[i], sizeof(float), matrix.cols, file);

        return matrix;
    }
};
