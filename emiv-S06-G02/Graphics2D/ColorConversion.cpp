
#include "ColorConversion.hh"

namespace Graphics2D {

void ColorConversion::ToGrey(const Image &src, Image &dst) {
	
	if(src.GetColorModel() == ImageBase::cm_Grey) {
		// do nothing
		dst = src;
		return;
	} 

	const Image *actualSrc;
	Image converted;

	if (src.GetColorModel() == ImageBase::cm_HSV) {
		ColorConversion::ToBMP(src, converted);
		actualSrc = &converted;
	} else {
		actualSrc = &src;
	}

	dst.Init(actualSrc->GetWidth(), actualSrc->GetHeight());
	dst.SetColorModel(ImageBase::cm_Grey);
	

	for(unsigned x = 0; x < actualSrc->GetWidth(); x++) {
		for(unsigned y = 0; y < actualSrc->GetHeight(); y++) {
			
			int r = actualSrc->GetPixel(x, y, 0);
			int g = actualSrc->GetPixel(x, y, 1);
			int b = actualSrc->GetPixel(x, y, 2);
			
			int grey = 30*r + 59*g + 11*b;
			grey /= 100;
			
			dst.SetPixel(x, y, 0, grey);
			dst.SetPixel(x, y, 1, grey);
			dst.SetPixel(x, y, 2, grey);
		}
	}
}

void ColorConversion::ToRGB(const Image &src, Image &dst) {

	if(src.GetColorModel() == ImageBase::cm_Grey || 
		src.GetColorModel() == ImageBase::cm_RGB) {
		// do nothing 
		dst = src;
		dst.SetColorModel(ImageBase::cm_RGB);
		return;
	}


	
}

void ColorConversion::ToHSV(const Image &src, Image &dst) {
	
	if(src.GetColorModel() == ImageBase::cm_HSV) {
		// do nothing
		dst = src;
		return;
	}

}

} 
