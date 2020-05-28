#ifndef MNIST_H
#define MNIST_H

#include "../../math/tensor.h"
#include "../idx_file.h"

namespace ml
{
  class mnist
  {

  private:

    static bool _isLoaded;

    static tensor _imagesTest;
    static tensor _imagesTrain;
    static tensor _labelsTest;
    static tensor _labelsTrain;
    
    static tensor convertToTensor( idx_file& file );

  public:

    static void loadData();
    static void freeData();

    static tensor& getTestImages();
    static tensor& getTestLabels();

  };
}

#endif