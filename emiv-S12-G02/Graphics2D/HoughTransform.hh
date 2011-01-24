
#ifndef HOUGHTRANSFORM_HH_
#define HOUGHTRANSFORM_HH_
#include <vector>
#include <Graphics2DBase/FloatImage.hh>
#include <Graphics2D/Image.hh>
#include <Graphics2D/PrimitiveLine.hh>
#include <Graphics2D/StructureTensor.hh>

namespace Graphics2D {

  /**
   * Detector for lines in images
   */
  class HoughTransform {
    public:
      HoughTransform();
      virtual ~HoughTransform();
      
      /**
       * Hough Transform of grey image
       * @param input grey input image
       * @param resolution angular resolution for 2d histogram per degree. resolution=2 means two bins per degree.
       * @param lines a vector of lines in 2-point parametrization from one image border to another
       */
      void StandardHoughTransform(const Image &input, const int resolution, std::vector<PrimitiveLine> &lines);

      /**
       * Fast Hough Transform of grey image from structure tensor
       * @param input already calculated structure tensor
       * @param resolution angular resolution for 2d histogram per degree. resolution=2 means two bins per degree.
       * @param lines a vector of lines in 2-point parametrization from one image border to another
       */
      void FastHoughTransform(const StructureTensor &input, const int resolution, std::vector<PrimitiveLine> &lines);
      
    protected:
      
      /**
       * create two dimensional hough space from input image. result is stored in FloatImage houghspace_
       * @param input grey input image
       * @param resolution angular resolution for 2d histogram per degree. resolution=2 means two bins per degree.
       */
      void Create2DHistogram_(const Image &input, const int resolution);

      /**
       * create two dimensional hough space from input structure tensor. result is stored in FloatImage houghspace_
       * @param input already calculated structure tensor
       * @param resolution angular resolution for 2d histogram per degree. resolution=2 means two bins per degree.
       */
      void Create2DHistogramFromStructureTensor_(const StructureTensor &input, const int resolution);
      
      /**
       * both hough methods use this to extract lines from hough space. lines are defined by their intersection with the image borders
       * @param imWidth right image border
       * @param imHeight bottom image border
       * @param lines a vector of lines
       */
      void GetLines_(int imWidth, int imHeight, std::vector<PrimitiveLine> &lines);
      
      /// image representation of 2d hough histogram
      FloatImage houghspace_;
  };

}

#endif /* HOUGHTRANSFORM_HH_ */
