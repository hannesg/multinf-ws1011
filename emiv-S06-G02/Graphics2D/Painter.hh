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
#include "Controller/ModusController.hh"
#include "Controller/PointModusController.hh"
#include "Controller/LineModusController.hh"
#include "Controller/BoxModusController.hh"
#include "Controller/PolygonModusController.hh"
#include "Controller/StarModusController.hh"
#include "Image.hh"

namespace Graphics2D {

class Painter : public PainterBase {

public:

	// constructor
	Painter(const Image &backgroundImage);

	// deconstructor
	virtual ~Painter();

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

	// Returns the current color
	Color GetCurrentColor() const { return currentColor_; }

private:

	// Print Help
	void PrintHelp();

	// Enumeration fuer moegliche Modi 
	enum Modus { POINT, LINE, POLYGON, BOX, STAR };

	// Sets the current Modus
	void SetModus(Modus m);

	// Die gegenwaertige Farbe
	Color currentColor_;

	// Vektor, der alle bisher gezeichneten Primitiven enthaelt
	// Hier *muessen* Zeiger verwendet werden!!
	vector<PrimitiveBase *> primitives_;

	// Gegenwaertiger Modus
	Modus currentModus_;

	// Gegenwaertiger Controller
	ModusController *currentController_;

	// Vorgegebene Controller
	PointModusController pointModusController_;
	LineModusController lineModusController_;
	BoxModusController boxModusController_;
	PolygonModusController polygonModusController_;
	StarModusController starModusController_;

	// angehalten?
	bool pause;

};


}


#endif
