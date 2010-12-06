 
#ifndef __FILTER_HH
#define __FILTER_HH

#include <vector>	
#include "Image.hh"

namespace Graphics2D {

class Filter
{
public:
	void FilterImage(const Image &src, Image &dst) const;
	
	static Filter *CreateMean(int width, int height);

	// Filter zum Testen
	static Filter *CreateIdentity(int width, int height);

	// debugging function
	void printFilter() const;
	
protected:
	Filter(const vector<vector <int> > & mask);
	
	
	
	
private:
	int sum_;
	unsigned int width_;
	unsigned int height_;
	vector <vector<int> > mask_;
	
};
}

#endif
