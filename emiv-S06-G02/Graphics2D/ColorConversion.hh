
#ifndef COLOR_CONVERSION_HH
#define COLOR_CONVERSION_HH

#include "Image.hh"

namespace Graphics2D{

class ColorConversion {

public:
	static void ToGrey(const Image &src, Image &dst);
	static void ToHSV(const Image &src, Image &dst);
	static void ToRGB(const Image &src, Image &dst);

};

}

#endif 
