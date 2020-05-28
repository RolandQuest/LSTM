#include "mnist.h"

#include <fstream>
#include <iostream>

namespace ml
{

  bool mnist::_isLoaded = false;
  tensor mnist::_imagesTest;
  tensor mnist::_labelsTest;
  tensor mnist::_imagesTrain;
  tensor mnist::_labelsTrain;

  void mnist::loadData() {

    idx_file itest( "examples/mnist/t10k-images.idx3-ubyte" );
    _imagesTest = convertToTensor(itest);





    _isLoaded = true;
  }

  tensor mnist::convertToTensor( idx_file& file ) {




    void* data = file.data();





    return tensor();

  }

  void mnist::freeData() {

    _imagesTest = tensor();
    _imagesTrain = tensor();
    _labelsTest = tensor();
    _labelsTrain = tensor();
    _isLoaded = false;
  }

  tensor& mnist::getTestImages() {
    return _imagesTest;
  }

  tensor& mnist::getTestLabels() {
    return _labelsTest;
  }

}
