#include "mnist.h"

void Seek(FILE *img, FILE *labels)
{
    fseek(img, 16, SEEK_SET);
    fseek(labels, 8, SEEK_SET);
}

void printIndex(int i, FILE *img, FILE *labels)
{
    fseek(img, 784 * i, SEEK_CUR);
    fseek(labels, i, SEEK_CUR);
    mnist_set m;
    m.LoadNext(img, labels);
    m.star();
}

void Init(FILE *img, FILE *labels)
{
    int magic = 0;
    int length = 0;
    int rows = 0;
    int cols = 0;
    fread(&magic, 4, 1, img);
    magic = __builtin_bswap32(magic);
    printf("Magic is %i\n", magic);

    fread(&length, 4, 1, img);
    length = __builtin_bswap32(length);
    printf("Length is %i\n", length);

    fread(&rows, 4, 1, img);
    rows = __builtin_bswap32(rows);
    printf("Rows is %i\n", rows);

    fread(&cols, 4, 1, img);
    cols = __builtin_bswap32(cols);
    printf("Cols is %i\n", cols);
}

int main()
{
    FILE *img = fopen("training/train-images.idx3-ubyte", "rb");
    FILE *labels = fopen("training/train-labels.idx1-ubyte", "rb");
    Seek(img, labels);
    printIndex(10000, img, labels);
    // fseek(img,784,SEEK_CUR);
    // fseek(labels,1,SEEK_CUR);
    // for (int i = 0; i < 10; i++)
    // {
    //     mnist_set m;
    //     m.LoadNext(img, labels);
    //     m.star();
    // }
}