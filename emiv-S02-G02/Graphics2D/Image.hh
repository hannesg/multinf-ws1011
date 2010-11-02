/*
Gruppe: 02
Serie 02
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef __IMAGE_HH
#define __IMAGE_HH

#include <fstream>
#include "ImageBase.hh"

using namespace std;

namespace Graphics2D {

class Image : public ImageBase
{
public:
	Image();
	Image(const Image &other);
	Image &operator =(const Image &other);
	virtual ~Image();

	virtual void FillZero();
	
	virtual unsigned char GetPixel(const int &x, const int &y, const int &ch) const;
	virtual void SetPixel(const int &x, const int &y, const int &ch, const unsigned char &value);
	
	/* Laedt Bilddatei. Rueckgabewert 0, wenn Erfolg, -1, sonst */
	virtual int LoadPPM(const std::string &filename);

	/* Speichert in Bilddatei. Rueckgabewert 0, wenn Erfolg, -1, sonst */
	virtual int SavePPM(const std::string &filename) const;
	

private:
	/* Liest den Header einer PPM-Datei */
	bool readHeader(ifstream &in, bool &Binary, int &width, int &height, int &max) const;
};
		
		
		
}

#endif
 
