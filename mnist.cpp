#include "NN.h"
#include "mnist.h"

void Seek(FILE *img, FILE *labels)
{
    fseek(img, 16, SEEK_SET);
    fseek(labels, 8, SEEK_SET);
}

void print_at_index(int i, FILE *img, FILE *labels)
{
    fseek(img, 784 * i, SEEK_CUR);
    fseek(labels, i, SEEK_CUR);
    mnist_module m;
    m.LoadNext(img, labels);
    m.star();
}

Vector<> input_vector(mnist_module mnist)
{
    Vector<> v = Vector<>(784);
    int k = 0;
    for (int i = 0; i < 28; i++)
        for (int j = 0; j < 28; j++)
            v[k++] = mnist.image[i][j];
    return v;
}

Vector<> output_vector(mnist_module mnist)
{
    Vector<> o = Vector<>(10);
    o.assign((float)0);
    o[mnist.label] = 1;
    return o;
}

int main()
{
    //setting up the neural network
    // NN nn=NN(784,{16,16,16,16},10);
    // nn.activation_function.function = Tanh;
    // nn.activation_function.derivative = dTanh;
    // nn.setLearningRate(0.05);

    FILE* save_file=fopen("MNIST_Tanh.nn","rb+");
    NN nn=NN::Load(save_file);

    //set up the file initialization
    FILE *img = fopen("training/train-images.idx3-ubyte", "rb");
    FILE *labels = fopen("training/train-labels.idx1-ubyte", "rb");
    Seek(img, labels);

    //setting up the images and labels
    mnist_module mnist=mnist_module();
    mnist.LoadNext(img,labels);

    //training the neural network on the entire mnist dataset
    // for(int i=0;i<=10000;i++)
    // {
    //     nn.train(Set(input_vector(mnist),output_vector(mnist)));
    //     mnist.LoadNext(img,labels);
    //     if(i%100==0)
    //         printf("%i\n",i);
    // }

    //prediction part
    for(int i=0;i<10;i++)
    {
        Vector<> prediction=nn.predict(input_vector(mnist));

        printf("Label was %i but the neural network predicted: ",mnist.label);
        std::cout<<prediction;
        mnist.star();
        printf("\n");

        mnist.LoadNext(img,labels);
    }

    //saving the neural network to a file
    nn.Save(save_file);

    printf("The End!");
}