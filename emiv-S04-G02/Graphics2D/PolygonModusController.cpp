/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#include <cassert>
#include <cstdlib>
#include "PolygonModusController.hh"
#include "Painter.hh"
#include "PrimitiveLine.hh"

using namespace std;

namespace Graphics2D {

void PolygonModusController::Activate() {

	points_.clear();
}

void PolygonModusController::Deactivate() {
	// Aufrauemen (loescht auch automatisch die hier in der Klasse
	// erzeugten Zeiger)! 
	RemoveAllTemporaryPrimitives();

	points_.clear();
}

void PolygonModusController::MouseDown(int x, int y) {
	// nichts tun
}

void PolygonModusController::MouseUp(int x, int y)  {

	if(IsCloseToStartingPoint(Coordinate(x, y))) {
		// Polygon schliessen und erstellen

		points_.push_back(points_[0]);

		// Darauf achten, dass auch wirklich ein Polygon gezeichnet wurde! 
		if(points_.size() >= 3) {
			// TODO!  Auskommentieren wenn PrimitivePolygon-Klasse erstellt
			// PrimitivePolygon p = new PrimitivePolygon();

			// p.SetCoordinates(points_);
			// p.SetColor(myPainter_.GetCurrentColor());

			// myPainter_.AddPrimitive(p);
		}

		RemoveAllTemporaryPrimitives();
		points_.clear();
	}
	else {
		// Punkt hinzunehmen
		points_.push_back(Coordinate(x, y));

		// Neue Linie erstellen
		PrimitiveLine * line = new PrimitiveLine(x, y, x, y, myPainter_.GetCurrentColor());

		tempPrimitives_.push_back(line);
	}

	
}

bool PolygonModusController::IsCloseToStartingPoint(const Coordinate &c) const {

	if(points_.size() == 0) {
		// Kein Startpunkt vorhanden
		return false;
	} else {
		Coordinate sp = points_.front();

		return ( abs(c.GetX()-sp.GetX()) < delta)
			&& (abs(c.GetY()-sp.GetY()) < delta);
	}
}

void PolygonModusController::MouseMove(int x, int y)  {

	if(points_.size() > 0) {

		PrimitiveLine *currentLine = dynamic_cast<PrimitiveLine *>(tempPrimitives_.back());

		assert(currentLine != NULL);

		currentLine->SetEndingPoint(x, y);

	}
}

}
