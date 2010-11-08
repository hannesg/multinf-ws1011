#ifndef __COLOR_HH
#define __COLOR_HH

#include <string>

using namespace std;

namespace Graphics2D {

class Color {
public:

	/* constructors */
	Color() {
		r_ = g_ = b_ = 0;
		name_ = "black";
	}

	Color(unsigned char r, unsigned char g, unsigned char b) : r_(r), g_(g), b_(b), name_("") { }

	Color(unsigned char r, unsigned char g, unsigned char b, 
		string name) : r_(r), g_(g), b_(b), name_(name) { }


	/* setters */
	inline void SetR(unsigned char r) { r_ = r; }
	inline void SetG(unsigned char g) { g_ = g; }
	inline void SetB(unsigned char b) { b_ = b; }
	inline void SetName(string s) { name_ = s; }

	/* getters */
	inline unsigned char GetR() const { return r_; }
	inline unsigned char GetG() const { return g_; }
	inline unsigned char GetB() const { return b_; }
	inline string GetName() const { return name_; }

	/* Static functions, returning some discrete color values */
	static Color black() { return Color(0, 0, 0, "black"); }
	static Color red() { return Color(255, 0, 0, "red"); }
	static Color green() { return Color(0, 255, 0, "green"); }
	static Color blue() { return Color(0, 0, 255, "blue"); }

private:
	unsigned char r_, g_, b_;
	string name_;

};



}

#endif 
