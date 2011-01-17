#ifndef FLOATIMAGE_HH_
#define FLOATIMAGE_HH_
#include <Graphics2DBase/ImageBase.hh>

namespace Graphics2D {

  /**
   * A FloatImage is a 1-channel image of floats.
   * Usage is the same as Image, except Get/SetPixel functions do not have a channel parameter.
   * FloatImages can not be saved directly to disc. See GetAsGreyImage.
   */
  class FloatImage {
    public:
      
      /// creates empty image
      FloatImage();
      /// copies image from other instance
      FloatImage(const FloatImage &other);
      /// copies image from other instance
      FloatImage& operator=(const FloatImage &other);

      /// deletes the image
      virtual ~FloatImage();
      
      /// creates memory for a width*height 3 channel image
      void Init(unsigned int width, unsigned int height);
      
      /// returns true if image is inited
      bool Valid() const;
      
      /// sets every pixel to black ( rgb(0,0,0) ), must be implemented by child 
      virtual void FillZero();
      
      virtual inline float GetPixel(const int &x, const int &y) const {
        return data_[y*width_+x];
      }
      
      virtual inline void SetPixel(const int &x, const int &y, const float &value) {
        data_[y*width_+x] = value;
      }
      
      /**
       * Scales the FloatImage to [0..255] and stores it as a greyscale Image.
       * This image can then be saved to disc by Image::SavePPM.
       * @param target where to store the greyscale representation.
       */
      void GetAsGreyImage(ImageBase &target);

      /// get pointer to data
      inline float *GetData() { return data_; }
      inline float *GetData() const { return data_; }
      /// get image width
      inline unsigned int GetWidth() const { return width_; }
      /// get image height
      inline unsigned int GetHeight() const { return height_; }

    protected:
      
      unsigned int width_, height_;
      float *data_;
  };

}

#endif /* FLOATIMAGE_HH_ */
