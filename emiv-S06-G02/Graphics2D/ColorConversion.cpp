
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
		ColorConversion::ToRGB(src, converted);
		actualSrc = &converted;
	} else {
		actualSrc = &src;
	}

	dst.Init(actualSrc->GetWidth(), actualSrc->GetHeight());
	dst.SetColorModel(ImageBase::cm_Grey);
	
	unsigned int size = actualSrc->GetWidth()*actualSrc->GetHeight();
	const unsigned char *data = actualSrc->GetData();
	unsigned char *dstData = dst.GetData();

	for(unsigned int i = 0; i < size; i++) {
		int r = data[3*i+0];
		int g = data[3*i+1];
		int b = data[3*i+2];
			
		int grey = 30*r + 59*g + 11*b;
		grey /= 100;

		/* Normalisieren, falls (sehr grosses falls) grey < 0 oder grey > 255 */
		if(grey < 0) { grey = 0; }
		if(grey > 255) { grey = 255; }
			
		dstData[3*i+0] = grey;
		dstData[3*i+1] = grey;
		dstData[3*i+2] = grey;
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
