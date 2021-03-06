/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#include <cassert>
#include "LineModusController.hh"
#include "Painter.hh"
#include "PrimitiveLine.hh"

using namespace std;

namespace Graphics2D {

void LineModusController::Activate() {

	pressed_ = false;
}

void LineModusController::Deactivate() {
	// Aufrauemen (loescht auch automatisch die hier in der Klasse
	// erzeugten Zeiger)! 
	RemoveAllTemporaryPrimitives();

	pressed_ = false;
}

void LineModusController::MouseDown(int x, int y) {

	pressed_ = true;

	// Startpunkt merken
	startingPoint_.Set(x, y);

	// Temporaere Linie erzeugen
	tempPrimitives_.push_back(new PrimitiveLine(startingPoint_, startingPoint_, myPainter_.GetCurrentColor()));
}

void LineModusController::MouseUp(int x, int y)  {

	if(pressed_) {
		pressed_ = false;

		// Die Linie endgueltig hinzufuegen
		myPainter_.AddPrimitive(new PrimitiveLine(startingPoint_, Coordinate(x, y), myPainter_.GetCurrentColor()));

		// Temporaere Objekte loeschen
		RemoveAllTemporaryPrimitives();
	}
}

void LineModusController::MouseMove(int x, int y)  {

	// Die temporaere Linie verschieben
	if(pressed_ && tempPrimitives_.size() != 0) {

		PrimitiveLine *theLine = dynamic_cast<PrimitiveLine *>(tempPrimitives_.front());
		assert(theLine != NULL);

		theLine->SetEndingPoint(x, y);
	}

}

}
