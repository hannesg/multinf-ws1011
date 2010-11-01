#ifndef __IMAGE_HH
#define __IMAGE_HH

// #include <Graphics2DBase/ImageBase.hh>
#include "ImageBase.hh"
#include "Image.hh"

namespace Graphics2D {

class Image : public ImageBase
{
public:
	Image();
	Image(const Image &other);
	Image &operator =(const Image &other);
	virtual ~Image();

	virtual void FillZero();
	
	virtual inline unsigned char GetPixel(const int &x, const int &y, const int &ch) const;
	virtual inline void SetPixel(const int &x, const int &y, const int &ch, const unsigned char &value);
	
	virtual int LoadPPM(const std::string &filename);
	virtual int SavePPM(const std::string &filename);
	
	
};
		
		
		
}

#endif
 
