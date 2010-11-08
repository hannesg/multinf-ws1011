

#include <cassert>
#include "PrimitivePoint.hh"

using namespace std;

namespace Graphics2D {

void PrimitivePoint::SetCoordinate(Coordinate coor) 
{
	/* delete previous point */
	points_.pop_back();
	/* add new point */
	points_.push_back(coor);

	assert(points_.size() == 1);
}

void PrimitivePoint::Draw(ImageBase *img) const {
	
	Coordinate c = points_.front();
	img->SetPixel(c.GetX(), c.GetY(), 0, color_.GetR());
	img->SetPixel(c.GetX(), c.GetY(), 1, color_.GetG());
	img->SetPixel(c.GetX(), c.GetY(), 2, color_.GetB());
}

void PrimitivePoint::Init(Coordinate coor, Color c)
{
	color_ = c;
	points_.push_back(coor);
}

} 
