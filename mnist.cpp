#include "NN.h"
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

// Vector<> image(mnist_set mnist)
// {
//     Vector<> v = Vector(784);
//     int k = 0;
//     for (int i = 0; i < 28; i++)
//         for (int j = 0; j < 28; j++)
//             v[k++] = mnist.image[i][j];
//     return v;
// }

// Vector label(mnist_set mnist)
// {
//     Vector o = Vector(10);
//     o.assign(0);
//     o[mnist.label] = 1;
//     return o;
// }

// Set set(mnist_set mnist)
// {
//     return Set(image(mnist), label(mnist));
// }

int main()
{
    FILE *img = fopen("training/train-images.idx3-ubyte", "rb");
    FILE *labels = fopen("training/train-labels.idx1-ubyte", "rb");
    Seek(img, labels);

    mnist_set mnist=mnist_set();
    mnist.LoadNext(img,labels);
    mnist.star();

    // NN nn = NN(784, {16, 16}, 10);
    // nn.activation_function.function = Tanh;
    // nn.activation_function.derivative = dTanh;
    // nn.setLearningRate(0.05);
    // mnist_set mnist;

    // for (int k = 0; k < 100; k++)
    // {
    //     for (int i = 0; i < 10; i++)
    //     {
    //         mnist.LoadNext(img, labels);
    //         nn.train(set(mnist));
    //     }
    //     Seek(img,labels);
    // }

    // Seek(img, labels);
    // for (int i = 0; i < 10; i++)
    // {
    //     mnist.LoadNext(img, labels);
    //     std::cout << "NN predicted " << nn.predict(image(mnist)) << " and the output was: " << label(mnist) << "\n\n";
    // }
}