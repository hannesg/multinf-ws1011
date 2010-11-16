/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#include "ModusController.hh"
#include "Painter.hh"

namespace Graphics2D {

ModusController::ModusController(Painter &b) : myPainter_(b) { }

void ModusController::RemoveAllTemporaryPrimitives() {
	vector<PrimitiveBase *>::iterator it;

	// Alle temporaere Primitives loeschen (Da sie mit new erstellt wurden! )
	for(it = tempPrimitives_.begin(); it != tempPrimitives_.end(); it++) {
		delete *it;
	}

	// Liste leeren
	tempPrimitives_.clear();
}

}