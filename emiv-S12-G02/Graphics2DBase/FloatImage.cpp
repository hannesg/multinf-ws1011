#include <Graphics2DBase/FloatImage.hh>
#include <iostream>
#include <cstring>

using namespace std;

namespace Graphics2D {

  FloatImage::FloatImage() {
    // initialize variables as zero
    width_ = 0;
    height_ = 0;
    data_ = NULL;
  }
  
  FloatImage::FloatImage(const FloatImage &other) {
    // copy everything from other image
    width_ = other.width_;
    height_ = other.height_;
    data_ = new float[width_*height_];
    memcpy(data_, other.data_, width_*height_*sizeof(float));
  }

  FloatImage& FloatImage::operator=(const FloatImage &other) {
    // check if call is like a=a, which means do nothing
    if (this != &other) {
      if (Valid()) {
        if (other.width_ != width_ || other.height_ != height_) {
          delete[] data_;
          data_ = NULL;
        }
      }
      width_ = other.width_;
      height_ = other.height_;
      if (!Valid())
        data_ = new float[width_*height_];
      memcpy(data_, other.data_, width_*height_*sizeof(float));
    }
    return *this;
  }

  FloatImage::~FloatImage() {
    // if data is allocated, delete it
    if (Valid()) {
      delete[] data_;
      data_ = NULL;
    }
  }

  bool FloatImage::Valid() const {
    return data_ != NULL;
  }
  
  void FloatImage::FillZero() {
    if (Valid())
      memset(data_, 0, width_*height_*sizeof(float));
  }
  
  void FloatImage::Init(unsigned int width, unsigned int height) {
    // only (re-)allocate data if neccessary
    if (Valid()) {
      if (width != width_ || height != height_) {
        delete[] data_;
        data_ = new float[width*height];
      }
    } else {
      data_ = new float[width*height];
    }
    width_ = width;
    height_ = height;
  }
  
  
  void FloatImage::GetAsGreyImage(ImageBase &target) {
    if (!Valid()) return;
    float minVal = data_[0];
    float maxVal = data_[0];
    for (unsigned int i=1;i<width_*height_;i++) {
      if (data_[i]<minVal) minVal = data_[i];
      if (data_[i]>maxVal) maxVal = data_[i];
//      if (data_[i]>1000) cout << "at:" << i << endl;
    }
    cout << "Scaling between " << minVal << " and " << maxVal << endl;
    target.Init(width_, height_);
    unsigned char *tdata = target.GetData();
    target.SetColorModel(ImageBase::cm_Grey);
    for (unsigned int i=0;i<width_*height_;i++) {
      unsigned char val = (unsigned char)((data_[i]-minVal)*(255.0f/(maxVal-minVal)));
      tdata[i*3+0] = val;
      tdata[i*3+1] = val;
      tdata[i*3+2] = val;
    }
  }

}
