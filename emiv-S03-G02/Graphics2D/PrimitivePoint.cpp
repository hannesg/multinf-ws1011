

#include "PrimitivePoint.hh"

namespace Graphics2D {

/* void PrimitivePoint::SetCoordinate(vector<Coordinate> c) 
{
	if(c.size() != 1) {
		throw exception();
	}
	coor_ = c;
} */

void PrimitivePoint::Draw(ImageBase *img) {
	
	Coordinate c = coor_.first();
	img->SetPixel(c.GetX(), c.GetY(), 0, color_.GetR());
	img->SetPixel(c.GetX(), c.GetY(), 1, color_.GetG());
	img->SetPixel(c.GetX(), c.GetY(), 2, color_.GetB());
}


} 
