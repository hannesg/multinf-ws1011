/*
 * Histogram.hh
 *
 *  Created on: Nov 30, 2010
 *      Author: hannes
 */

#ifndef HISTOGRAM_HH_
#define HISTOGRAM_HH_

#include <vector>
#include "PrimitiveBase.hh"
#include "Image.hh"
#include "ImageBase.hh"
#include "ColorConversion.hh"
#include "PrimitiveBox.hh"

namespace Graphics2D {

class Histogram : public PrimitiveBase {
public:
	/* constructors */
	Histogram();
	Histogram(const Coordinate &c1, const Coordinate &c2, const Color &c);

	virtual ~Histogram();

	/* Histogramm von Image image und channel channel erstellen */
	int FromImage(const Image& image, const int channel);


	int Max() const;
	int Min() const;

	int MaxValue() const;

	/* überschriebene Zeichenfunktion */
	virtual void Draw(Graphics2D::ImageBase* image) const;

	/* stellt den Kontrast von src optimal ein */
	static void Autocontrast(const Image &src, Image &dest);

protected:
	/* speichert das Histogramm */
	std::vector<int> histogram_;

	/* Anzahl der erlaubten Punkte */
	virtual int GetNumberOfPointsAllowed() const { return 2; }

private:
	/* Initialisation function */
	void Init(const Coordinate &c1, const Coordinate &c2, const Color &c);
};

}

#endif /* HISTOGRAM_HH_ */
