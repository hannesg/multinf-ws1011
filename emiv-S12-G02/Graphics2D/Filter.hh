 /*
Gruppe: 02
Serie 07
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef __FILTER_HH
#define __FILTER_HH

#include <vector>	
#include "Image.hh"
#include "FloatImage.hh"

namespace Graphics2D {

class Filter
{
public:
	// execute filter on image
	void FilterImage(const Image &src, Image &dst) const;
	
	// returns the corresponding filter
	static Filter *CreateMean(int width, int height);
	static Filter *CreateBinomial(int width);

	// Filter zum Testen (laesst das Bild unveraendert)
	static Filter *CreateIdentity(int width, int height);
	
	// Gradientfilter in x-Richtung
	static Filter *CreateGradX();

	// Gradientenfilter in y-Richtung
	static Filter *CreateGradY();

	static Filter *CreateLaplace();

	// Rekursiven Mittelwert berechnen
	static void MeanRecursive(const Image &src, Image &dst, unsigned int width, unsigned int height);
	
	// Rankfilter
	static void Rank3x3(const Image &src, Image &dst, int rank);

	// Rankfilter
	static void FilterGradMag(const Image &src, Image &dst);

	// debugging function
	void printFilter() const;
	
	/**
	* Filtering a Greyscale Image to a one-channel FloatImage
	* It is not necessary to shift, scale or discretize the result, so it is often better suited for image processing.
	* 
	* Usage example:
	* Image rgbImage, greyImage;
	* FloatImage gx;
	* 
	* rgbImage.LoadPPM("myholidaypic.ppm");
	* ColorConversion::ToGrey(rgbImage, greyImage);
	* 
	* Filter *filterGradX = Filter::CreateGradX();
	* filterGradX->FilterImage(greyImage, gx);
	* delete filterGradX;
	* gx.GetAsGreyImage(greyImage);
	* greyImage.SavePPM("myholidaypic-gradX.ppm");
	* 
	* @param src Input image, will be scaled from [0..255] to [0.0f..1.0f]!
	* @param dst float valued output image (any range!)
	*/
	void FilterImage(const Image& src, FloatImage &dst);
	
	/**
	* Filtering from FloatImage to FloatImage
	* @param src input image
	* @param dst output image
	*/
	void FilterImage(const FloatImage& src, FloatImage &dst);
	
	static void NonMaximumSuppression(const FloatImage &src, FloatImage &dst, float threshold, int size=21);
	
protected:
	Filter(const vector<vector <int> > & mask, int scale);
	
	
	
	
private:
	// the sum of all values in the filter
	int sum_;

	// width and height of the filter
	unsigned int width_;
	unsigned int height_;
	
	// the scale factor
	int scale_;
	int offset_;
	
	/// half mask width
    int hmw_;
    /// half mask height
    int hmh_;

	// the filter mask
	vector <vector<int> > mask_;
	
};
}

#endif
