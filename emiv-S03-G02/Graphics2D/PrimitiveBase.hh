#ifndef __PRIMITIVE_BASE
#define __PRIMITIVE_BASE

#include <vector>
#include "ImageBase.hh"
#include "Color.hh"
#include "Coordinate.hh"

using namespace std;

namespace Graphics2D {

class PrimitiveBase {
	
public:	
	PrimitiveBase() : num_points_(-1) { }
	Color GetColor() const { return color_; }
	void SetColor(Color c) { color_ = c; }
	
	vector<Coordinate> GetCoordinates() { return coor_; }
	virtual void SetCoordinates(vector<Coordinate> cs);
		
	virtual void Draw(ImageBase *im) const = 0;
	
protected:
	vector<Coordinate> coor_;
	Color color_;
	const int num_points_;
};

}

#endif
 
