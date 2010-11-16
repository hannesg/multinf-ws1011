/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#include <cassert>
#include "PointModusController.hh"
#include "Painter.hh"
#include "PrimitivePoint.hh"

using namespace std;

namespace Graphics2D {

void PointModusController::Activate() {

	pressed_ = false;
}

void PointModusController::Deactivate() {
	// Aufrauemen (loescht auch automatisch die hier in der Klasse
	// erzeugten Zeiger)! 
	RemoveAllTemporaryPrimitives();

	pressed_ = false;
}

void PointModusController::MouseDown(int x, int y) {

	pressed_ = true;

	// Temporaeren Punkt erzeugen
	tempPrimitives_.push_back(new PrimitivePoint(x, y, myPainter_.GetCurrentColor()));
}

void PointModusController::MouseUp(int x, int y)  {

	if(pressed_) {
		pressed_ = false;

		// Den Punkt endgueltig hinzufuegen
		myPainter_.AddPrimitive(new PrimitivePoint(x, y, myPainter_.GetCurrentColor()));

		// Temporaere Objekte loeschen
		RemoveAllTemporaryPrimitives();
	}
}

void PointModusController::MouseMove(int x, int y)  {

	// Den temporaeren Punkt verschieben
	if(pressed_) {

		if(tempPrimitives_.size() == 0) {
			// Punkt hinzugfuegen, falls nicht vorhanden
			tempPrimitives_.push_back(new PrimitivePoint(x, y, myPainter_.GetCurrentColor()));
		}
		
		PrimitivePoint *thePoint = dynamic_cast<PrimitivePoint *>(tempPrimitives_.front());
		assert(thePoint != NULL);

		// neue Koordinaten setzen
		thePoint->SetCoordinate(x, y);
	}

}

}