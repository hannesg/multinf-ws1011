/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef PAINTER_HH
#define PAINTER_HH

#include "PainterBase.hh"
#include "Color.hh"
#include "PrimitiveBase.hh"

namespace Graphics2D {

class Painter : public PainterBase {

public:

	// constructor
	Painter();

	// deconstructor
	~Painter();

	/// draws a vector of primitives
	virtual void Draw();

	/// helpers for the canvas2d class. currently selected color and primitive name (see keypressed)
	virtual std::string GetColorString();
	virtual std::string GetString();

	/// this function is called when a user presses a mouse button in the gui at (x,y)
	virtual void MouseDown(int x, int y);

	/// this function is called when a user releases a mouse button in the gui at (x,y)
	virtual void MouseUp(int x, int y);

	/// this function is called when a user holds a mouse button in the gui at (x,y)
	virtual void MouseMove(int x, int y);

	/// this function is called when a user presses a key in the gui. ch is the key pressed.
	/// keys '1' to '4' select different colors
	/// key 'p' for 'draw points', 'l' for 'draw lines' etc.
	/// key 'h' prints help to console
	virtual void KeyPressed(unsigned char ch, int x, int y);

	// Adds a primitive to the primitive list 
	void AddPrimitive(PrimitiveBase *p);

	// Removes all primitives
	void RemoveAllPrimitives();

private:

	// Adds a temporary primitive to the temporary primitive list
	void AddTemporaryPrimitive(PrimitiveBase *p);

	// Removes all temporary primitives
	void RemoveAllTemporaryPrimitives();

	// Returns temporary primitive number i
	PrimitiveBase *GetTemporaryPrimitive(int i);

	// Print Help
	void PrintHelp();

	// Die gegenwaertige Farbe
	Color currentColor_;

	// Vektor, der alle bisher gezeichneten Primitiven enthaelt
	vector<PrimitiveBase *> primitives_;

	// Vektor, der alle *temporaeren* zu zeichnenden Primitive enthaelt
	vector<PrimitiveBase *> tempPrimitives_;

	// Enumeration fuer moegliche Modi 
	enum Modus { POINT, LINE, POLYGON, BOX };

	// Gegenwaertiger Modus
	Modus currentModus_;
};


}


#endif
