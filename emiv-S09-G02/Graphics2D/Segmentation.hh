#ifndef SEGMENTATION_HH_
#define SEGMENTATION_HH_

#include <vector>

#include <Graphics2D/Image.hh>
#include <Graphics2D/Coordinate.hh>
#include <Graphics2D/Color.hh>

namespace Graphics2D {

  /** 
   * Segmentation class interface, fkellner 12/10
   */
  class Segmentation {
    public:
      /**
       * if input image is rgb:
       * constructor stores the image in a hsv representation (color conversion)
       * initializes internal label image with zeros
       *
       * if input image is hsv:
       * constructor stores the hsv image
       * initializes internal label image with zeros
       * 
       * if input image is grey:
       * consider input image as label image
       * 
       * needed for task 9.1
       */
      Segmentation(const Image &inputImage);

      /**
       * delete dynamic memory if needed
       *
       * needed for task 9.1
       */
      virtual ~Segmentation();
      
      /**
       * add pixels with minHue <= hue <= maxHue with label "label" to the label image
       * (only works if hsv image is present! consider hue wrap around)
       * 
       * needed for task 9.1
       * 
       * @param label label for found pixels
       * @param minHue minimum hue of pixel
       * @param maxHue maximum hue of pixel
       * @param minSat minimum saturation of pixel
       */
      void AddHueSegment(const int label, const int minHue, const int maxHue, const int minSat=128);
      
      /**
       * perform one step closing operation on label image
       *
       * needed for task 9.1
       */
      void ClosingOperation();

      /**
       * return label image in labelImage
       * 
       * needed for task 9.1
       */
      void GetLabelImage(Image &labelImage);
      
      /**
       * compute center of mass and area of object with label "label"
       * @param label label of object
       * @param center center of mass is stored here 
       * @param area area of object is stored here
       * @return 0 on success, 1 if no such label exists
       */
      int GetCenterAndArea(const int label, Coordinate &center, int &area);
      
      /**
       * compute freeman code of object with label "label" with Pavlidis' Algorithm
       * @param label label of object
       * @param firstPoint Coordinate of first encountered object pixel 
       * @param freemanCode result vector containing freeman code
       * @return 0 on success, 1 if no such label exists
       */
      int GetFreemanCode(const int label, Coordinate &firstPoint, std::vector<int> &freemanCode);
      
      /**
       * starting at coordinate firstpoint, freeman code is unrolled to actual pixel coordinates and drawn
       * with the given color. targetImage should be RGB.
       * @param firstPoint see GetFreemanCode
       * @param freemanCode see GetFreemanCode
       * @param color color to draw the contour in
       * @param targetImage where to draw the contour
       */
      void DrawContourFreeman(const Coordinate firstPoint, const std::vector<int> &freemanCode, 
          const Color color, Image &targetImage);
      
      /*
       * Add more functions as you need them.
       * Consider making functions private if you intent to use them only internally. 
       */
      
    private:

      /// store hsv representation of input image here
      Image hsvImage_;
      /// use this image to do the labeling
      Image labelImage_;
      
      // add more variables as you need them
  };

}

#endif /* SEGMENTATION_HH_ */
