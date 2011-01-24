#include <Graphics2D/HoughTransform.hh>

using namespace std;

namespace Graphics2D {

  HoughTransform::HoughTransform() {
    // nothing
  }

  HoughTransform::~HoughTransform() {
    // nothing
  }

  
  void HoughTransform::StandardHoughTransform(const Image &input, const int resolution, vector<PrimitiveLine> &lines) {
    // call Create2DHistogram_
    // apply non maximum suppression
    // save houghimage for debugging (optional)
    // call GetLines_
  }

  void HoughTransform::FastHoughTransform(const StructureTensor &input, const int resolution, vector<PrimitiveLine> &lines) {
    // call Create2DHistogramFromStructureTensor_
    // apply non maximum suppression
    // save hough image for debugging (optional)
    // call GetLines_ (extend StructureTensor class for getting width and height)
  }

  // ---- protected
  
  void HoughTransform::Create2DHistogram_(const Image &input, const int resolution) {
    // calculate hough transform
    // for all pixels with magnitude of gradients > 100 (fixed threshold)
    // consider needed size for 2d histogram!
    // save hough image for debugging
  }
  
  void HoughTransform::Create2DHistogramFromStructureTensor_(const StructureTensor &input, const int resolution) {
    // get elements of structure tensor  (extend StructureTensor class for getting Jxx, Jxy, Jyy)
    // calculate hough transform using structure tensor orientation
    // consider needed size for 2d histogram!
    // save hough image for debugging
  }

  
  void HoughTransform::GetLines_(int imWidth, int imHeight, std::vector<PrimitiveLine> &lines) {
    // for each pixel != 0 in hough space
    // calculate a line from one image border to another
    // by calculating the intersection points with the image borders
    // consider vertical/horizontal lines, you might need to consider different cases
  }
}
