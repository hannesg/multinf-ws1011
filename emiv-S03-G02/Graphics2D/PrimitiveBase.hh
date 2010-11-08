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
	/* get and set colors */
	Color GetColor() const { return color_; }
	void SetColor(Color c) { color_ = c; }
	
	/* get and set coordinates. Attention: SetCoordinates is virtual, 
	 * because it might be overwritten by subclasses */
	vector<Coordinate> GetCoordinates() const { return points_; }
	virtual void SetCoordinates(const vector<Coordinate> &points);
		
	/* Draws the primitive into the image */
	virtual void Draw(ImageBase *im) const = 0;
	
protected:
	/* coordinates */
	vector<Coordinate> points_;
	/* color */
	Color color_;

	/* constant that showes, that every number of points is allowed */
	static const int ANY_NUMBER_ALLOWED = -1;

	/* virtual function that returns the allowed number of points
	 * that can be given to "SetCoordinates()". Must be overwritten
	 * by every subclass that needs to specify how many points are 
	 * allowed (Points, Lines, ...). If it is not implemented in a 
	 * subclass, no check occurs, because in this case, the followig
	 * function is called, which returns ANY_NUMBER_ALLOWED. */
	virtual int GetNumberOfPointsAllowed() const { return ANY_NUMBER_ALLOWED; }

};

}

#endif
 
