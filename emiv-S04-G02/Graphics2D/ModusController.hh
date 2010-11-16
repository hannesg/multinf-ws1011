/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef MODUS_CONTROLLER_HH
#define MODUS_CONTROLLER_HH

#include <vector>
#include "PrimitiveBase.hh"

using namespace std;

namespace Graphics2D {

//forward declaration
class Painter;


/* Klasse, die den jeweiligen Modus kontrolliert, und entsprechend des Modus
 * den Painter modifiziert */
class ModusController {
public:
	/* Constructor. Needs always a reference to the corresponding painter */
	ModusController(Painter &b);

	/* deconstructor */
	virtual ~ModusController() { /* Aufraeumen und Speicherplatz freigeben! */ RemoveAllPrimitives(); }

	/* called, when the modus is activated */
	virtual void Activate() = 0;

	/* called, when modus is deactivated */
	virtual void Deactivate() = 0;

	/* The following functions are taken from PointerBase */

	/// this function is called when a user presses a mouse button in the gui at (x,y)
	virtual void MouseDown(int x, int y) = 0;

	/// this function is called when a user releases a mouse button in the gui at (x,y)
	virtual void MouseUp(int x, int y) = 0;

	/// this function is called when a user holds a mouse button in the gui at (x,y)
	virtual void MouseMove(int x, int y) = 0;

	/// this function is called when a user presses a key in the gui. ch is the key pressed.
	// virtual void KeyPressed(unsigned char ch, int x, int y) = 0;

	/* liefert den Vektor mit temporaeren Primitiven zurueck */
	const vector<PrimitiveBase *> & GetTemporaryPrimitives() const { return tempPrimitives_; }

	// Removes all temporary primitives
	void RemoveAllPrimitives();

protected:
	/* der Painter, zu dem dieser Controller gehoehrt */
	Painter &myPainter_;

	// Vektor, der alle *temporaeren* zu zeichnenden Primitive enthaelt
	vector<PrimitiveBase *> tempPrimitives_;
};


}

#endif
