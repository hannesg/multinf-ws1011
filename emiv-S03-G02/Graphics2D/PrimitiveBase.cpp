
#include "PrimitiveBase.hh"

namespace Graphics2D {

void PrimitiveBase::SetCoordinates(vector<Coordinate> cs) {
	if(cs.size() != num_points_) {
		throw exception();
	}
	coor_ = cs;
}

}
