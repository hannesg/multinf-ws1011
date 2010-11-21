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
	/* wenn Breite und Hoehe uebereinstimmen, einfach kopieren */
	if(img_.GetWidth() == img->GetWidth() && img_.GetHeight() == img->GetHeight()) {
		memcpy(img->GetData(), img_.GetData(), img_.GetWidth()*img_.GetHeight()*3);
	} else {

		/* Kopiert das Bild. Achtet darauf, dass nicht ueber den Rand eines 
		 * der Bilder gelesen bzw. geschrieben wird. */

		unsigned int minWidth = min(img->GetWidth(), img_.GetWidth());
		unsigned int minHeight = min(img->GetHeight(), img_.GetHeight());

		for(unsigned int x = 0; x < minWidth; x++) {
			for(unsigned int y = 0; y < minHeight; y++) {
				img->SetPixel(x, y, 0, img_.GetPixel(x, y, 0));
				img->SetPixel(x, y, 1, img_.GetPixel(x, y, 1));
				img->SetPixel(x, y, 2, img_.GetPixel(x, y, 2));
			}
		}
	}
	
}

}
