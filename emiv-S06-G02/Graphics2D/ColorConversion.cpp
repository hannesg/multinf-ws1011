
#include "ColorConversion.hh"

namespace Graphics2D {

void ColorConversion::ToGrey(const Image &src, Image &dst) {
	
	if(src.GetColorModel() != ImageBase::cm_RGB) {
		throw exception();
	}

	dst.Init(src.GetWidth(), src.GetHeight());
	dst.SetColorModel(ImageBase::cm_Grey);
	
	for(unsigned x = 0; x < src.GetWidth(); x++) {
		for(unsigned y = 0; y < src.GetHeight(); y++) {
			
			int r = src.GetPixel(x, y, 0);
			int g = src.GetPixel(x, y, 1);
			int b = src.GetPixel(x, y, 2);
			
			int grey = 30*r + 59*g + 11*b;
			grey /= 100;
			
			dst.SetPixel(x, y, 0, grey);
			dst.SetPixel(x, y, 1, grey);
			dst.SetPixel(x, y, 2, grey);
		}
	}
}

void ColorConversion::ToRGB(const Image &src, Image &dst) {
	if(src.GetColorModel() != ImageBase::cm_HSV) {
		throw exception();
	}
}

void ColorConversion::ToHSV(const Image &src, Image &dst) {
	if(src.GetColorModel() != Image::cm_RGB && src.GetColorModel() != Image::cm_Grey) {
		throw exception();
	}
}

} 
