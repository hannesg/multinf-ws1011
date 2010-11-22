/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#include <cassert>
#include "StarModusController.hh"
#include "Painter.hh"
#include "PrimitiveStar.hh"

using namespace std;

namespace Graphics2D {

void StarModusController::Activate() {

	pressed_ = false;
}

void StarModusController::Deactivate() {
	// Aufrauemen (loescht auch automatisch die hier in der Klasse
	// erzeugten Zeiger)! 
	RemoveAllTemporaryPrimitives();

	pressed_ = false;
}

void StarModusController::MouseDown(int x, int y) {

	pressed_ = true;

	// Startpunkt merken
	startingPoint_.Set(x, y);

	PrimitiveStar *theStar = new PrimitiveStar(startingPoint_, 0, 0);
	theStar->SetColor(myPainter_.GetCurrentColor());

	// Temporaeren Stern erzeugen
	tempPrimitives_.push_back(theStar);
}

void StarModusController::MouseUp(int x, int y)  {

	if(pressed_) {
		pressed_ = false;

		// Den Stern endgueltig hinzufuegen
		float radius = getRadius(x, y);

		PrimitiveStar *theStar = new PrimitiveStar(startingPoint_, radius/2, radius);
		theStar->SetColor(myPainter_.GetCurrentColor());

		myPainter_.AddPrimitive(theStar);

		// Temporaere Objekte loeschen
		RemoveAllTemporaryPrimitives();
	}
}

void StarModusController::MouseMove(int x, int y)  {

	// Den temporaeren Stern verschieben
	if(pressed_ && tempPrimitives_.size() != 0) {

		PrimitiveStar *theStar = dynamic_cast<PrimitiveStar *>(tempPrimitives_.front());
		assert(theStar != NULL);

		float radius = getRadius(x, y);

		theStar->SetOuterRadius(radius); 
		theStar->SetInnerRadius(radius/2);
	}

}

float StarModusController::getRadius(int x, int y) const {
	Coordinate radius = Coordinate(x, y) - startingPoint_;

	return sqrt(pow(radius.GetX(), 2) + pow(radius.GetY(), 2));
}

}
