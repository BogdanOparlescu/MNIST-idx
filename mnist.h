#include "algebra.h"

class mnist_set
{
public:
    uint8_t image[28][28];
    uint8_t label;

    mnist_set() {}
    mnist_set(const char image[28][28], int label)
    {
        for (int i = 0; i < 28; i++)
            for (int j = 0; j < 28; j++)
                this->image[i][j] = image[i][j];
        this->label = label;
    }

    mnist_set LoadNext(FILE *img, FILE *labels)
    {
        for(int i=0;i<28;i++)
            fread(image[i],28,sizeof(uint8_t),img);
        fread(&label,1,sizeof(uint8_t),labels);
    }

    void star()
    {
        printf("Label is %i\n",label);
        for (int i = 0; i < 28; i++)
        {
            for (int j = 0; j < 28; j++)
                printf("%c ", image[i][j] > 0 ? '0' : ' ');
            printf("\n");
        }
        printf("\n");
    }
};