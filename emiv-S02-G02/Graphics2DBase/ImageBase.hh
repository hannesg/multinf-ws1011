/*
 * ImageBase
 * @author fkellner, 10/10
 */

#ifndef IMAGEBASE_HH_
#define IMAGEBASE_HH_

#include <string>
#include <iostream>

// our library will live in Graphics2D name space
namespace Graphics2D {

  class ImageBase {
    public:

      // each image has a color model, defaults to rgb
      enum ColorModel {
        cm_RGB=0,
        cm_HSV,
        cm_Grey
      };
      
      /**
       * constructor, creates empty image
       */
      ImageBase();
      
      /**
       * constructor, copies image from other instance
       */
      ImageBase(const ImageBase &other);
      
      /**
       * = operator, copies image from other instance
       * use ImageBase a = b;
       */
      ImageBase& operator=(const ImageBase &other);

      /**
       * destructor, releases memory
       */
      virtual ~ImageBase();
      
      /**
       * @brief Initialize image size and channels
       *
       * @param width  image width  of new image
       * @param height image height of new image
       *
       */
      void Init(unsigned int width, unsigned int height);
      
      /**
       * @brief checks if image is initialized
       * @return true if image is initialized
       */
      bool Valid();
      
      /**
       * @brief set every pixel in image to r=g=b=0, black
       *
       * implement in subclass
       */
      virtual void FillZero() = 0;
      
      /**
       * @brief get value of a specific pixel's color channel
       * @param x x-coordinate of pixel
       * @param y y-coordinate of pixel
       * @param ch color channel, 0,1 or 2 for r,g or b
       *
       * implement in subclass
       */
      virtual inline unsigned char GetPixel(const int &x, const int &y, const int &ch) const = 0;
      
      /**
       * @brief set value of a specific pixel's color channel
       * @param x x-coordinate of pixel
       * @param y y-coordinate of pixel
       * @param ch color channel, 0,1 or 2 for r,g or b
       * @param value color channel value to be set
       *
       * implement in subclass
       */
      virtual inline void SetPixel(const int &x, const int &y, const int &ch, const unsigned char &value) = 0;

      /**
       * @brief load image from *.ppm file and set data, width, height
       * can read P3 and P6 format
       *
       * implement in subclass
       */
      virtual int LoadPPM(const std::string &filename) = 0;

      /**
       * @brief save image to *.ppm file in P6 format
       *
       * implement in subclass
       */
      virtual int SavePPM(const std::string &filename) = 0;

      /**
       * @brief get pointer of image data
       *
       * A pixel can be accessed  by
       * GetData()[row * getHeight() + col * Channelcount + Channel]
       * (ChannelCount is 3)
       *
       * @return pointer to first pixel of image
       */
      inline unsigned char *GetData() { return data_; }

      /**
       * @brief get image width
       * @return image width
       */
      inline unsigned int GetWidth() const { return width_; }

      /**
       * @brief get image height
       * @return image height
       */
      inline unsigned int GetHeight() const { return height_; }

      /**
       * @brief get color model
       * @return ColorModel
       */
      inline ColorModel GetColorModel() const { return colormodel_; }
      /**
       * @brief Set color model
       * @param colormodel to set, will not modify data
       */
      inline void SetColorModel(ColorModel colormodel) { colormodel_ = colormodel; }

    protected:
      
      unsigned int width_, height_;
      ColorModel colormodel_;
      unsigned char *data_;

  };

}

#endif /* IMAGEBASE_HH_ */
