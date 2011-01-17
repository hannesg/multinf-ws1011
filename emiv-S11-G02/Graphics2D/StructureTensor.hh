#ifndef STRUCTURETENSOR_HH_
#define STRUCTURETENSOR_HH_

#include <Graphics2D/Image.hh>
#include <Graphics2DBase/FloatImage.hh>
#include <Graphics2D/Filter.hh>

namespace Graphics2D {

  class StructureTensor {
      
    public:
      
      /**
       * the constructor initializes all internal filters
       * @param filterSize size of binomial filter
       */
      StructureTensor(int filterSize=7);
      
      /**
       * deletes all internal filters
       */
      virtual ~StructureTensor();
      
      /**
       * stores derivatives of image "input" in gx_, gy_, elements of Structure Tensor J in gxx_, gxy and gyy
       */
      void SetFromImage(const Image &input);

      /**
       * calculates foerstner operator on each pixel with trace(j)>thres
       * @param thres threshold on trace
       * @param corners image on which result is drawn. red pixels will indicate corners, green pixels indicate edges 
       */
      void FoerstnerDetector(float thres, Image &corners);
      
      /**
       * calculates Harris Corner Detector on each pixel.
       * After thresholding the corner strength, non-maximum suppression yields single interest points
       * @param thres threshold on corner strength
       * @param corners image on which result is drawn. blue pixels indicate Harris Corners 
       */
      void HarrisCornerDetector(float thres, Image &corners);
      
    private:

      /// storage for the different derivates
      /// read documentation of FloatImage
      FloatImage gx_, gy_, gxx_, gxy_, gyy_;
      
      /// read documentation of Filter::FilterImage(Image, FloatImage) and Filter::FilterImage(FloatImage, FloatImage)
      Filter *filterGx_, *filterGy_, *filterBinomial_;
      
      /// half window size of binomial filter used 
      int halfwinSize_;
      
      // the result
      FloatImage Jxx_, Jxy_, Jyy_;
  };

}

#endif /* STRUCTURETENSOR_HH_ */
