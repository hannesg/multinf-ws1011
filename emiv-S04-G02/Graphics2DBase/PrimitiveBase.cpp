
#include "PrimitiveBase.hh"

namespace Graphics2D {

void PrimitiveBase::SetCoordinates(const vector<Coordinate> &points) {
	/* ermittele die Anzahl der erlaubten Punkte. Nutzt Polymorphie aus: 
	 * die richtige Funktion der möglichen Subklassen wird automatisch 
	 * aufgerufen. */
	int num_of_points_allowed = this->GetNumberOfPointsAllowed();

	/* if checking enabled (num_of_points_allowed != ANY_NUMBER_ALLOWED) and 
	 * argument points has not the expected size -> Error!
	 */
	if(num_of_points_allowed != ANY_NUMBER_ALLOWED && points.size() != (unsigned)num_of_points_allowed) {
		throw exception();
	}

	points_ = points;
}

}
