/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <memory.h>
#include "BackgroundImage.hh"

using namespace std;

namespace Graphics2D {

void BackgroundImage::Draw(ImageBase *img) const
{
	/* Kopiert das Bild. Achtet darauf, dass nicht ueber den Rand eines 
	 * der Bilder gelesen bzw. geschrieben wird. */
	for(unsigned int x = 0; x < min(img->GetWidth(), img_.GetWidth()); x++) {
		for(unsigned int y = 0; y < min(img->GetHeight(), img_.GetHeight()); y++) {
			img->SetPixel(x, y, 0, img_.GetPixel(x, y, 0));
			img->SetPixel(x, y, 1, img_.GetPixel(x, y, 1));
			img->SetPixel(x, y, 2, img_.GetPixel(x, y, 2));
		}
	}
	// memset(img->GetData(), 255, img->GetWidth()*img->GetHeight()*3);
}

}
