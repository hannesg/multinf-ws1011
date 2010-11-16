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
	myPainter_.RemoveAllTemporaryPrimitives();
}

void PointModusController::MouseDown(int x, int y) {

	pressed_ = true;

	// Temporaeren Punkt erzeugen
	myPainter_.AddTemporaryPrimitive(new PrimitivePoint(x, y, myPainter_.GetCurrentColor()));
}

void PointModusController::MouseUp(int x, int y)  {

	if(pressed_) {
		pressed_ = false;

		// Den Punkt endgueltig hinzufuegen
		myPainter_.AddPrimitive(new PrimitivePoint(x, y, myPainter_.GetCurrentColor()));

		// Temporaere Objekte loeschen
		myPainter_.RemoveAllTemporaryPrimitives();
	}
}

void PointModusController::MouseMove(int x, int y)  {

	// Den temporaeren Punkt verschieben
	if(pressed_) {
		/* TODO: was wenn GetTemporaryPrimitive(0) nicht existiert */
		PrimitivePoint *thePoint = dynamic_cast<PrimitivePoint *>(myPainter_.GetTemporaryPrimitive(0));
		assert(thePoint != NULL);

		thePoint->SetCoordinate(x, y);
	}

}

}