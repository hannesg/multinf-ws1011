/*
Gruppe: 02
Serie 03
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <cassert>
#include "PrimitivePoint.hh"

using namespace std;

namespace Graphics2D {

void PrimitivePoint::SetCoordinate(const Coordinate &coor) 
{
	/* delete previous point */
	points_.pop_back();
	/* add new point */
	points_.push_back(coor);

	assert(points_.size() == 1);
}

void PrimitivePoint::Draw(ImageBase *img) const {
	
	Coordinate c = points_.front();
	int x = c.GetX();
	int y = c.GetY();

	if(x >= 0 && y >= 0 && x < img->GetWidth() && y < img->GetHeight()) {
		img->SetPixel(x, y, 0, color_.GetR());
		img->SetPixel(x, y, 1, color_.GetG());
		img->SetPixel(x, y, 2, color_.GetB());
	}
}

void PrimitivePoint::Init(const Coordinate &coor, const Color &c)
{
	color_ = c;
	points_.push_back(coor);
}

ostream& operator<<(ostream& os, const PrimitivePoint &p)
{
    os << "(" << p.GetX() << ", " << p.GetY() << ")";
    return os;
}



} 
