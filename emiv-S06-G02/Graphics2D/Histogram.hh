/*
 * Histogram.hh
 *
 *  Created on: Nov 30, 2010
 *      Author: hannes
 */

#ifndef HISTOGRAM_HH_
#define HISTOGRAM_HH_

#include "PrimitiveBase.hh"
#include "Image.hh"
#include "ImageBase.hh"
#include "ColorConversion.hh"
#include "PrimitiveBox.hh"
#include <vector>

namespace Graphics2D {

class Histogram : public PrimitiveBase {
public:
	Histogram();
	Histogram(const Coordinate &c1, const Coordinate &c2, const Color &c);

	virtual ~Histogram();
	int FromImage(const Image& image, const int channel);

	int Max() const;
	int Min() const;

	int MaxValue() const;

	virtual void Draw(Graphics2D::ImageBase* image) const;

	static void Autocontrast(const Image &src, Image &dest);

protected:
	std::vector<int> histogram_;
	/* Anzahl der erlaubten Punkte */
	virtual int GetNumberOfPointsAllowed() const { return 2; }
private:
	void Init(const Coordinate &c1, const Coordinate &c2, const Color &c);
};

}

#endif /* HISTOGRAM_HH_ */
