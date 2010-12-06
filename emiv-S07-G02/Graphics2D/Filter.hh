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

	// debugging function
	void printFilter() const;
	
protected:
	Filter(const vector<vector <int> > & mask);
	
	
	
	
private:
	// the sum of all values in the filter
	int sum_;

	// width and height of the filter
	unsigned int width_;
	unsigned int height_;

	// the filter mask
	vector <vector<int> > mask_;
	
};
}

#endif
