/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef __BACKGROUND_IMAGE_HH
#define __BACKGROUND_IMAGE_HH

#include "PrimitiveBase.hh"
#include "Image.hh"

namespace Graphics2D {

/* Klasse, die ein Bild zeichnet */
class BackgroundImage : public PrimitiveBase
{
public:
	/* nimmt uebergebenes Bild */
	BackgroundImage(const Image &img) { img_ = img; }

	/* Draw-Funktion */
	virtual void Draw(ImageBase *img) const;

private:
	Image img_;
};

}
#endif
